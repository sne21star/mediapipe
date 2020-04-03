#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/port/ret_check.h"


#include <vector>
#include <string>
#include <iostream>


namespace mediapipe{

    namespace{
        constexpr char NormalizedLandmarks[] = "LANDMARKS";
    }


    class ZScoreCalculator : public CalculatorBase {
        public:
        ZScoreCalculator(){};
        ~ZScoreCalculator(){};

        static ::mediapipe::Status GetContract(CalculatorContract* cc){
            cc->Inputs().Tag(NormalizedLandmarks).Set<std::vector<std::vector<NormalizedLandmark>>>();
            cc->Outputs().Tag(NormalizedLandmarks).Set<std::vector<std::vector<NormalizedLandmark>>>();
            return ::mediapipe::OkStatus();
        }
        ::mediapipe::Status Open(CalculatorContext* cc){
            return ::mediapipe::OkStatus();
        }
        ::mediapipe::Status Process(CalculatorContext* cc){
            std::vector<std::vector<NormalizedLandmark>> hands = cc -> Inputs().Tag(NormalizedLandmarks).Get<std::vector<std::vector<NormalizedLandmark>>>();
            switch(hands.size()){
                case 0:
                    std::cout << "No hands detected!\n";
                    cc->Outputs().Tag(NormalizedLandmarks).AddPacket(cc->Inputs().Tag(NormalizedLandmarks).Value());
                    return ::mediapipe::OkStatus();
                case 1:
                    break;
                default:
                    std::cout << hands.size() << " hands detected!\n";
                    cc->Outputs().Tag(NormalizedLandmarks).AddPacket(cc->Inputs().Tag(NormalizedLandmarks).Value());
                    return ::mediapipe::OkStatus();
            }
            std::vector<NormalizedLandmark> hand = hands.at(0);
            float x_mean = 0;
            float x_sdev = 0;
            float y_mean = 0;
            float y_sdev = 0;

            // Find mean
            for(unsigned int i = 0; i < hand.size(); i++){
                x_mean += hand.at(i).x();
                y_mean += hand.at(i).y();
            }
            x_mean /= hand.size();
            y_mean /= hand.size();

            // Find sdev
            // Σ(xi -mu)^2
            for(unsigned int i = 0; i < hand.size(); i++){
                x_sdev += powf(hand.at(i).x() - x_mean, 2.0);
                y_sdev += powf(hand.at(i).y() - y_mean, 2.0);
            }
            // (Σ(xi -mu)^2) / N
            x_sdev /= hands.size();
            y_sdev /= hands.size();
            // sqrt((Σ(xi -mu)^2) / N)
            x_sdev = sqrtf(x_sdev);
            y_sdev = sqrtf(y_sdev);
            // LOG(INFO) << "X MEAN: " << x_mean << ", X SDEV: " << x_sdev;
            // LOG(INFO) << "YMEAN: " << y_mean << ", Y SDEV: " << y_sdev;


            // get z scores
            std::vector<NormalizedLandmark> zscores;
            for(unsigned int i = 0; i < hand.size(); i++){
                NormalizedLandmark scored = NormalizedLandmark();
                scored.set_x((hand.at(i).x() - x_mean) / x_sdev);
                scored.set_y((hand.at(i).y() - y_mean) / y_sdev);
                zscores.push_back(scored);
            }

            // send to output
            std::vector<std::vector<NormalizedLandmark>> send;
            send.push_back(zscores);
            std::unique_ptr<std::vector<std::vector<NormalizedLandmark>>> output_stream_collection = std::make_unique<std::vector<std::vector<NormalizedLandmark>>>(send);
            cc -> Outputs().Tag(NormalizedLandmarks).Add(output_stream_collection.release(), cc->InputTimestamp());

            return ::mediapipe::OkStatus();
        }
        ::mediapipe::Status Close(CalculatorContext* cc){
            return ::mediapipe::OkStatus();
        }

        private:

    };
    REGISTER_CALCULATOR(ZScoreCalculator);
}