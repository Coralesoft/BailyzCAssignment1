CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o random.o mappingFunc.o playerMovement.o terminal.o newsleep.o carMovement.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c random.h mapping.h player.h terminal.h newsleep.h carMovement.h
	$(CC) $(CFLAGS) main.c -c

random.o : random.c random.h
	$(CC) $(CFLAGS) random.c -c

mappingFunc.o : mappingFunc.c mapping.h random.h
	$(CC) $(CFLAGS) mappingFunc.c -c

playerMovement.o : playerMovement.c player.h mapping.h
	$(CC) $(CFLAGS) playerMovement.c -c

carMovement.o : carMovement.c carMovement.h
	$(CC) $(CFLAGS) carMovement.c -c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

newsleep.o : newsleep.c newsleep.h
	$(CC) $(CFLAGS) newsleep.c -c



clean :
	rm -f $(EXEC) $(OBJ)
