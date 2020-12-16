#ifndef _PROGRAM2_HPP_
#define _PROGRAM2_HPP_

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

bool program_2(int nKey, WINDOW *childWin);
bool closeProgram_2(WINDOW *childWin);

#endif
