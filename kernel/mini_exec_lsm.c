// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/lsm_hooks.h>
#include <linux/binfmts.h>

#include "mini_exec_lsm.h"

// Requirement: Implements bprm_check_security
static int mini_bprm_check_security(struct linux_binprm *bprm)
{
    (void)bprm;
    // Stub: allow everything.
    return 0;
}

static struct security_hook_list mini_hooks[] __lsm_ro_after_init = {
    LSM_HOOK_INIT(bprm_check_security, mini_bprm_check_security),
};

static int __init mini_exec_lsm_init_mod(void)
{
    security_add_hooks(mini_hooks, ARRAY_SIZE(mini_hooks), "mini_exec");
    return 0;
}

static void __exit mini_exec_lsm_exit_mod(void)
{
}

module_init(mini_exec_lsm_init_mod);
module_exit(mini_exec_lsm_exit_mod);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("execguard");
MODULE_DESCRIPTION("mini exec LSM (stub)");
