package(default_visibility = ["//visibility:public"])

exports_files(["cyber.pb.conf"])

filegroup(
    name = "control_sched_conf",
    srcs = [
        "control_sched.conf",
        "control_sched_choreography.conf",
        "control_sched_classic.conf",
    ],
)

filegroup(
    name = "compute_sched_conf",
    srcs = [
        "compute_sched.conf",
        "compute_sched_choreography.conf",
        "compute_sched_classic.conf",
    ],
)

filegroup(
    name = "example_sched_conf",
    testonly = True,
    srcs = [
        "example_sched_choreography.conf",
        "example_sched_classic.conf",
    ],
)
