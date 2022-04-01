

# Makefile Rogue-Like

OBJ=obj/
INC=inc/
SRC=src/

CC=gcc
CFLAGS=-ansi -Wall #-fsanitize=address
OBJE=$(OBJ)main.o $(OBJ)player.o $(OBJ)graphique.o $(OBJ)terrain.o $(OBJ)liste.o $(OBJ)game.o $(OBJ)monster.o $(OBJ)treasure.o $(OBJ)objet.o
EXEC=rogue

all: makedirs $(EXEC)

makedirs:
	@mkdir -p obj

$(EXEC): $(OBJE)
	$(CC) -o $@ $^ $(CFLAGS) -lMLV

$(OBJ)main.o: $(SRC)main.c $(INC)player.h $(INC)graphique.h $(INC)terrain.h $(INC)liste.h $(INC)game.h $(INC)monster.h $(INC)treasure.h $(INC)objet.h

$(OBJ)player.o: $(SRC)player.c $(INC)player.h

$(OBJ)terrain.o: $(SRC)terrain.c $(INC)terrain.h

$(OBJ)graphique.o: $(SRC)graphique.c $(INC)graphique.h $(SRC)terrain.c $(INC)terrain.h

$(OBJ)liste.o: $(SRC)liste.c $(INC)liste.h

$(OBJ)game.o: $(SRC)game.c $(INC)game.h

$(OBJ)monster.o: $(SRC)monster.c $(INC)monster.h

$(OBJ)treasure.o: $(SRC)treasure.c $(INC)treasure.h

$(OBJ)objet.o: $(SRC)objet.c $(INC)objet.h

$(OBJ)monster.o: $(SRC)monster.c $(INC)monster.h

$(OBJ)%.o:
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ)*.o
	rm -f $(EXEC)
	rmdir obj