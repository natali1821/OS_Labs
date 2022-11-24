#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

void exitFunc() {
	printf("Exit from %d\n", getpid());
}

int main(int argc, char** argv) {
	(void) argc;
	(void) argv;

	if ((mkfifo("./fifo_file", 0777) < 0) && (errno != EEXIST)) {
		int error = errno;
		fprintf(stderr, "Error %d: %s", error, strerror(error));
		exit(1);
	}

	int fd;

	atexit(exitFunc);

	struct timespec ts;
	struct tm* curr;

	pid_t pid = fork();
	switch(pid) {
		case -1: {
			fprintf(stderr, "Fork error %d", errno);
			exit(-1);
		}
		case 0: {
			sleep(6);
			printf("[CHILD] PID: %4d PPID: %4d %d\n", getpid(), getppid(), errno);
			char buf[128];
			int len;

			fd = open("./fifo_file", O_RDONLY);
			if (fd  == -1) {
				int error = errno;
				fprintf(stderr, "Error %d: %s", error, strerror(error));
				exit(1);
			}
			while((len = read(fd, buf, 128)) != 0) {
				printf("%s", buf);
			}
			close(fd);
			
			clock_gettime(CLOCK_REALTIME, &ts);
			curr = localtime(&ts.tv_sec);
			strftime(buf, 128, "\n[CHILD] time: %X\n", curr);
			printf("%s", buf);
			exit(1);
		}	
		default: {
			printf("[PARENT] PID: %4d PPID: %4d %d\n", getpid(), getppid(), errno);
			char str[128];
			char str1[56];
			
			clock_gettime(CLOCK_REALTIME, &ts);
			curr = localtime(&ts.tv_sec);
			strftime(str, 128, "string passed via named pipe: [PARENT] time: %X pid: ", curr);
			snprintf(str1, 56, "%d", getpid());
			strcat(str, str1);
			
			fd = open("./fifo_file", O_WRONLY);
			if (fd  == -1) {
				int error = errno;
				fprintf(stderr, "Error %d: %s", error, strerror(error));
				exit(1);
			}
			write(fd, (void*)str, 128);
			close(fd);
			
			sleep(8);
			exit(1);
		}	
	}

	return 0;
}