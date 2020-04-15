// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/memory/memory.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator_options.pb.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/util/render_data.pb.h"

namespace mediapipe {

namespace {

constexpr char kTextTag[] = "TEXT";
constexpr char kRenderDataTag[] = "RENDER_DATA";
constexpr double kTextLineXPos = 0.25;
constexpr double kTextLineHeight = 0.25;
constexpr double kTextFontHeight = 0.05;

}  // namespace

// A calculator that converts a string to RenderData proto for visualization
// via AnnotationOverlayCalculator.
//
// The input can be std::string.
//
// Please note that this calculator displays the string on the top left corner
// of the image by using normalized coordinates (0, 0). Modify the calculator
// to accept a location for the string.
//
// Example config:
// node {
//   calculator: "StringToRenderDataCalculator"
//   input_stream: "TEXT:text"
//   output_stream: "RENDER_DATA:text_render_data"
// }
class StringToRenderDataCalculator : public CalculatorBase {
 public:
  StringToRenderDataCalculator() {}
  ~StringToRenderDataCalculator() override {}
  StringToRenderDataCalculator(const StringToRenderDataCalculator&) =
      delete;
  StringToRenderDataCalculator& operator=(
      const StringToRenderDataCalculator&) = delete;

  static ::mediapipe::Status GetContract(CalculatorContract* cc);

  ::mediapipe::Status Open(CalculatorContext* cc) override;

  ::mediapipe::Status Process(CalculatorContext* cc) override;

};
REGISTER_CALCULATOR(StringToRenderDataCalculator);

::mediapipe::Status StringToRenderDataCalculator::GetContract(
    CalculatorContract* cc) {
  RET_CHECK(cc->Inputs().HasTag(kTextTag))
      << "None of the input streams are provided.";
  RET_CHECK(cc->Outputs().HasTag(kRenderDataTag))
      << "None of the output streams are provided.";

  cc->Inputs().Tag(kTextTag).Set<std::string>();
  cc->Outputs().Tag(kRenderDataTag).Set<RenderData>();

  return ::mediapipe::OkStatus();
}

::mediapipe::Status StringToRenderDataCalculator::Open(
    CalculatorContext* cc) {
  // Every input packet either has a corresponding output packet or a
  // corresponding timestamp bound update for the output stream if no
  // output packet is generated.
  cc->SetOffset(TimestampDiff(0));

  return ::mediapipe::OkStatus();
}

::mediapipe::Status StringToRenderDataCalculator::Process(
    CalculatorContext* cc) {

  if (cc->Inputs().Tag(kTextTag).IsEmpty()) {
    return ::mediapipe::OkStatus();
  }

  auto render_data = absl::make_unique<RenderData>();
  render_data->set_scene_class("TEXT");

  const std::string& text_string =
      cc->Inputs().Tag(kTextTag).Get<std::string>();

  auto* text_annotation = render_data->add_render_annotations();
  text_annotation->mutable_color()->set_r(0);
  text_annotation->mutable_color()->set_g(255);
  text_annotation->mutable_color()->set_b(255);
  text_annotation->set_thickness(4.0);

  auto* text = text_annotation->mutable_text();
  text->set_display_text(text_string);
  LOG(INFO) << "Displaying text: " << text_string;

  text->set_normalized(true);
  text->set_left(kTextLineXPos);
  text->set_baseline(kTextLineHeight);
  text->set_font_height(kTextFontHeight);

  cc->Outputs()
      .Tag(kRenderDataTag)
      .Add(render_data.release(), cc->InputTimestamp());
  return ::mediapipe::OkStatus();
}

}  // namespace mediapipe
