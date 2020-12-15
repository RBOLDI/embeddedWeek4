#include "program1.hpp"

using namespace std;

bool program_1(int nKey){
	mvprintw(5,5, "Programn 1: %c", nKey); refresh();
	return false;
}

bool closeProgram_1(){
	mvprintw(6,5, "Closed programn 1"); refresh();
	return false;
}