cc_library(
    name = "hand-gesture-recognition-calculator",
    srcs = ["hand-gesture-recognition-calculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:landmark_cc_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/formats:rect_cc_proto",
        "//mediapipe/framework/port:ret_check",
        "//mediapipe/util:resource_util",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        ]+ select({
        "//mediapipe:android": [
            "//mediapipe/util/android/file/base",
            "@org_tensorflow//tensorflow/lite/delegates/nnapi:nnapi_delegate",
        ],
        "//mediapipe:apple": [
            "//mediapipe/util/android/file/base",
        ],
        "//mediapipe:macos": [
            "//mediapipe/framework/port:file_helpers",
        ],
        "//conditions:default": [
            "//mediapipe/framework/port:file_helpers",
        ],
    }),

    alwayslink = 1,
)

cc_library(
    name = "string_to_render_data_calculator",
    srcs = ["string_to_render_data_calculator.cc"],
    visibility = ["//visibility:public"],
    deps =[
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/port:ret_check",
        "//mediapipe/util:render_data_cc_proto",
        "@com_google_absl//absl/memory",
    ],
    alwayslink = 1,
)

cc_library(
    name = "z_score_calculator",
    srcs = ["z_score_calculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:landmark_cc_proto",
        "//mediapipe/framework/formats:location_data_cc_proto",
        "//mediapipe/framework/formats:detection_cc_proto",
    ],
    alwayslink = 1
)

