#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define N 3
#define FIR 1
#define SEC 2
#define OFFSET 1
#define POB_1 3
#define POB_2 6
#define X 'X'
#define O 'O'
#define MESG_OFF (height/2)-6


void print_mesg(const char *mesg, int height, int width);


void print_field(char (*a)[N], int start_y, int start_x);

int make_move(char move,char a[][3],int flag);

int pobeda(char a[][3]);


int main()
{
    curs_set(1);
    initscr();
        cbreak();
    noecho();
  char  a[N][N]=
    {   {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };
    char kletka;
    int height, width;
    getmaxyx(stdscr, height, width);
    const char *mesgp="No right symbol!";
   
    print_mesg("This is tic-tac-toe",MESG_OFF-6,width);
    refresh();
    int start_y = (height - (N * 2 - 1)) / 2; // Центр по вертикали
    int start_x = (width - (N * 4 - 1)) / 2;  // Центр по горизонтали
    int flag=FIR;
    while(1)
    {
    print_mesg("This is tic-tac-toe",MESG_OFF-6,width);
        if(flag==FIR)
        {
          //  printf("Игрок 1 ходит\nВведите номер клетки\n");
          print_mesg("Player 1 move ",MESG_OFF-4,width);
          
          print_mesg(" Enter index of cell",MESG_OFF-2,width);
            print_field(a,start_y,start_x);
refresh();
            kletka=getchar();
           
            if(kletka<'1' || kletka>'9'){
             //   printf("Неккоретный ввод\n");
             print_mesg(mesgp,MESG_OFF,width);
             refresh();
                continue;
            }
            else 
                if(make_move(kletka,a,flag)==0){
                    clear();
                    switch(pobeda(a))

                    {
                        case 0:
                            flag=SEC;
                            break;
                        case 1:
                          //  printf("Победил 1 игрок!\n");
                            print_mesg("WINNER 1 PLAYER!",MESG_OFF,width);
                            print_field(a,start_y,start_x);
refresh();
                            goto Finish;
                        default:

                    }
                }
                else
                {
                    print_mesg("Sorry the cell is occupied!",MESG_OFF,width);
                    refresh();
                    continue;
                }
        }
        else
        {
          print_mesg("Player 2 move",MESG_OFF-4,width);
          print_mesg(" Enter index of cell",MESG_OFF-2,width);
            print_field(a,start_y,start_x);
            refresh();
            kletka=getchar();
            if(kletka<'1' || kletka>'9'){
            //    printf("Неккоретный ввод\n");
                print_mesg(mesgp,MESG_OFF,width);
                refresh();
                continue;
            }
            else 
                if(make_move(kletka,a,flag)==0){
                    clear();
                    switch(pobeda(a))
                    {
                        case 0:
                            flag=FIR;
                            break;
                        case 2:
                         print_mesg("2 player is the winner!",MESG_OFF,width);
                         print_field(a,start_y,start_x);
refresh();
                            goto Finish;
                        default:

                    }
                }
                else
                {
                    print_mesg("Sorry the cell is occpueid!",MESG_OFF,width);
refresh();
                    continue;
                }
                
        }
        


    }
Finish:
    getchar();
    endwin();
    return 0;


}



int make_move(char move,char a[][N],int flag)
{
    int choice = move - '1';
    int row = choice / N;
    int col = choice % N;
    if (a[row][col] == ' ')    
        a[row][col]=(flag==FIR)? 'X' : 'O' ;

    else
        return 1;
            
    return 0;
}


void print_field(char (*a)[N],int start_y,int start_x)
{
   
    for (int i = 0; i < N+1 ; i++) {
        for (int j = 0; j < N+1 ; j++) {
            mvaddch(start_y + i * 2, start_x + j * 4, '+'); // Углы
            if (j < N ) {
                mvaddch(start_y + i * 2, start_x + j * 4+1 , '-'); // Горизонтальные линии
                mvaddch(start_y + i * 2, start_x + j * 4 + 2, '-'); // Горизонтальные линии
                mvaddch(start_y + i * 2, start_x + j * 4 + 3, '-'); // Горизонтальные линии
            }
        }
        if (i < N ) {
            for (int j = 0; j < N+1; j++) {
                mvaddch(start_y + i * 2 + 1, start_x + j * 4, '|'); // Вертикальные линии
            }
        }
    }
    
    for (int i = 0; i < N ; i++) {
        for (int j = 0; j < N ; j++) {
            if (a[i][j] !=  ' ') {
              mvaddch(start_y + i * 2 + 1, start_x + j * 4 + 2, a[i][j]); // Символ (X или O)
            } else {
                mvaddch(start_y + i * 2 + 1, start_x + j * 4 + 1, ' '); // Пустое место
            }
        }
    }
    refresh();
}


int pobeda(char a[][3])
{
          for (int i = 0; i < N; i++) {
        if (a[i][0] == 'X' && a[i][1] == 'X' && a[i][2] == 'X') return FIR; // Win for X
        if (a[i][0] == 'O' && a[i][1] == 'O' && a[i][2] == 'O') return SEC; // Win for O
        if (a[0][i] == 'X' && a[1][i] == 'X' && a[2][i] == 'X') return FIR; // Win for X
        if (a[0][i] == 'O' && a[1][i] == 'O' && a[2][i] == 'O') return SEC; // Win for O
    } 
    // Проверка диагоналей
    if ((a[0][0]==X && a[1][1]==X && a[2][2] == X) || 
        (a[0][2]==X && a[1][1]==X && a[2][0] == X))
        return FIR;
    if ((a[0][0]==O && a[1][1]==O && a[2][2]==O) || 
        (a[0][2]==O && a[1][1]==O && a[2][0]==O))
        return SEC;
    return 0;
}

void print_mesg(const char *mesg,int height, int width)
{
    mvprintw(height ,(width-strlen(mesg)) / 2, mesg);
}
