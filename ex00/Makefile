SRC = main.c tool.c string.c dict.c
OBJ = $(SRC:.c=.o)
PROG = rush-02

CFLAGS = -Wall -Wextra -Werror

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

tool.o: tool.h

string.o: string.h

dict.o: dict.h string.h tool.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PROG)

.PHONY: all clean fclean
