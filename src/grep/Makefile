CC = gcc -Werror -Wall -Wextra
FILES = s21_grep.c

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(FILES) -o s21_grep

clean:
	rm -rf *.o *.a s21_grep

rebuild: clean all