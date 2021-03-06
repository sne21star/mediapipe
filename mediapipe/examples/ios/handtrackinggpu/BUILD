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
    "@build_bazel_rules_apple//apple:ios.bzl",
    "ios_application",
)

licenses(["notice"])  # Apache 2.0

MIN_IOS_VERSION = "10.0"

ios_application(
    name = "HandTrackingGpuApp",
    bundle_id = "edu.purdue.ecn.das",
    families = [
        "iphone",
        "ipad",
    ],
    infoplists = ["Info.plist"],
    minimum_os_version = MIN_IOS_VERSION,
    provisioning_profile = "//mediapipe/examples/ios:provisioning_profile",
    deps = [
        ":HandTrackingGpuAppLibrary",
        "@ios_opencv//:OpencvFramework",
    ],
)

objc_library(
    name = "HandTrackingGpuAppLibrary",
    srcs = [
        "AppDelegate.m",
        "ViewController.mm",
        "ViewControllerPhrase.mm",
        "AppViewController.mm",
        "main.m",
    ],
    hdrs = [
        "HandTrackingGpuApp-Bridging-Header.h",
        "AppDelegate.h",
        "ViewControllerPhrase.h",
        "ViewController.h",
        "AppViewController.h",      
    ],
    data = [
        "Base.lproj/LaunchScreen.storyboard",
        "Base.lproj/Main.storyboard",
        "//mediapipe/graphs/hand_tracking:hand_tracking_mobile_gpu_binary_graph",
        "//mediapipe/models:hand_landmark.tflite",
        "//mediapipe/models:handedness.txt",
        "//mediapipe/models:palm_detection.tflite",
	    "//mediapipe/models:model_targeted_a.tflite",
        "//mediapipe/models:model_targeted_b.tflite",
        "//mediapipe/models:palm_detection_labelmap.txt",
    ],
    sdk_frameworks = [
        "AVFoundation",
        "CoreGraphics",
        "CoreMedia",
        "UIKit",
    ],
    deps = [
        "//mediapipe/objc:mediapipe_framework_ios",
        "//mediapipe/objc:mediapipe_input_sources_ios",
        "//mediapipe/objc:mediapipe_layer_renderer",
    ] + select({
        "//mediapipe:ios_i386": [],
        "//mediapipe:ios_x86_64": [],
        "//conditions:default": [
            "//mediapipe/graphs/hand_tracking:mobile_calculators",
            "//mediapipe/framework/formats:landmark_cc_proto",
        ],
    }),
)
