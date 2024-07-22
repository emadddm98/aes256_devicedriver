#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 256

int main() {
    int ssh_fd;
    char buffer[BUFFER_SIZE];
    const char *password = "kali";
    const char *raspberry_pi_ip = "192.168.131.141";

    char ssh_cmd_write[BUFFER_SIZE];
    char ssh_cmd_read[BUFFER_SIZE];

    snprintf(ssh_cmd_write, BUFFER_SIZE, "sshpass -p %s ssh pi@%s 'echo \"Hello from PC\" | sudo -S tee /dev/simple_char > /dev/null'", password, raspberry_pi_ip);
    snprintf(ssh_cmd_read, BUFFER_SIZE, "sshpass -p %s ssh pi@%s 'sudo -S cat /dev/simple_char'", password, raspberry_pi_ip);

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
    printf("Reading from the device file:\n");
    while (fgets(buffer, sizeof(buffer)-1, ssh_fd) != NULL) {
        printf("%s", buffer);
    }
    pclose(ssh_fd);

    return 0;
}

