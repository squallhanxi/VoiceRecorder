
/*  Squall Hon   2015.11.11  */

/*  ���������߳�ͷ�ļ���������ȼ�  */

#include "global.h"

int sockfd,flags;
unsigned char buf[MAXRECVDATA];
ssize_t n;
IP_HEADER *ip;
UDP_HEADER *st;
unsigned char databuf[MAXRECVDATA];

struct timeval now_tv;
struct timezone now_tz;
struct tm *now_tm;
time_t now_timep;

void tellrecrun();
extern void *Recv_thread(void *arg);

