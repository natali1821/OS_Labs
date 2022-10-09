.PHONY: clean

all: ls.o functions.o
	gcc ls.o functions.o -o ls -Wall -Wextra -Werror

ls.o: ls.c
	gcc -c ls.c

functions.o: functions.c
	gcc -c functions.c 

clean:
	rm *.o ls