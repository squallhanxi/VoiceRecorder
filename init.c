
/*  Squall Hon   2015.11.11  */

/*  初始化函数  */

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

	printf("Create dir...\n");	//创建文件系统结构
	DIRSYS();

	mkdir("WAV",0777);	//在当前目录下创建WAV目录

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

	md.p_buff_mix = md.buff_mix;	//混音数据缓存空间指针初始化
	md.isfirstpkg = YES;	//初始化首包变量
	md.allrecbyte = 0;	//总记录字节数清零
	
	//测试中只初始化了一个，实际使用时所有52个终端结构都必须初始化..........
	td[P2][3].ipaddr = 0xD41fa8c0;	//初始化IP于车辆对应表，实际使用时由上位机设置
	td[P2][3].cartype = P2;
	td[P2][3].p_buff = td[P2][3].buff;	//单音数据缓存空间指针初始化
	td[P2][3].isfirstpkg = YES;	//首包标志初始化
	td[P2][3].allrecbyte = 0;	//总记录字节数清零

	recrun = NO;
	savrun = NO;

	printf("Init all config data OK!\n\n");	

	printf("Waiting for TKQ.....\n");

	if((sockfd = socket(AF_PACKET,  SOCK_DGRAM, htons(ETH_P_IP)))== -1)	//准备与通控器链接
	{
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
	}
	flags = fcntl(sockfd, F_GETFL, 0);    	//获取文件的flags值
	fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);	//设置成阻塞模式
	
	printf("sockfd is:%d\n",sockfd);

	initfromTKQ = NO;
	while(initfromTKQ == NO)	//与通控器初始化成功标志
	{	
		n = recv(sockfd, buf, sizeof(buf), 0);//MSG_WAITALL);
		ip = ( IP_HEADER *)(buf);

		if(ip->proto == IPPROTO_UDP)
		{
			UDP_HEADER *st;	
			analysevoc(buf,ip,n,databuf);
			st = ( UDP_HEADER *)(databuf);

			if(ntohs(st->dest) == WSUDPPORT && ip->destIP == 0x941fa8c0)	//握手信号处理
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
	








