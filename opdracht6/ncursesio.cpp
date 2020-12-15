// Embedded Systems | HvA 2020
// Opdracht 4 week 2
//
// Rowan Bolding
// Bart-Jan van Strien
//
// Compile: g++ -Wall -o ncurses ncurses.cpp -lncurses
// Run    : ./ncurses
#define SELECTED_WIN 1
#define UNSELECTED_WIN 2

#include "ncursesio.hpp"

using namespace std;

int main()
{
    char sUsbName[] = "/dev/ttyACM0";
    int nKey;
    int ch;
    bool bExit;
    uint8_t nByte;

    char string[100];

    printw("w4.2.2ncursesio\n\n"); refresh();

    WINDOW * mainwin, * childwin, * childwin2;

    // init main window;
    int max_x;
    int max_y;
    if ( (mainwin = initscr()) == NULL )
    {
        fprintf(stderr, "ERROR INIT NCURSES\n");
        exit(EXIT_FAILURE);
    }
    box(mainwin, '|', '-');

    getmaxyx(stdscr,max_y,max_x);
    int width = max_x, height = max_y;
    int halfwidth = width / 2;
    int halfheight = height / 2;

    noecho();
    start_color();
    keypad(mainwin, TRUE);

    init_pair(1, COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_WHITE,COLOR_BLACK);

    // init child window
    attron(COLOR_PAIR(SELECTED_WIN));
    childwin = subwin(mainwin, height - 2, halfwidth - 2, 1, 2);
    box(childwin, '|', '-');
    attroff(COLOR_PAIR(SELECTED_WIN));
    mvwaddstr(childwin, 1, 0, "Verbinden");
  
    // init child2 window
    attron(COLOR_PAIR(UNSELECTED_WIN));
    childwin2 = subwin(mainwin, height - 2, halfwidth - 2, 1, halfwidth + 1);
    box(childwin2, '|', '-');
    attroff(COLOR_PAIR(UNSELECTED_WIN));
    mvwaddstr(childwin2, 6, 7, "Verbinden...");
    //mvwaddstr(childwin2, 7, 11, "met XMEGA...");
    //mvwaddstr(childwin2, 8, 8, "Rowan Bolding");
    //mvwaddstr(childwin2, 9, 5, "Bart-Jan van Strien");
    refresh();
    wmove(childwin,1,1);
    wclrtoeol(childwin);
    attron(COLOR_PAIR(UNSELECTED_WIN));
    box(childwin, '|', '-');
    attroff(COLOR_PAIR(UNSELECTED_WIN));
    // Initialiseer de correct Xmega-connectie
    if (!InitXmegaSerial(sUsbName, B38400, 0)) {
      //fout
      mvwaddstr(childwin, 1, 3, "VERBINDING MISLUKT");
    }
    else {
      //goei
      mvwaddstr(childwin, 1, 3, "Verbonden");
    };
  wrefresh(childwin);
    
    // wait for user input before exit
    bExit = false;
    while (!bExit) {
        nKey = getch();
        // Exit is ESC
        if (nKey == ESC) {
        bExit = true;
        };


        if (nKey != -1) {
            ch = nKey; 
            wmove(childwin,3,1);
            wclrtoeol(childwin);
            wmove(childwin,4,1);
            wclrtoeol(childwin);
            wmove(childwin,5,1);
            wclrtoeol(childwin);
            sprintf(string,"KEY NAME : %s - %d\n", keyname(ch),ch);
            mvwaddstr(childwin, 3, 3, string);
            sprintf(string,"Toets: %d=%c    ", nKey, nKey);
            mvwaddstr(childwin, 4, 3, string);
            XmegaWriteByte((uint8_t*)&nKey);
            while (!XmegaReadByte(&nByte));
            sprintf(string,"Xmega: %d=%c    ", nByte, nByte);
            mvwaddstr(childwin, 5, 3, string);
            wrefresh(childwin);
        };


  };
	
    // EXIT!
    CloseXmegaSerial();
    delwin(childwin);
    delwin(childwin2);
    delwin(mainwin);
    endwin();
    refresh();
    return EXIT_SUCCESS;
}