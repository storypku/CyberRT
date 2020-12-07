load("@rules_python//python:defs.bzl", "py_binary")

package(
    default_visibility = ["//visibility:public"],
)

py_binary(
    name = "cyber_channel",
    srcs = ["cyber_channel.py"],
    deps = [
        "//cyber/proto:role_attributes_py_pb2",
        "//cyber_py3:cyber",
        "//cyber_py3:cyber_time",
    ],
)

py_binary(
    name = "cyber_launch",
    srcs = ["cyber_launch.py"],
)

py_binary(
    name = "cyber_node",
    srcs = ["cyber_node.py"],
    deps = [
        "//cyber_py3:cyber",
    ],
)

py_binary(
    name = "cyber_service",
    srcs = ["cyber_service.py"],
    deps = [
        "//cyber_py3:cyber",
    ],
)
