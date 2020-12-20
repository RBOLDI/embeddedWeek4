#include "program1.hpp"

using namespace std;

bool program_1(int nKey, WINDOW *childWin){
	uint8_t nByte;
	char string[100];
	int ch;
	ch = nKey; 
	wmove(childWin,3,1);
	wclrtoeol(childWin);
	wmove(childWin,4,1);
	wclrtoeol(childWin);
	wmove(childWin,5,1);
	wclrtoeol(childWin);
	sprintf(string,"KEY NAME : %s - %d\n", keyname(ch),ch);
	mvwaddstr(childWin, 3, 3, string);
	sprintf(string,"Toets: %d=%c    ", nKey, nKey);
	mvwaddstr(childWin, 4, 3, string);
	XmegaWriteByte((uint8_t*)&nKey);
	while (!XmegaReadByte(&nByte));
	sprintf(string,"Xmega: %d=%c    ", nByte, nByte);
	mvwaddstr(childWin, 5, 3, string);
	attron(COLOR_PAIR(UNSELECTED_WIN));
	box(childWin, '|', '-');
	attroff(COLOR_PAIR(UNSELECTED_WIN));
	wrefresh(childWin);
	return false;
}

bool closeProgram_1(WINDOW *childWin){
	char string[100];
	wmove(childWin,3,1);
	wclrtoeol(childWin);
	wmove(childWin,4,1);
	wclrtoeol(childWin);
	wmove(childWin,5,1);
	wclrtoeol(childWin);
	sprintf(string,"Program closed...");
	mvwaddstr(childWin, 3, 3, string);
	sprintf(string," ");
	mvwaddstr(childWin, 4, 3, string);
	sprintf(string," ");
	mvwaddstr(childWin, 5, 3, string);
	attron(COLOR_PAIR(UNSELECTED_WIN));
	box(childWin, '|', '-');
	attroff(COLOR_PAIR(UNSELECTED_WIN));
	wrefresh(childWin);
	return false;
}