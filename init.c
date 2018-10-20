
/*  Squall Hon   2015.11.11  */

/*  ��ʼ������  */

#include "init.h"

void init()
{
	int i,sockfd,flags;
	unsigned char buf[MAXRECVDATA];
	ssize_t n;
	IP_HEADER *ip;
	unsigned char databuf[MAXRECVDATA];
	unsigned int initfromTKQ;
	char dirpath[20];

	printf("Create dir...\n");	//�����ļ�ϵͳ�ṹ
	DIRSYS();

	mkdir("WAV",0777);	//�ڵ�ǰĿ¼�´���WAVĿ¼

	for(i=0;i<CARNO+1;i++)
	{
		strcpy(dirpath,"WAV/");
		strcat(dirpath,dirname[i]);
		if(mkdir(dirpath,0777) == 0)
      		{   
			printf("Create dir %s OK!\n",dirname[i]);
      		}
		else
		{
			printf("Create dir %s error!\n",dirname[i]);
		}
	}
	printf("\nCreate dir finish!\n\n");

	printf("Init all config data....\n");	

	md.p_buff_mix = md.buff_mix;	//�������ݻ���ռ�ָ���ʼ��
	md.isfirstpkg = YES;	//��ʼ���װ�����
	md.allrecbyte = 0;	//�ܼ�¼�ֽ�������
	
	//������ֻ��ʼ����һ����ʵ��ʹ��ʱ����52���ն˽ṹ�������ʼ��..........
	td[P2][3].ipaddr = 0xD41fa8c0;	//��ʼ��IP�ڳ�����Ӧ��ʵ��ʹ��ʱ����λ������
	td[P2][3].cartype = P2;
	td[P2][3].p_buff = td[P2][3].buff;	//�������ݻ���ռ�ָ���ʼ��
	td[P2][3].isfirstpkg = YES;	//�װ���־��ʼ��
	td[P2][3].allrecbyte = 0;	//�ܼ�¼�ֽ�������

	recrun = NO;
	savrun = NO;

	printf("Init all config data OK!\n\n");	

	printf("Waiting for TKQ.....\n");

	if((sockfd = socket(AF_PACKET,  SOCK_DGRAM, htons(ETH_P_IP)))== -1)	//׼����ͨ��������
	{
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
	}
	flags = fcntl(sockfd, F_GETFL, 0);    	//��ȡ�ļ���flagsֵ
	fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);	//���ó�����ģʽ
	
	printf("sockfd is:%d\n",sockfd);

	initfromTKQ = NO;
	while(initfromTKQ == NO)	//��ͨ������ʼ���ɹ���־
	{	
		n = recv(sockfd, buf, sizeof(buf), 0);//MSG_WAITALL);
		ip = ( IP_HEADER *)(buf);

		if(ip->proto == IPPROTO_UDP)
		{
			UDP_HEADER *st;	
			analysevoc(buf,ip,n,databuf);
			st = ( UDP_HEADER *)(databuf);

			if(ntohs(st->dest) == WSUDPPORT && ip->destIP == 0x941fa8c0)	//�����źŴ���
			{
				printf("Recive IP is : %d.%d.%d.%d\n",*(databuf+8),*(databuf+9),*(databuf+10),*(databuf+11));
				printf("Recive time is : %d-%d-%d %d:%d:%d\n",*(databuf+12),*(databuf+13),*(databuf+14),\
					*(databuf+15),*(databuf+16),*(databuf+17));
				initfromTKQ = YES;
			}
		}
	}
	printf("Connect TKQ OK!\n\n");

	printf("Init com.....\n");
	//initcom(COMBPS);
	printf("Init com OK!\n\n");

	printf("Init all OK!\n\n");
}
	








