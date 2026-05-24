SRC = main.c tool.c string.c dict.c parse.c convert_string.c convert_string2.c convert_string3.c
OBJ = $(SRC:.c=.o)
PROG = rush-02

CFLAGS = -Wall -Wextra -Werror

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

main.o: convert_string.h dict.h tool.h

tool.o: tool.h

string.o: string.h

dict.o: parse.h dict.h string.h tool.h

parse.o: parse.h dict.h string.h

convert_string.c: convert_string.h dict.h tool.h

convert_string2.c: convert_string.h dict.h tool.h

convert_string3.c: convert_string.h dict.h tool.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PROG)

.PHONY: all clean fclean
