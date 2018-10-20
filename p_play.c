
/*  Squall Hon   2015.11.11  */

/*  播放线程  */

#include "p_play.h" 

void *Play_thread(void *arg)    //播放线程
{
	while(1)
	{		
		initplay(playstr,8192,1,8);
		PWD.isStopplay = PLAY_NO_STOP;
		audioplay(playtime);
	}
}


