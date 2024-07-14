#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define LM_MAGIC_NUMBER 0xFF
#define SET _IOW(LM_MAGIC_NUMBER, 1, int)
#define RESET _IOW(LM_MAGIC_NUMBER, 2, int)

int main() {

	int fd = open ("/dev/LM_module",O_RDWR	);
	if (fd < 0) {
		perror ("Unable to open device");
	}

	int arg;
	arg = 1;

	printf ("Command 1 %ld\n", SET);
	printf ("Command 2 %ld\n", RESET);

	long r =  ioctl(fd, SET, &arg);
	arg=2;
	r =  ioctl(fd, RESET, &arg);

	if (r < 0) {
		perror ("Unable to open device");
	}

	int buf;
	r = read (fd, &buf, sizeof(int));

	write (fd, &buf, sizeof(int));	

	close(fd);

}
