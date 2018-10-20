
/*  Squall Hon   2015.11.11  */

/*  主函数  */

#include "global.h"

int main()
{     	
	init();

	pthread_create(&id_recv,NULL,(void *)Recv_thread,NULL);		//创建接收线程
	pthread_create(&id_record,NULL,(void *)Record_thread,NULL);	//创建记录线程
	pthread_create(&id_alive,NULL,(void *)Alive_thread,NULL);	//创建保活线程
	pthread_create(&id_save,NULL,(void *)Save_thread,NULL);		//创建存盘线程
	pthread_create(&id_play,NULL,(void *)Play_thread,NULL);		//创建播放线程

	while(1);

	return 0;
}


