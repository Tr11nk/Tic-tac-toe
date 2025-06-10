CC=gcc
CONS=cons.o
MAIN=main.o
GAME=game.o
TARGET=tic_tac_toe
all: $(TARGET)
$(CONS): cons.c
	$(CC) -c -o $(CONS) cons.c
$(MAIN): main.c
	$(CC) -c -o $(MAIN) main.c
$(GAME): game.c
	$(CC) -c -o $(GAME) game.c
tic-tac-toe: $(CONS) $(MAIN) $(GAME)
	$(CC)   $(GAME) $(CONS) $(MAIN)  -o tic_tac_toe -lncurses

clean:
	rm -f $(CONS) $(MAIN) $(GAME)
