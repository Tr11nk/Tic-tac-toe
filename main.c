#include "display.h"
#include <ncurses.h>
#define OFFSET 1
#define MESG_OFF (height / 2) - 6
#define NUM_ELEM_MASS N *N
int main() {
  initscr();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  cbreak();
  noecho();
  curs_set(0);
  int full = 0;
  char a[N][N] = {
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
  };
  char kletka;
  int height, width;
  getmaxyx(stdscr, height, width);
  const char *mesgp = "No right symbol!";
  print_mesg("This is tic-tac-toe", MESG_OFF - 6, width);
  refresh();
  int start_y = (height - (N * 2 - 1)) / 2; // Центр по вертикали
  int start_x = (width - (N * 4 - 1)) / 2;  // Центр по горизонтали
  int flag = FIR;
  while (1) {
    print_mesg("This is tic-tac-toe", MESG_OFF - 6, width);
    if (flag == FIR) {
      if (full == NUM_ELEM_MASS) {
        break;
      }
      print_mesg("Player 1 move ", MESG_OFF - 4, width);
      print_mesg("Enter index of cell", MESG_OFF - 2, width);
      print_field(a, start_y, start_x);
      refresh();
      kletka = getchar();
      if (kletka < '1' || kletka > '9') {
        print_mesg(mesgp, MESG_OFF, width);
        refresh();
        continue;
      } else if (make_move(kletka, a, flag, &full) == 0) {
        clear();
        switch (check_victory_Diag(a, X) || check_victory_lanes(a, X)) {
        case 0:
          flag = SEC;
          break;
        case 1:
          print_mesg("1 player is the winner!", MESG_OFF, width);
          print_field(a, start_y, start_x);
          refresh();
          goto Finish;
        default:
        }
      } else {
        print_mesg("Sorry the cell is occupied!", MESG_OFF, width);
        refresh();
        continue;
      }
    } else {
      if (full == NUM_ELEM_MASS) {
        break;
      }
      print_mesg("Player 2 move", MESG_OFF - 4, width);
      print_mesg(" Enter index of cell", MESG_OFF - 2, width);
      print_field(a, start_y, start_x);
      refresh();
      kletka = getchar();
      if (kletka < '1' || kletka > '9') {
        print_mesg(mesgp, MESG_OFF, width);
        refresh();
        continue;
      } else if (make_move(kletka, a, flag, &full) == 0) {
        clear();
        switch (check_victory_Diag(a, O) || check_victory_lanes(a, O)) {
        case 0:
          flag = FIR;
          break;
        case 1:
          print_mesg("2 player is the winner!", MESG_OFF, width);
          print_field(a, start_y, start_x);
          refresh();
          goto Finish;
        default:
        }
      } else {
        print_mesg("Sorry the cell is occupied!", MESG_OFF, width);
        refresh();
        continue;
      }
    }
  }
Tie:
  print_mesg("It`s a tie no more available cells to play!", MESG_OFF, width);
  print_field(a, start_y, start_x);
  refresh();
  getchar();
  endwin();
  return 0;
Finish:
  getchar();
  endwin();
  return 0;
}
