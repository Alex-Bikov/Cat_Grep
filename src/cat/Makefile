CC = gcc -Werror -Wall -Wextra
FILES = s21_cat.c

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(FILES) -o s21_cat

clean:
	rm -rf *.o *.a s21_cat

rebuild: clean all
