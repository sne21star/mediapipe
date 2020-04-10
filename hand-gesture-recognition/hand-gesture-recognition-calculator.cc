#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <typeinfo>
#include <algorithm>
#include <memory>
#include <array>
//#include <dos.h>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/input_stream_handler.h"
#include "tensorflow/lite/kernels/register.h"
#include "mediapipe/util/resource_util.h"
#if defined(MEDIAPIPE_ANDROID)
#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#endif  // ANDROID
/*
#if !defined(MEDIAPIPE_DISABLE_GL_COMPUTE)
    const auto& input_tensors =
        cc->Inputs().Tag("TENSORS_GPU").Get<std::vector<GpuTensor>>();
    RET_CHECK_GT(input_tensors.size(), 0);
    MP_RETURN_IF_ERROR(gpu_helper_.RunInGlContext(
        [this, &input_tensors]() -> ::mediapipe::Status {
          // Explicit copy input.
          gpu_data_in_.resize(input_tensors.size());
          for (int i = 0; i < input_tensors.size(); ++i) {
            RET_CHECK_CALL(
                CopyBuffer(input_tensors[i], gpu_data_in_[i]->buffer));
          }

          return ::mediapipe::OkStatus();
        }));
#elif defined(MEDIAPIPE_IOS)
    const auto& input_tensors =
        cc->Inputs().Tag("TENSORS_GPU").Get<std::vector<GpuTensor>>();
    RET_CHECK_GT(input_tensors.size(), 0);
    // Explicit copy input with conversion float 32 bits to 16 bits.
    gpu_data_in_.resize(input_tensors.size());
    id<MTLCommandBuffer> command_buffer = [gpu_helper_ commandBuffer];
    command_buffer.label = @"TfLiteInferenceCalculatorConvert";
    id<MTLComputeCommandEncoder> compute_encoder =
        [command_buffer computeCommandEncoder];
    [compute_encoder setComputePipelineState:fp32_to_fp16_program_];
    for (int i = 0; i < input_tensors.size(); ++i) {
      [compute_encoder setBuffer:input_tensors[i] offset:0 atIndex:0];
      [compute_encoder setBuffer:gpu_data_in_[i]->buffer offset:0 atIndex:1];
      constexpr int kWorkgroupSize = 64;  // Block size for GPU shader.
      MTLSize threads_per_group = MTLSizeMake(kWorkgroupSize, 1, 1);
      const int threadgroups =
          NumGroups(gpu_data_in_[i]->elements, kWorkgroupSize);
      [compute_encoder dispatchThreadgroups:MTLSizeMake(threadgroups, 1, 1)
                      threadsPerThreadgroup:threads_per_group];
    }
    [compute_encoder endEncoding];
    [command_buffer commit];
#else
    RET_CHECK_FAIL() << "GPU processing not enabled.";
#endif
  } else {
    // Read CPU input into tensors.
    const auto& input_tensors =
        cc->Inputs().Tag("TENSORS").Get<std::vector<TfLiteTensor>>();
    RET_CHECK_GT(input_tensors.size(), 0);
    for (int i = 0; i < input_tensors.size(); ++i) {
      const TfLiteTensor* input_tensor = &input_tensors[i];
      RET_CHECK(input_tensor->data.raw);
      if (use_quantized_tensors_) {
        const uint8* input_tensor_buffer = input_tensor->data.uint8;
        uint8* local_tensor_buffer = interpreter_->typed_input_tensor<uint8>(i);
        std::memcpy(local_tensor_buffer, input_tensor_buffer,
                    input_tensor->bytes);
      } else {
        const float* input_tensor_buffer = input_tensor->data.f;
        float* local_tensor_buffer = interpreter_->typed_input_tensor<float>(i);
        std::memcpy(local_tensor_buffer, input_tensor_buffer,
                    input_tensor->bytes);
      }
    }
  }
*/
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
     LOG(INFO) << "X Stn Devi";
      LOG(INFO) << std::to_string(x_sdev);
       LOG(INFO) << "Y Stn Devi";
      LOG(INFO) << std::to_string(y_sdev);
     // get z scores
    std::vector<NormalizedLandmark> zscores;
    float zscore_array[42] = {0};
    for(unsigned int i = 0; i < 21; i++){
        NormalizedLandmark scored = NormalizedLandmark();
        scored.set_x((landmarkList.landmark(i).x() - x_mean) / x_sdev);
        scored.set_y((landmarkList.landmark(i).y() - y_mean) / y_sdev);

        zscore_array[2*i] = (landmarkList.landmark(i).x() - x_mean) / x_sdev;
        zscore_array[2*i + 1] = (landmarkList.landmark(i).y() - y_mean) / y_sdev;

//        zscores.push_back(scored);
    }

    float maxprob = 0;
    int maxindex = 24;
    std::string model_path = "mediapipe/models/model.tflite";
    ASSIGN_OR_RETURN(model_path, PathToResourceAsFile(model_path));
    const char *filename = model_path.c_str();
    std::unique_ptr<tflite::Interpreter> interpreter;
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(filename);

    if(model)
    {
        //  Build the interpreter
        LOG(INFO) << "Build interpreter before";
        LOG(INFO) << "Build interpreter before resolver";
        tflite::ops::builtin::BuiltinOpResolver resolver;
        // LOG(INFO) << "Build interpreter before resolver";
        //model->error_reporter();
        LOG(INFO) << "resolved reporter\n";

        tflite::InterpreterBuilder(*model, resolver)(&interpreter);
       // tflite::PrintInterpreterState(interpreter.get());
        LOG(INFO) << "Interpreter";
        interpreter->SetNumThreads(1);
        if(interpreter)
        {
            std::vector<int> sizes = {42};

            // Resize input tensors, if desired.
            LOG(INFO) << "Inputs before";
            interpreter->UseNNAPI(false);
          //  const int num_threads = 1;
          //  if(num_threads != 1){
            //        interpreter->SetNumThreads(num_threads);
           // }
            int inputINT = interpreter->inputs()[0];
            LOG(INFO) << "inputINT";
             LOG(INFO) << std::to_string(inputINT);
             LOG(INFO) << "resize Inputs before";
            interpreter->ResizeInputTensor(interpreter->inputs()[0], {42});
             LOG(INFO) << "before Inputs before";

            //usleep(1000000);
            interpreter->SetNumThreads(1);
            if(interpreter->AllocateTensors() == kTfLiteOk)
               {
                 //TfLiteIntArray* dims = interpreter->tensor(inputINT)->dims;
                // int len = sizeof(dims->data)/sizeof(dims->data[0]);
                //  LOG(INFO) << "LENGTH OF DIMENSION DATA";
               //  LOG(INFO) << len;
                 //LOG(INFO) << std::to_string(x);
                  const auto& input_indices = interpreter->inputs();
                  LOG(INFO) << "Size of Input Tensor input_indices.size()";
                  LOG(INFO) << std::to_string(input_indices.size());
                 /*
                 int wanted_height = dims->data[1];
                 int wanted_width = dims->data[2];
                 int wanted_channels = dims->data[3];

                 dims->data[3] = 4;

                 LOG(INFO) << "Dimension 0??";
                 LOG(INFO) << std::to_string(dims->data[0]);
                  LOG(INFO) << "Height";
                 LOG(INFO) << std::to_string(wanted_height);
                  LOG(INFO) << "Type";
                 LOG(INFO) << std::to_string(interpreter->tensor(inputINT)->type);
                 LOG(INFO) << "Width";
                 LOG(INFO) << std::to_string(wanted_width);
                   LOG(INFO) << "Channel";
                 LOG(INFO) << std::to_string(wanted_channels);
                  LOG(INFO) << "Dimension Data of the three exist";
                  LOG(INFO) << std::to_string(dims->data[1]);
                  LOG(INFO) << std::to_string(dims->data[2]);
                  LOG(INFO) << std::to_string(dims->data[3]);
                   LOG(INFO) << std::to_string(dims->data[1]==NULL);
                  LOG(INFO) << std::to_string(dims->data[2]==NULL);
                  LOG(INFO) << std::to_string(dims->data[3]==NULL);
                   LOG(INFO) << "Data Empty";
                   LOG(INFO) << std::to_string(dims->data == NULL);
                   LOG(INFO) << "Dimensions Empty";
                   LOG(INFO) << std::to_string(dims == nullptr);
                */
                //if(dims->data[0] > 0 && dims->data[0] < 1000)
                //{
                 LOG(INFO) << "after Allocation";

                 LOG(INFO) << "zscore";
                 LOG(INFO) << std::to_string(zscore_array[0]);
                 for (int i = 0; i < 42; i++)
                 {
                    interpreter->typed_input_tensor<float>(0)[i] = zscore_array[i];
                 }
                    //LOG(INFO) << std::to_string(interpreter->typed_input_tensor<float>(0)[41]);
                    LOG(INFO) << "Before Invoke";

                    if(interpreter->Invoke() == kTfLiteOk)
                    {
                        LOG(INFO) << "Before Output";
                        float* output = interpreter->typed_output_tensor<float>(0);

                        LOG(INFO) << "After Output";
                        if(output != 0)
                        {
                            LOG(INFO) << std::to_string(output[0]);
                            for (int i = 0; i < 24; i++)
                            {
                                if (output[i] > maxprob)
                                {
                                    maxprob = output[i];
                                    maxindex = i;
                                }
                            }
                        }

                     }

                    }


            //}
       }
    }
    std::string letters =  {'G', 'V', 'Y', 'A', 'E', 'L', 'R', 'W', 'Q', 'T', 'I', 'P', 'H', 'F', 'O', 'U', 'M', 'B', 'N', 'D', 'K', 'X', 'S', 'C', 'Z'};
    ASL_Word = letters[maxindex];

     if (cc->Outputs().HasTag("ASL")) {
    cc->Outputs().Tag("ASL").AddPacket(
        MakePacket<std::string>(ASL_Word)
            .At(cc->InputTimestamp()));
           }
    return ::mediapipe::OkStatus();
} // namespace mediapipe

} // namespace mediapipe