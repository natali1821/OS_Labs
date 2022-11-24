#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <time.h>

void exitFunc() {
	printf("Exit from %d\n", getpid());
}

int main(int argc, char** argv) {
	(void) argc;
	(void) argv;

	int pipedes[2];
	pipe(pipedes);

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
			
			close(pipedes[1]);
			while(read(pipedes[0], buf, 128) != 0) {
				printf("%s", buf);
			}
			close(pipedes[0]);
			
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
			strftime(str, 128, "string passed via pipe: [PARENT] time: %X pid: ", curr);
			snprintf(str1, 56, "%d", getpid());
			strcat(str, str1);
			
			close(pipedes[0]);
			write(pipedes[1], (void*)str, 128);
			close(pipedes[1]);
			
			sleep(8);
			exit(1);
		}	
	}

	return 0;
}