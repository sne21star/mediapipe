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
    ],
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