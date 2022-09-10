.PHONY: clean

cat: cat.o cat_functions.o
	gcc cat.o cat_functions.o -o cat -Wall -Wextra -Werror

cat.o: cat.c
	gcc -c cat.c

cat_functions.o: cat_functions.c
	gcc -c cat_functions.c

clean:
	rm *.o cat