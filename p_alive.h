
/*  Squall Hon   2015.11.7  */

/*  �����߳�ͷ�ļ�  */

#include "global.h"

unsigned long int lastalivetime;

struct timeval as_tv;
struct timezone as_tz;
struct tm *as_tm;
time_t as_timep;

extern void *Alive_thread(void *arg);

