#pragma once

#include <linux/types.h>

struct exec_event {
    __u32 pid;
    __u32 tgid;
    char filename[256];
};
