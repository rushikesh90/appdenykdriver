// SPDX-License-Identifier: GPL-2.0
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#include "exec_events.h"
#include "maps.h"

char LICENSE[] SEC("license") = "GPL";

// Requirement: Uses BPF hash map for allowlist (stub)
struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 1024);
    __type(key, __u8[32]);
    __type(value, __u8);
} allowlist SEC(".maps");

// Requirement: Uses ring buffer for events
struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 1 << 24);
} events SEC(".maps");

// Requirement: Uses SEC("lsm/bprm_check_security")
SEC("lsm/bprm_check_security")
int BPF_PROG(mini_bprm_check_security, struct linux_binprm *bprm)
{
    // Stub: allow everything and optionally emit event.
    struct exec_event *e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
    if (e) {
        e->pid = (__u32)(bpf_get_current_pid_tgid() & 0xffffffff);
        e->tgid = (__u32)(bpf_get_current_pid_tgid() >> 32);
        // filename extraction omitted in stub
        bpf_ringbuf_submit(e, 0);
    }
    return 0;
}
