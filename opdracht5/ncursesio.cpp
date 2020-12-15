// w4.2.2ncursesio
// g++ -Wall -lncurses -o ncursesio ncursesio.cpp hello-xmega-lib.cpp
// ./ncursesio

//TODO: zorg voor de juiste include
#include "ncursesio.hpp"

using namespace std;
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
			closeProgram_1();
		break;
	case PROGRAM_2:
			closeProgram_2();
		break;
	}
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
			program_1(Key);
			break;
		case PROGRAM_2:
			program_2(Key);
			break;
	}
}

int main(int argc, char* argv[]) {
	char sUsbName[] = "/dev/ttyACM0";
	int nKey;
	bool bExit;
	uint8_t nByte;
	char buffer[255];
	uint8_t bufferIndex = 0;

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
		if(nKey != -1){
			manager(nKey);
		}
		/*
		while(nKey < 255 && nKey != '\0'){
			if(nKey == ENTER){
				buffer[bufferIndex] = '\0';
				bufferIndex = 0;
			}
			buffer[bufferIndex++] = nKey
		}
		
		// Verwerk de toetsaanslag
		//check of het een ascii waarde is
		if (nKey != -1) {
		 // ch = nKey; endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);
		  mvprintw(5,5, "Toets: %d=%c    ", nKey, nKey); refresh();
		  XmegaWriteByte((uint8_t*)&nKey);
		  while (!XmegaReadByte(&nByte));
		  mvprintw(6,5, "Xmega: %d=%c    ", nByte, nByte); refresh();
		}
		//Move to other window
		else if(nKey == 558){
		nKey = 244;
		//tell xmega to switch window
		XmegaWriteByte((uint8_t*)&nKey);
		}*/
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

