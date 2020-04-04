#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <typeinfo>
#include <algorithm>

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/input_stream_handler.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/tensor.h"
#include "tensorflow/lite/kernels/padding.h"

#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "absl/memory/memory.h"
#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "tensorflow/lite/string_util.h"

#include "absl/memory/memory.h"
#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/profiling/profiler.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/tools/evaluation/utils.h"
#include <sys/types.h>

void stringToFile();
std::string ASL_Word;
namespace mediapipe
{

namespace
{
constexpr char normRectTag[] = "NORM_RECT";
constexpr char normalizedLandmarkListTag[] = "NORM_LANDMARKS";
}

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

    float x_mean = 0;
    float x_sdev = 0;
    float y_mean = 0;
    float y_sdev = 0;


    // Find mean
    for(unsigned int i = 0; i < 21; i++){
        x_mean += landmarkList.landmark(i).x();
        y_mean += landmarkList.landmark(i).y();
    }

    x_mean /= 21.0;
    y_mean /= 21.0;

    // Find sdev
    // Σ(xi -mu)^2
    for(unsigned int i = 0; i < 21; i++){
        x_sdev += powf(landmarkList.landmark(i).x() - x_mean, 2.0);
        y_sdev += powf(landmarkList.landmark(i).y() - y_mean, 2.0);
    }

    // sqrt((Σ(xi -mu)^2) / N)
    x_sdev = sqrtf(x_sdev);
    y_sdev = sqrtf(y_sdev);

     // get z scores
    std::vector<NormalizedLandmark> zscores;
    float zscore_array[42] = {0};

    for(unsigned int i = 0; i < 21; i++){
        NormalizedLandmark scored = NormalizedLandmark();
        scored.set_x((landmarkList.landmark(i).x() - x_mean) / x_sdev);
        scored.set_y((landmarkList.landmark(i).y() - y_mean) / y_sdev);

        zscore_array[2*i] = (landmarkList.landmark(i).x() - x_mean) / x_sdev;
        zscore_array[2*i + 1] = (landmarkList.landmark(i).y() - y_mean) / y_sdev;

        zscores.push_back(scored);
    }


    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("/Users/ishaghodgaonkar/SeniorDesign/mediapipe/hand-gesture-recognition/model.tflite");

    //  Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);

    std::vector<int> sizes = {42};

    // Resize input tensors, if desired.
    interpreter->ResizeInputTensor(0, sizes);
    interpreter->AllocateTensors();

    for (int i = 0; i < 42; i++)
    {
        interpreter->typed_input_tensor<float>(0)[i] = zscore_array[i];
    }
    //interpreter->typed_input_tensor<float*>(0)[0] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    interpreter->Invoke();


    LOG(INFO) << "here";
    float* output = interpreter->typed_output_tensor<float>(0);
    LOG(INFO) << "here 2";

    float maxprob = 0;
    int maxindex = 0;
    for (int i = 0; i < 24; i++)
    {
        if (output[i] > maxprob)
        {
            maxprob = output[i];
            maxindex = i;
        }
    }

    LOG(INFO) << "max probability" << maxprob;
    LOG(INFO) << "max index" << maxindex;

    std::string letters =  {'G', 'V', 'Y', 'A', 'E', 'L', 'R', 'W', 'Q', 'T', 'I', 'P', 'H', 'F', 'O', 'U', 'M', 'B', 'N', 'D', 'K', 'X', 'S', 'C'};
    ASL_Word = letters[maxindex];

     if (cc->Outputs().HasTag("ASL")) {
    cc->Outputs().Tag("ASL").AddPacket(
        MakePacket<std::string>(ASL_Word)
            .At(cc->InputTimestamp()));
           }
    return ::mediapipe::OkStatus();
} // namespace mediapipe

} // namespace mediapipe
