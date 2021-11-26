CC = gcc
CFLAGS = -Wall
OBJ = ts_separator
OPTFLAGS = -O0
STD = c11
CFLAGS += -std=$(STD) -ggdb $(OPTFLAGS)
INCLUDES = -Iincludes

clean:
	rm $(OBJ) *.o

all:
	$(CC) $(INCLUDES) $(CFLAGS) -o $(OBJ)  src/main.c includes/*.c
	
