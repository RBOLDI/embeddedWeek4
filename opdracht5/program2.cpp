#include "program2.hpp"

using namespace std;

bool program_2(int nKey){
	mvprintw(5,5, "Programn 2: %c", nKey); refresh();
	return false;
}

bool closeProgram_2(){
	mvprintw(6,5, "Closed programn 2"); refresh();
	return false;
}