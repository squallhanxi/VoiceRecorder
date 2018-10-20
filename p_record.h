
/*  Squall Hon   2015.11.8  */

/*  记录线程头文件  */

#include "global.h"

unsigned int s,i,j,k,l;
unsigned long int mutesize;

void dealmix();
void dealsin(unsigned short int port);
void nonrecdata();

struct timeval now_tv;
struct timezone now_tz;
struct tm *now_tm;
time_t now_timep;

void tellsavrun();
extern void *Record_thread(void *arg);

