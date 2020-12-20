// Embedded Systems | HvA 2020
// Opdracht 4 week 2
//
// Rowan Bolding
// Bart-Jan van Strien
//
// Compile: g++ -Wall -o ncurses ncurses.cpp -lncurses
// Run    : ./ncurses
#include "ncursesio.hpp"

using namespace std;

//WINDOW CLASS POINTERS
WINDOW * mainwin, * childWin_1, * childWin_2, * childwinh;

//Main window parameters:
static int width; 
static int height;
static int halfwidth;
static int max_x;
static int max_y;


/*********************************************************************************
PROGRAM MANAGER
*********************************************************************************/
uint8_t activeProgramIndex = PROGRAM_1;

uint8_t nextActiveProgram(void){
	activeProgramIndex++;
	if(activeProgramIndex == PROGRAM_NUM) activeProgramIndex = PROGRAM_1;
	return activeProgramIndex;
}

uint8_t previousActiveProgram(void){
	if(activeProgramIndex == PROGRAM_1) activeProgramIndex = PROGRAM_NUM-1;
	activeProgramIndex--;
	return activeProgramIndex;
}

bool closeCurrentProgram(uint8_t program){
	switch(activeProgramIndex){
		case PROGRAM_1:
			closeProgram_1(childWin_1);
		break;
	case PROGRAM_2:
			closeProgram_2(childWin_2);
		break;
	}
	return false;
}

bool manager(int Key){
	if(Key == SHIFT_RIGHT){
		closeCurrentProgram(activeProgramIndex);
		nextActiveProgram();
		return false;
	}
	if(Key == SHIFT_LEFT){
		closeCurrentProgram(activeProgramIndex);
		previousActiveProgram();
		return false;
	}
	
	switch (activeProgramIndex){
		case PROGRAM_1:
			program_1(Key, childWin_1);
			break;
		case PROGRAM_2:
			program_2(Key, childWin_2);
			break;
	}
	return false;
}

/*********************************************************************************
WINDOW MANAGER
*********************************************************************************/
int initMainWindow(){

    if ( (mainwin = initscr()) == NULL )
    {
        fprintf(stderr, "ERROR INIT NCURSES\n");
        exit(EXIT_FAILURE);
    }
    box(mainwin, '|', '-');

    getmaxyx(stdscr,max_y,max_x);
    width = max_x;
	height = max_y;
    halfwidth = width / 2;

    noecho();
    start_color();
    keypad(mainwin, TRUE);

    init_pair(1, COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_WHITE,COLOR_BLACK);
	return 0;
}

int initHeader(void){
	// 
	char str[255];
	uint8_t str_len = 0;
    childwinh = subwin(mainwin, 10, width - 4, 1, 2);
    box(childwinh, '|', '-');
    mvwaddstr(childwinh, 1, 3, "8888888888     888               d8b           .d88888b.   .d8888b.   |");
    mvwaddstr(childwinh, 2, 3, "888            888               Y8P          d88P' 'Y88b d88P  Y88b  |");
    mvwaddstr(childwinh, 3, 3, "888            888                            888     888 Y88b.       |");
    mvwaddstr(childwinh, 4, 3, "8888888    .d88888 888  888  888 888 88888b.  888     888  'Y888b.    |");
    mvwaddstr(childwinh, 5, 3, "888       d88' 888 888  888  888 888 888 '88b 888     888     'Y88b.  |");
    mvwaddstr(childwinh, 6, 3, "888       888  888 888  888  888 888 888  888 888     888       '888  |");
    mvwaddstr(childwinh, 7, 3, "888       Y88b 888 Y88b 888 d88P 888 888  888 Y88b. .d88P Y88b  d88P  |");
    mvwaddstr(childwinh, 8, 3, "8888888888 'Y88888  'Y8888888P'  888 888  888  'Y88888P'   'Y8888P'   |");
    mvwaddstr(childwinh, 6, 76, "Embedded Systems | HvA 2020");
    mvwaddstr(childwinh, 7, 76, "Rowan Bolding");
    mvwaddstr(childwinh, 8, 76, "Bart-Jan van Strien");
	strcpy(str, "Press SHIFT+Right_arrow -> to switch to next program");
	str_len = strlen(str);
	mvwaddstr(childwinh, 6, max_x - (str_len+7), str);
	strcpy(str, "Press SHIFT+Left_arrow <- to switch to previous program");
	str_len = strlen(str);
	mvwaddstr(childwinh, 7, max_x - (str_len+7), str);
	strcpy(str, "Press ESC to exit");
	str_len = strlen(str);
    mvwaddstr(childwinh, 8, max_x - (str_len+7), str);
	
	return 0;
}

int initChildWindow_1(void){
	attron(COLOR_PAIR(SELECTED_WIN));
    childWin_1 = subwin(mainwin, height - 12, halfwidth - 2, 11, 2);
    box(childWin_1, '|', '-');
    attroff(COLOR_PAIR(SELECTED_WIN));
    mvwaddstr(childWin_1, 1, 0, "Verbinden");
	return 0;
}

int initChildWindow_2(void){
	attron(COLOR_PAIR(UNSELECTED_WIN));
    childWin_2 = subwin(mainwin, height - 12, halfwidth - 3, 11, halfwidth + 1);
    box(childWin_2, '|', '-');
    attroff(COLOR_PAIR(UNSELECTED_WIN));
    // mvwaddstr(childWin_2, 6, 7, "Verbinden...");
    //mvwaddstr(childWin_2, 7, 11, "met XMEGA...");
    //mvwaddstr(childWin_2, 8, 8, "Rowan Bolding");
    //mvwaddstr(childWin_2, 9, 5, "Bart-Jan van Strien");
	return 0;
}

/*********************************************************************************
XMEGA SERIAL
*********************************************************************************/
int initXmegaSerial(void){
	char sUsbName[] = "/dev/ttyACM0";
	if (!InitXmegaSerial(sUsbName, B38400, 0)) {
		//fout
		mvwaddstr(childWin_1, 1, 3, "VERBINDING MISLUKT");
	}
	else {
		//goei
		mvwaddstr(childWin_1, 1, 3, "Verbonden");
	};
	wrefresh(childWin_1);
	return 0;
}

/*********************************************************************************
MAIN
*********************************************************************************/

int main()
{
    int nKey;
    bool bExit;
	//Initialiseer windows
    printw("w4.2.2ncursesio\n\n"); refresh();
	initMainWindow();
	initHeader();
	initChildWindow_1();
    initChildWindow_2();
    refresh();
	
	//start met childWindow 1 (childWin_1)
    wmove(childWin_1,1,1);
    wclrtoeol(childWin_1);
    attron(COLOR_PAIR(UNSELECTED_WIN));
    box(childWin_1, '|', '-');
    attroff(COLOR_PAIR(UNSELECTED_WIN));
	
    // Initialiseer de correct Xmega-connectie
    initXmegaSerial();
	
    // wait for user input before exit
	
	bExit = false;
	while (!bExit) {
		nKey = getch();
		// Exit is ESC
		if (nKey == ESC) {
		bExit = true;
		};
		if(nKey != -1){
			manager(nKey);
		}
  };
	
    // EXIT!
    CloseXmegaSerial();
    delwin(childwinh);
    delwin(childWin_1);
    delwin(childWin_2);
    delwin(mainwin);
    endwin();
    refresh();
    return EXIT_SUCCESS;
}