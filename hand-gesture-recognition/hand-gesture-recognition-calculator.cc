#include <cmath>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/input_stream_handler.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void stringToFile();
string ASL_Word;
namespace mediapipe
{

namespace
{
constexpr char normRectTag[] = "NORM_RECT";
constexpr char normalizedLandmarkListTag[] = "NORM_LANDMARKS";
} // namespace

// Graph config:
//
// node {
//   calculator: "HandGestureRecognitionCalculator"
//   input_stream: "NORM_LANDMARKS:scaled_landmarks"
//   input_stream: "NORM_RECT:hand_rect_for_next_frame"
// }
class HandGestureRecognitionCalculator : public CalculatorBase
{
public:
    static ::mediapipe::Status GetContract(CalculatorContract *cc);
    ::mediapipe::Status Open(CalculatorContext *cc) override;

    ::mediapipe::Status Process(CalculatorContext *cc) override;
private:
    float get_Euclidean_DistanceAB(float a_x, float a_y, float b_x, float b_y)
    {
        float dist = std::pow(a_x - b_x, 2) + pow(a_y - b_y, 2);
        return std::sqrt(dist);
    }

    bool areLandmarksClose(NormalizedLandmark point1, NormalizedLandmark point2)
    {
        float distance = this->get_Euclidean_DistanceAB(point1.x(), point1.y(), point2.x(), point2.y());
        return distance < 0.085;
    }

};

/*
void stringToFile(std::string toWrite)
{
    std::string s=toWrite;
    std::ofstream os("string_to_Screen.txt");
    if (!os)
    {
        std::cerr<<"Error writing to ..."<<std::endl;
    }
    else
    {
        os << s;
    }
}
*/

REGISTER_CALCULATOR(HandGestureRecognitionCalculator);

::mediapipe::Status HandGestureRecognitionCalculator::GetContract(
    CalculatorContract *cc)
{
    RET_CHECK(cc->Inputs().HasTag(normalizedLandmarkListTag));
    cc->Inputs().Tag(normalizedLandmarkListTag).Set<mediapipe::NormalizedLandmarkList>();

    RET_CHECK(cc->Inputs().HasTag(normRectTag));
    cc->Inputs().Tag(normRectTag).Set<NormalizedRect>();

    if (cc->Outputs().HasTag("ASL")) {
    cc->Outputs().Tag("ASL").Set<std::string>();
  }
    return ::mediapipe::OkStatus();
}

::mediapipe::Status HandGestureRecognitionCalculator::Open(
    CalculatorContext *cc)
{
    cc->SetOffset(TimestampDiff(0));
    return ::mediapipe::OkStatus();
}

::mediapipe::Status HandGestureRecognitionCalculator::Process(
    CalculatorContext *cc)
{
    // hand closed (red) rectangle
    const auto rect = &(cc->Inputs().Tag(normRectTag).Get<NormalizedRect>());
    float width = rect->width();
    float height = rect->height();

    if (width < 0.01 || height < 0.01)
    {
        LOG(INFO) << "No Hand Detected";
        if (cc->Outputs().HasTag("ASL")) {
    cc->Outputs().Tag("ASL").AddPacket(
        MakePacket<std::string>("No Hand Detected")
            .At(cc->InputTimestamp()));
           }
        return ::mediapipe::OkStatus();
    }

    const auto &landmarkList = cc->Inputs()
                                   .Tag(normalizedLandmarkListTag)
                                   .Get<mediapipe::NormalizedLandmarkList>();
    RET_CHECK_GT(landmarkList.landmark_size(), 0) << "Input landmark vector is empty.";

    // finger states
    bool thumbIsOpen = false;
    bool firstFingerIsOpen = false;
    bool secondFingerIsOpen = false;
    bool thirdFingerIsOpen = false;
    bool fourthFingerIsOpen = false;
    //
    float pseudoFixKeyPoint = landmarkList.landmark(2).x();
    if (landmarkList.landmark(3).x() < pseudoFixKeyPoint && landmarkList.landmark(4).x() < pseudoFixKeyPoint)
    {
        thumbIsOpen = true;
    }

    pseudoFixKeyPoint = landmarkList.landmark(6).y();
    if (landmarkList.landmark(7).y() < pseudoFixKeyPoint && landmarkList.landmark(8).y() < pseudoFixKeyPoint)
    {
        firstFingerIsOpen = true;
    }

    pseudoFixKeyPoint = landmarkList.landmark(10).y();
    if (landmarkList.landmark(11).y() < pseudoFixKeyPoint && landmarkList.landmark(12).y() < pseudoFixKeyPoint)
    {
        secondFingerIsOpen = true;
    }

    pseudoFixKeyPoint = landmarkList.landmark(14).y();
    if (landmarkList.landmark(15).y() < pseudoFixKeyPoint && landmarkList.landmark(16).y() < pseudoFixKeyPoint)
    {
        thirdFingerIsOpen = true;
    }

    pseudoFixKeyPoint = landmarkList.landmark(18).y();
    if (landmarkList.landmark(19).y() < pseudoFixKeyPoint && landmarkList.landmark(20).y() < pseudoFixKeyPoint)
    {
        fourthFingerIsOpen = true;
    }

    // Hand gesture recognition
    if (thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen)
    {
        ASL_Word = "C";
        LOG(INFO) << "C - ASL Letter!!";
    }

    else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen)
    {
        ASL_Word = "B";
        LOG(INFO) << "B - ASL Letter!";
    }
    else if (!thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
    {
            ASL_Word = "D";
             LOG(INFO) << "D - ASL LETTER!";
    }

    else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen && this->areLandmarksClose(landmarkList.landmark(6), landmarkList.landmark(10)))
    {
        if (!(this->areLandmarksClose(landmarkList.landmark(12), landmarkList.landmark(8))))
        {
            ASL_Word = "U";
            LOG(INFO) << "U - ASL Letter!";
        }
        else
        {
            ASL_Word = "R";
            LOG(INFO) << "R - ASL Letter!";
        }
    }

