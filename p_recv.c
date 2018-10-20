
/*  Squall Hon   2015.11.11  */

/*  ���������̣߳�������ȼ�  */

#include "p_recv.h"

void *Recv_thread(void *arg)    //�����߳�
{
	if ((sockfd = socket(AF_PACKET,  SOCK_DGRAM, htons(ETH_P_IP)))== -1)
	{    
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
	}
	flags = fcntl(sockfd, F_GETFL, 0);    	//��ȡ�ļ���flagsֵ
	fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);	//���ó�����ģʽ

	struct timeval timeout = {TIMEOUT,0};	//���ý��ճ�ʱ
	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));

	while (1)
	{
		n = recv(sockfd, buf, sizeof(buf), 0);	//��������
	
		ip = ( IP_HEADER *)(buf);
		analysevoc(buf,ip,n,databuf);
		st = ( UDP_HEADER *)(databuf);

		if(ip->proto == IPPROTO_UDP)
		{
			switch(ntohs(st->dest))
			{
				case HYUDPPORT:	//��������

				gettimeofday(&md.now_mixtv,NULL);
				wavport = HYUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case ZBUDPPORT:	//�����鲥����
			
				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = ZBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case GBUDPPORT:	//�����㲥����
			
				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = GBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case CNGBUDPPORT://�������ڹ㲥����

				gettimeofday(&now_tv,&now_tz);
				sinwavtime = now_tv.tv_sec;
				sinwavIP = ip->sourceIP;
				wavport = CNGBUDPPORT;
				bcopy(databuf+8,wavbuff,sizeof(databuf)-8);

				tellrecrun();
			
				break;
				case SYNUDPPORT:	//ʱ��ͬ��
			
				break;
				default:	//��UDP���ݽ��뵫��WAV����
			
				gettimeofday(&mixwavtime,NULL);
				gettimeofday(&now_tv,&now_tz);

				sinwavtime = now_tv.tv_sec;
				wavport = NO;

				tellrecrun();
			}		
		}
		else	//�з�UDP���ݽ���
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

void tellrecrun()	//����record�߳�����
{
	recrun = YES;
}


