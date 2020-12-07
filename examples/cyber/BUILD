load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//tools/bazel:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber",
        "//examples/proto:chatter_cc_proto",
    ],
    data = [
        "//cyber/conf:compute_sched_conf",
        ],

)

cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber",
        "//examples/proto:chatter_cc_proto",
    ],
)

cc_binary(
    name = "parameter",
    srcs = ["parameter.cc"],
    deps = [
        "//cyber",
        "//cyber/parameter",
    ],
)

cc_binary(
    name = "service",
    srcs = ["service.cc"],
    deps = [
        "//cyber",
        "//examples/proto:driver_cc_proto",
    ],
)

cc_binary(
    name = "record",
    srcs = ["record.cc"],
    deps = [
        "//cyber",
        "//cyber/proto:record_cc_proto",
    ],
)

cpplint()
