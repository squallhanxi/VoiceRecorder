
/*  Squall Hon   2015.11.8  */

/*  功能函数头文件  */

#include "global.h"

int fd;

extern void analysevoc(char *buff , IP_HEADER *ip , int n , char *databuf);
extern void setIP(char *ipaddr);
extern void initcom(int combps);
extern void syntime(char *udptime);
extern void alive();
extern void slipsend(char *uartdata,int n);
extern void wavdirsize(char *path);
extern void delfirstfile(char *dir_name);
extern int initplay(char *pathname,int nSampleRate,int nChannels,int fmt);
extern int audioplay(int playtime);
