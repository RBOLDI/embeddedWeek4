// w4.2.2ncursesio

#ifndef _NCURSESIO_HPP_
#define _NCURSESIO_HPP_
#define ESC 27
#define ENTER 10
#define SHIFT_RIGHT 402
#define SHIFT_LEFT	393

#define PROGRAM_1 	0
#define PROGRAM_2	1
#define PROGRAM_NUM	2
  //TODO: zorg dat ncurses beschikbaar is
  #include <iostream>
  #include <curses.h>
  #include <stdbool.h>
  #include <stdio.h>
  #include <stdint.h>
  #include <string.h>
  #include <time.h>
  
  #include "program1.hpp"
  #include "program2.hpp"

  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

#endif // _NCURSESIO_HPP_