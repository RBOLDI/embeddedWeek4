#ifndef _PROGRAM1_HPP_
#define _PROGRAM1_HPP_

#include <iostream>
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "hello-xmega-lib.hpp"

#define SELECTED_WIN 1
#define UNSELECTED_WIN 2

bool program_1(int nKey, WINDOW *childWin);
bool closeProgram_1(WINDOW *childWin);

#endif
