// w4.1.1cyclischbuffer

//TODO: voeg de 2 #-commando's toe



  #include <stdbool.h>
  #include <stdio.h>
  #include <string.h>
  #include <time.h>
  #include "buffer.hpp"

  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

#endif // _CYCLISCHBUFFER_HPP_

