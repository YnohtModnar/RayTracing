CC=g++
CFLAGS= -W -Wall -ansi -pedantic
LDFLAGS= -std=gnu++11 `pkg-config --cflags --libs opencv4` -lassimp -pthread
EXEC=main
SRC= ../src/*.cpp
OBJ= $(SRC:.c=.o)
INC= -I/home/project/triangulation/include/
all: $(EXEC)

main: $(OBJ)
	$(CC) -o  $@ $(INC)  $^ $(LDFLAGS)

main.o: main.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
