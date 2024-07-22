#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>
#include <libssh/sftp.h>

#define USERNAME "kali"  // Replace with your Raspberry Pi username
#define PASSWORD "kali"  // Replace with your actual password
#define RPI_IP "192.168.131.141"  // Replace with your Raspberry Pi's IP address
#define MESSAGE "Hello from AES256 group!"

void execute_command(ssh_session session, const char *command) {
    ssh_channel channel;
    int rc;
    char buffer[256];
    unsigned int nbytes;

    channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Error creating channel\n");
        exit(EXIT_FAILURE);
    }

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(session));
        exit(EXIT_FAILURE);
    }

    rc = ssh_channel_request_exec(channel, command);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error requesting command execution: %s\n", ssh_get_error(session));
        exit(EXIT_FAILURE);
    }

    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    if (nbytes < 0) {
        fprintf(stderr, "Error reading from channel: %s\n", ssh_get_error(session));
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
}

int main() {
    ssh_session session;
    int rc;
    char command[512];

    // Initialize SSH session
    session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creating SSH session\n");
        return EXIT_FAILURE;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, RPI_IP);
    ssh_options_set(session, SSH_OPTIONS_USER, USERNAME);

    // Connect to the Raspberry Pi
    rc = ssh_connect(session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to %s: %s\n", RPI_IP, ssh_get_error(session));
        ssh_free(session);
        return EXIT_FAILURE;
    }

    // Authenticate with the password
    rc = ssh_userauth_password(session, NULL, PASSWORD);
    if (rc != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error authenticating: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    // Construct the command to write to the kernel log
    snprintf(command, sizeof(command),
             "echo \"%s\" | sudo tee /dev/kmsg > /dev/null",
             MESSAGE);

    // Execute the command on the Raspberry Pi
    execute_command(session, command);

    // Disconnect and clean up
    ssh_disconnect(session);
    ssh_free(session);

    return EXIT_SUCCESS;
}

