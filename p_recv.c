
/*  Squall Hon   2015.11.11  */

/*  接收数据线程，最高优先级  */

#include "p_recv.h"

void *Recv_thread(void *arg)    //接收线程
{
	if ((sockfd = socket(AF_PACKET,  SOCK_DGRAM, htons(ETH_P_IP)))== -1)
	{    
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
	}
	flags = fcntl(sockfd, F_GETFL, 0);    	//获取文件的flags值
	fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);	//设置成阻塞模式

	struct timeval timeout = {TIMEOUT,0};	//设置接收超时
	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));

	while (1)
	{
		n = recv(sockfd, buf, sizeof(buf), 0);	//阻塞接收
	
		ip = ( IP_HEADER *)(buf);
		analysevoc(buf,ip,n,databuf);
		st = ( UDP_HEADER *)(databuf);

		if(ip->proto == IPPROTO_UDP)
		{
			switch(ntohs(st->dest))
			{
				case HYUDPPORT:	//混音处理

				gettimeofday(&md.now_mixtv,NULL);
				wavport = HYUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case ZBUDPPORT:	//单音组播处理
			
				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = ZBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case GBUDPPORT:	//单音广播处理
			
				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = GBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case CNGBUDPPORT://单音车内广播处理

				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = CNGBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case SYNUDPPORT:	//时间同步
			
				break;
				default:	//有UDP数据进入但非WAV数据
			
				gettimeofday(&mixwavtime,NULL);
				gettimeofday(&now_tv,&now_tz);

				sinwavtime = now_tv.tv_sec;
				wavport = NO;

				tellrecrun();
			}		
		}
		else	//有非UDP数据进入
		{
			gettimeofday(&mixwavtime,NULL);
			gettimeofday(&now_tv,&now_tz);

			sinwavtime = now_tv.tv_sec;
			wavport = NO;

			tellrecrun();
		}
	}
	close(sockfd);
}

void tellrecrun()	//告诉record线程运行
{
	recrun = YES;
}


