
/*  Squall Hon   2015.11.8  */

/*  �����߳�ͷ�ļ�  */

#include "global.h"

int s;
 
extern int initplay(char *pathname,int nSampleRate,int nChannels,int fmt); 
extern int audioplay(int playtime);
extern void *Play_thread(void *arg);
