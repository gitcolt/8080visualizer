SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

LDFLAGS = -lncurses
CCFLAGS = -g -Wall

db8080: $(OBJ)
	mkdir -p bin
	$(CC) $(LDFLAGS) $(CCFLAGS) -o bin/$@ $^

.PHONY: clean
clean:
	rm -rf $(OBJ) bin/db8080

