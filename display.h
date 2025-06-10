#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#define N 3
#define X_PAIR 1
#define O_PAIR 2
#define X 'X'
#define O 'O'
#define FIR 1
#define SEC 2
void print_mesg(const char *mesg, int height, int width);
void print_field(char (*a)[N], int start_y, int start_x);
int check_victory_lanes(char a[][3], char ch);
int check_victory_Diag(char a[][3], char ch);
int make_move(char move, char a[][N], int flag, int *full);
#endif
