
/*  Squall Hon   2015.11.11  */

/*  �����߳�  */

#include "p_play.h" 

void *Play_thread(void *arg)    //�����߳�
{
	while(1)
	{		
		initplay(playstr,8192,1,8);
		PWD.isStopplay = PLAY_NO_STOP;
		audioplay(playtime);
	}
}


