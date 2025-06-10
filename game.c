#include "display.h"
#include <stdbool.h>
int make_move(char move, char a[][N], int flag, int *full) {
  int choice = move - '1';
  int row = choice / N;
  int col = choice % N;
  if (a[row][col] == ' ') {
    a[row][col] = (flag == FIR) ? X : O;
    (*full)++;
  } else
    return 1;
  return 0;
}

int pobeda(char a[][3]) {
  for (int i = 0; i < N; i++) {
    if (a[i][0] == 'X' && a[i][1] == 'X' && a[i][2] == 'X')
      return FIR; // Win for X
    if (a[i][0] == 'O' && a[i][1] == 'O' && a[i][2] == 'O')
      return SEC; // Win for O
    if (a[0][i] == 'X' && a[1][i] == 'X' && a[2][i] == 'X')
      return FIR; // Win for X
    if (a[0][i] == 'O' && a[1][i] == 'O' && a[2][i] == 'O')
      return SEC; // Win for O
  }
  // Проверка диагоналей
  if ((a[0][0] == X && a[1][1] == X && a[2][2] == X) ||
      (a[0][2] == X && a[1][1] == X && a[2][0] == X))
    return FIR;
  if ((a[0][0] == O && a[1][1] == O && a[2][2] == O) ||
      (a[0][2] == O && a[1][1] == O && a[2][0] == O))
    return SEC;
  return 0;
}

int check_victory_lanes(char a[][3], char ch) {
  bool cols, rows;
  for (int i = 0; i < N; i++) {
    cols = true, rows = true;
    for (int j = 0; j < N; j++) {
      cols &= (a[i][j] == ch);
      rows &= (a[j][i] == ch);
    }
    if (cols || rows)
      return 1;
  }
  return 0;
}
int check_victory_Diag(char a[][3], char ch) {
  bool toright, toleft;
  toright = true, toleft = true;
  for (int i = 0; i < N; i++) {
    toright &= (a[i][i] == ch);
    toleft &= (a[N - i - 1][i] == ch);
  }
  if (toright || toleft)
    return 1;

  return 0;
}
