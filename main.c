
/*  Squall Hon   2015.11.11  */

/*  ������  */

#include "global.h"

int main()
{     	
	init();

	pthread_create(&id_recv,NULL,(void *)Recv_thread,NULL);		//���������߳�
	pthread_create(&id_record,NULL,(void *)Record_thread,NULL);	//������¼�߳�
	pthread_create(&id_alive,NULL,(void *)Alive_thread,NULL);	//���������߳�
	pthread_create(&id_save,NULL,(void *)Save_thread,NULL);		//���������߳�
	pthread_create(&id_play,NULL,(void *)Play_thread,NULL);		//���������߳�

	while(1);

	return 0;
}


