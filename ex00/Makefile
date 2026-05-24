SRC = main.c tool.c string.c dict.c parse.c convert_string.c
OBJ = $(SRC:.c=.o)
PROG = rush-02

CFLAGS = -Wall -Wextra -Werror

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

main.o: dict.h tool.h

tool.o: tool.h

string.o: string.h

dict.o: parse.h dict.h string.h tool.h

parse.o: parse.h dict.h string.h

convert_string.c: tool.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PROG)

.PHONY: all clean fclean