    else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
    {
        if ((this->areLandmarksClose(landmarkList.landmark(4), landmarkList.landmark(6))))
        {
            ASL_Word = "K";
            LOG(INFO) << "K - ASL Letter!";
        }
        else
        {
            ASL_Word = "V";
            LOG(INFO) << "V - ASL Letter!";
        }
    }
    else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && !fourthFingerIsOpen)
    {
        ASL_Word = "W";
        LOG(INFO) << "W - ASL Letter!";
    }

    else if (thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && fourthFingerIsOpen)
    {
         ASL_Word = "I LOVE YOU!";
        LOG(INFO) << "I LOVE YOU!";
    }
    else if (thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && fourthFingerIsOpen)
    {
        ASL_Word = "Y";
        LOG(INFO) << "Y - ASL Letter!";
    }
     else if (!thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen && this->areLandmarksClose(landmarkList.landmark(7), landmarkList.landmark(6)))
    {
        ASL_Word = "X";
        LOG(INFO) << "X - ASL LETTER!";
    }
    else if (thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen && this->areLandmarksClose(landmarkList.landmark(4), landmarkList.landmark(6)))
    {
        ASL_Word = "P";
        LOG(INFO) << "P - ASL LETTER!";
    }
    else if (!thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen && (this-> areLandmarksClose(landmarkList.landmark(7), landmarkList.landmark(3))))
    {
        ASL_Word = "S";
        LOG(INFO) << "S - ASL LETTER!";
    }
    else if (thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
    {
        if(this->areLandmarksClose(landmarkList.landmark(4), landmarkList.landmark(9)))
        {
             ASL_Word = "T";
             LOG(INFO) << "T - ASL LETTER!";
        }
        else if(this->areLandmarksClose(landmarkList.landmark(4), landmarkList.landmark(8)))
        {
            ASL_Word = "O";
             LOG(INFO) << "O - ASL LETTER!";
        }
        else
        {
            LOG(INFO) << "A - ASL LETTER!";
            ASL_Word = "A";
            //outputString = "A - ASL LETTER!";
        }
    }
    else if (!thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && fourthFingerIsOpen)
    {
        ASL_Word = "I";
        LOG(INFO) << "I - ASL LETTER!";
    }
    else if (!firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen && this->areLandmarksClose(landmarkList.landmark(4), landmarkList.landmark(8)))
    {
        ASL_Word = "F";
        LOG(INFO) << "F - ASL LETTER!";
    }
    else if (thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
    {
        ASL_Word = "L";
        LOG(INFO) << "L - ASL LETTER!";
    }
    else if(!thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen && !(this-> areLandmarksClose(landmarkList.landmark(7), landmarkList.landmark(3))))
    {
        ASL_Word = "E";
        LOG(INFO) << "E - ASL LETTER!";
    }
    else if (thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
    {
        ASL_Word = "H";
        LOG(INFO) << "H - ASL Letter!!";
    }
    else
    {
       ASL_Word = "Not in ASL";
        LOG(INFO) << "Finger States: " << thumbIsOpen << firstFingerIsOpen << secondFingerIsOpen << thirdFingerIsOpen << fourthFingerIsOpen;
        LOG(INFO) << "___";
    }
     if (cc->Outputs().HasTag("ASL")) {
    cc->Outputs().Tag("ASL").AddPacket(
        MakePacket<std::string>(ASL_Word)
            .At(cc->InputTimestamp()));
           }
    return ::mediapipe::OkStatus();
} // namespace mediapipe

} // namespace mediapipe
