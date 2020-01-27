run these commands

to build:

	bazel build -c opt --define MEDIAPIPE_DISABLE_GPU=1     mediapipe/examples/desktop/hand_tracking:hand_tracking_cpu

to run:

	GLOG_logtostderr=1 bazel-bin/mediapipe/examples/desktop/hand_tracking/hand_tracking_cpu     --calculator_graph_config_file=mediapipe/graphs/hand_tracking/hand_tracking_desktop_live.pbtxt
