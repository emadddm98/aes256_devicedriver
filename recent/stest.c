#include <stdio.h>
#include <stdlib.h>

#define PASSWORD "kali"  // Replace with your actual password
#define RPI_IP "192.168.131.141"  // Replace with your Raspberry Pi's IP address
#define COMMAND "dmesg"  // Replace with your arbitrary superuser command

int main() {
    char command[1024];

    // Construct the SSH command with sshpass to execute a superuser command
    snprintf(command, sizeof(command),
             "sshpass -p %s ssh kali@%s 'echo %s | sudo -S %s'",
             PASSWORD, RPI_IP, PASSWORD, COMMAND);

    // Execute the constructed command
    int ret = system(command);
    if (ret == -1) {
        perror("Failed to execute command");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

