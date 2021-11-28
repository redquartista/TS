CC = gcc
CFLAGS = -Wall -Werror
OBJ = ts_demux
OPTFLAGS = -O0
STD = c11
CFLAGS += -std=$(STD) -ggdb $(OPTFLAGS)
INCLUDES = -Iincludes

default: all

clean:
	rm $(OBJ) *.o

all:
	$(CC) $(INCLUDES) $(CFLAGS) -o $(OBJ)  src/main.c includes/*.c
	
