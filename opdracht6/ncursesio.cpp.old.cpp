// w4.2.2ncursesio
// g++ -Wall -lncurses -o ncursesio ncursesio.cpp hello-xmega-lib.cpp
// ./ncursesio

//TODO: zorg voor de juiste include
#include "ncursesio.hpp"

using namespace std;

int main(int argc, char* argv[]) {

  char sUsbName[] = "/dev/ttyACM0";
  int nKey;
  int ch;
  bool bExit;
  uint8_t nByte;

  // Initialiseren
  initscr();
  clear();
  noecho();
  cbreak();
  raw();
  keypad(stdscr, true);
  nodelay(stdscr, true);

  printw("w4.2.2ncursesio\n\n"); refresh();

  // Initialiseer de correct Xmega-connectie
  printw("> Verbinden: ");
  if (!InitXmegaSerial(sUsbName, B38400, 0)) {
    printw(" fout\n");
  }
  else {
    printw(" OK\n");
  };
  refresh();

  // Blijf opvragen, versturen en tonen
  bExit = false;
  while (!bExit) {
    nKey = getch();
    // Exit is ESC
    if (nKey == ESC) {
      bExit = true;
    };

    // Verwerk de toetsaanslag
    if (nKey != -1) {
	  ch = nKey; endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);
      mvprintw(5,5, "Toets: %d=%c    ", nKey, nKey); refresh();
      XmegaWriteByte((uint8_t*)&nKey);
      while (!XmegaReadByte(&nByte));
      mvprintw(6,5, "Xmega: %d=%c    ", nByte, nByte); refresh();
    };
  };
  
  // Afsluiten
  endwin();
  printf("Afgesloten :-) ");
  if (!CloseXmegaSerial()) {
    printf(" fout\n");
  }
  else {
    printf(" OK\n");
  };

  return 0;
}