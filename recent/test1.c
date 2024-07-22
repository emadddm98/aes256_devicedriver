#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 256

int main() {
    int ssh_fd, nbytes;
    char buffer[BUFFER_SIZE];
    const char *ssh_cmd_open = "ssh kali@192.168.131.141 'exec 3<>/dev/00.hello2 && echo $? >&3 && exec 3<&-'";
    const char *ssh_cmd_read = "ssh kali@192.168.131.141 'exec 3</dev/00.hello1 && cat <&3'";
    const char *ssh_cmd_write = "ssh kali@192.168.131.141 'echo \"Hello from PC\" > /dev/00.hello0'";

    // Open the device file via SSH
    ssh_fd = popen(ssh_cmd_open, "r");
    if (ssh_fd == NULL) {
        perror("Failed to run ssh command");
        return errno;
    }

    // Write to the device file via SSH
    ssh_fd = popen(ssh_cmd_write, "r");
    if (ssh_fd == NULL) {
        perror("Failed to run ssh command");
        return errno;
    }
    pclose(ssh_fd);

    // Read from the device file via SSH
    ssh_fd = popen(ssh_cmd_read, "r");
    if (ssh_fd == NULL) {
        perror("Failed to run ssh command");
        return errno;
    }

    // Read the output from the SSH command
    while (fgets(buffer, sizeof(buffer)-1, ssh_fd) != NULL) {
        printf("%s", buffer);
    }
    pclose(ssh_fd);

    return 0;
}

