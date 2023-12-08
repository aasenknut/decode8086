CFLAGS=-Wall -Wextra -Werror -ggdb


main: main.c
	gcc $(CFLAGS) -o main main.c data.c decode.c bit_mask.c && ./main
