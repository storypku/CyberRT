load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/bazel:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base",
    testonly = True,
    hdrs = ["base.h"],
)

cc_binary(
    name = "libplugin1.so",
    testonly = True,
    srcs = ["plugin1.cc"],
    linkshared = True,
    linkstatic = False,
    deps = [
        ":base",
        "//cyber/class_loader:class_loader_manager",
    ],
)

cc_binary(
    name = "libplugin2.so",
    testonly = True,
    srcs = ["plugin2.cc"],
    linkshared = True,
    linkstatic = False,
    deps = [
        ":base",
        "//cyber/class_loader:class_loader_manager",
    ],
)

cpplint()
