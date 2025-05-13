#include "display.h"
#include <string.h>
void print_mesg(const char *mesg, int height, int width) {

  mvprintw(height, (width - strlen(mesg)) / 2, mesg);
}
void print_field(char (*a)[N], int start_y, int start_x) {

  for (int i = 0; i < N + 1; i++) {
    for (int j = 0; j < N + 1; j++) {
      mvaddch(start_y + i * 2, start_x + j * 4, '+'); // Углы
      if (j < N) {
        mvaddch(start_y + i * 2, start_x + j * 4 + 1,
                '-'); // Горизонтальные линии
        mvaddch(start_y + i * 2, start_x + j * 4 + 2,
                '-'); // Горизонтальные линии
        mvaddch(start_y + i * 2, start_x + j * 4 + 3,
                '-'); // Горизонтальные линии
      }
    }
    if (i < N) {
      for (int j = 0; j < N + 1; j++) {
        mvaddch(start_y + i * 2 + 1, start_x + j * 4,
                '|'); // Вертикальные линии
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (a[i][j] == X) {
        attron(COLOR_PAIR(1)); // Включаем цветовую пару для X (синий)
        mvaddch(start_y + i * 2 + 1, start_x + j * 4 + 2, a[i][j]);
        attroff(COLOR_PAIR(1)); // Выключаем цветовую пару
      } else if (a[i][j] == O) {
        attron(COLOR_PAIR(2)); // Включаем цветовую пару для O (красный)
        mvaddch(start_y + i * 2 + 1, start_x + j * 4 + 2, a[i][j]);
        attroff(COLOR_PAIR(2)); // Выключаем цветовую пару
      } else {
        mvaddch(start_y + i * 2 + 1, start_x + j * 4 + 1, ' '); // Пустое место
      }
    }
  }
}
