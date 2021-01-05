#include<ncurses.h>
#include<pthread.h>
#include<unistd.h>
#include<locale.h>
#include"sfen2bod.h"

static int X,Y; // screen size

// 1:OK / 0:NG
static int checkEnvironment ( void ) {
  if ( !can_change_color() ) {
    printw("This application require that terminal supports change color");
    printw("Your terminal NOT support change color.");
    return 1;
  }
  return 0;
}

static void initialize ( void ) {
  setlocale(LC_ALL,"");
  initscr();
  start_color();
  noecho();
  cbreak();
  //curs_set(0);
  keypad(stdscr,TRUE);
  mousemask(ALL_MOUSE_EVENTS,NULL);
  // NOTE getmaxyx is a MACRO, NOT a function.
  // So use Y and X without address operator '&'.
  getmaxyx(stdscr,Y,X);
  timeout(50); // 50ms = 20Hz;
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_WHITE,COLOR_YELLOW);
  init_pair(3,COLOR_BLACK,COLOR_YELLOW);
  // COLOR_BLACK   /usr/include/ncurses.h 
  // COLOR_CYAN    /usr/include/ncurses.h 
  // COLOR_WHITE   /usr/include/ncurses.h 
  // COLOR_PAIR    /usr/include/ncurses.h 
  // COLORS        /usr/include/ncurses.h 
  // COLOR_PAIRS   /usr/include/ncurses.h 
  // COLOR_RED     /usr/include/ncurses.h 
  // COLOR_GREEN   /usr/include/ncurses.h 
  // COLOR_YELLOW  /usr/include/ncurses.h 
  // COLOR_BLUE    /usr/include/ncurses.h
  // COLOR_MAGENTA /usr/include/ncurses.h 
}

static void terminate ( void ) {
  endwin();
}


int main ( int args, char *argv[] ) {
  char sfen[]="5k1nl/5sgb1/8p/5p1P1/6Gp1/9/6N1P/9/8L b P 1";
  char bod[4096]="";
  WINDOW *bodWindow;
  int px,py;
  px = py = 0;
  sfen2bod(sfen,bod);
  printf(bod);
  sleep(1);
  if ( !checkEnvironment() ) {
    return 1;
  }
  initialize();
  bodWindow=subwin(stdscr,16,32,2,10);
  wbkgd(bodWindow,COLOR_PAIR(2));
  mvwprintw(bodWindow,0,0,bod);
  move(py,px);
  refresh();
  while ( 1 ) {
    int ch = getch();
    if ( ch == 'q' ) break;
    if ( ch == KEY_MOUSE ) {
      MEVENT e;
      if ( getmouse(&e) == OK ) {
        px = e.x;
        py = e.y;
        //clear();
        ////mvprintw(py,px,bod);
        //mvwprintw(bodWindow,0,0,bod);
        //refresh();
      }
    } else {
      switch ( ch ) {
        case KEY_UP     : py--; break;
        case KEY_DOWN   : py++; break;
        case KEY_RIGHT  : px++; break;
        case KEY_LEFT   : px--; break;
      }
    }
    if ( px <   0 ) px =   0;
    if ( px > X-1 ) px = X-1;
    if ( py <   0 ) py =   0;
    if ( py > Y-1 ) py = Y-1;
    mvwprintw(bodWindow,0,0,bod);
    refresh();
    move(py,px);
  }
  terminate();
  return 0;
}

