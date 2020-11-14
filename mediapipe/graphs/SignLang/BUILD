# Copyright 2019 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load(
    "//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

mediapipe_binary_graph(
    name = "sign_lang_prediction_gpu_binary_graph",
    graph = "sign_lang_prediction_gpu.pbtxt",
    output_name = "sign_lang_prediction_gpu.binarypb",
    deps = [":mobile_calculators",
            ],
)
cc_library(
    name = "mobile_calculators",
    deps = [
        "//mediapipe/calculators/core:flow_limiter_calculator",
        "//mediapipe/calculators/core:gate_calculator",
        "//mediapipe/calculators/core:merge_calculator",
        "//mediapipe/calculators/core:previous_loopback_calculator",
        "//mediapipe/graphs/hand_tracking/subgraphs:hand_detection_gpu",
        "//mediapipe/graphs/hand_tracking/subgraphs:hand_landmark_gpu",
        "//mediapipe/graphs/hand_tracking/subgraphs:renderer_gpu",
    ],
)

