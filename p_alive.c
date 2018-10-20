
/*  Squall Hon   2015.11.11  */

/*  保活线程  */

#include "p_alive.h"

void *Alive_thread(void *arg)    //守护线程
{
	gettimeofday(&as_tv,&as_tz);
	lastalivetime = as_tv.tv_sec;

	int i;
	char carwavpath[100];
	
	while(1)
	{
		gettimeofday(&as_tv,&as_tz);
		if(as_tv.tv_sec - lastalivetime >= ALIVEDELTATIME)
		{
			alive();
			lastalivetime = as_tv.tv_sec;
			
			wavtotalsize = 0;
			wavdirsize(WAVDIRPATH);
			printf("WAV total size is : %d\n",wavtotalsize);
			if(wavtotalsize/1048576 >= DIRALARMSIZE)	//超过告警值
			{
				iswavfull40 = YES;
				printf("Size alarm!!!!\n");
				if(wavtotalsize/1048576 >= DIRDELSIZE)	//超过删除值
				{
					printf("Size alarm,try to delete some file!\n");
					for(i=0;i<CARNO+1;i++)
					{
						strcpy(carwavpath,WAVDIRPATH);
						strcat(carwavpath,"/");
						strcat(carwavpath,dirname[i]);
						wavtotalsize = 0;
						wavdirsize(carwavpath);
						while(wavtotalsize/1048576 >= KEEPSIZE)	//大于130M
						{
							delfirstfile(carwavpath);
							wavtotalsize = 0;
							wavdirsize(carwavpath);
						}
						memset(carwavpath,'\0',100);
					}
				}
			}
			else
			{
				iswavfull40 = NO;
			}
		}
	}
}



