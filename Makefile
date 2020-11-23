CC = gcc

INCLUDE_PATHS = -I/usr/include/x86_64-linux-gnu/SDL2
LIBRARY_PATHS = -L/usr/lib/x86_64-linux-gnu

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2

OBJS = main.o
OBJ_NAME = fire_arena

$(OBJ_NAME) : $(OBJS)
	$(CC) $(OBJS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)

objs/main.o : main.c
	$(CC) -c main.c -o objs/main.o

clean :
	rm objs/*.o
	rm $(OBJ_NAME)
