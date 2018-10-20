
/*  Squall Hon   2015.11.11  */

/*  ��¼�߳�  */

#include "p_record.h"

void *Record_thread(void *arg)    //��¼�߳�
{
	while (1)
	{
		if(md.isfirstpkg == YES)	//�жϻ�����¼�Ƿ�Ϊ�״�
		{
			md.isfirstpkg = NO;
			gettimeofday(&md.now_mixtv,NULL);

			char str_filestarttime[50];
					
			time(&now_timep);
			now_tm = localtime(&now_timep);

			sprintf(str_filestarttime,"%d%02d%02d%02d%02d%02d",(1900 + now_tm->tm_year),
				(1 + now_tm->tm_mon),now_tm->tm_mday , 
				now_tm->tm_hour , 
				now_tm->tm_min , now_tm->tm_sec);

			strcpy(md.wavpath,"./WAV/HUN/HUN-0-");
			strcat(md.wavpath,str_filestarttime);
			strcat(md.wavpath,".wav");
		}
		
		while(recrun != YES);
		recrun = NO;
		
		switch(wavport)
		{
			case HYUDPPORT:
				dealmix();
				break;
			case ZBUDPPORT:
				dealsin(ZBUDPPORT);
				break;
			case GBUDPPORT:
				dealsin(GBUDPPORT);
				break;
			case CNGBUDPPORT:
				dealsin(CNGBUDPPORT);
				break;
			default:
				nonrecdata();
		}
	}
}

void dealsin(unsigned short int port)	//����������
{
	for(i=0;i<CARNO;i++)
	{
		for(j=0;j<TEMNO;j++)
		{
			if(td[i][j].ipaddr == sinwavIP)
			{
				time(&now_timep);
				now_tm = localtime(&now_timep);

				if(td[i][j].isfirstpkg == YES)	//�����ļ�·��,�״�ʹ�ü�Ϊ�½�·��
				{
					char str_no[50];
					char str_filestarttime[50];
							
					sprintf(str_no,"%d",(sinwavIP & 0xff000000)>>24);
					sprintf(str_filestarttime,"%d%02d%02d%02d%02d%02d",(1900 + now_tm->tm_year),
						(1 + now_tm->tm_mon),now_tm->tm_mday , 
						now_tm->tm_hour , 
						now_tm->tm_min , now_tm->tm_sec);
							
					strcpy(td[i][j].wavpath,"./WAV/");
					strcat(td[i][j].wavpath,dirname[td[i][j].cartype]);
					strcat(td[i][j].wavpath,"/");
					strcat(td[i][j].wavpath,dirname[td[i][j].cartype]);
					strcat(td[i][j].wavpath,"-");
					strcat(td[i][j].wavpath,str_no);
					strcat(td[i][j].wavpath,"-");	
					strcat(td[i][j].wavpath,str_filestarttime);
					strcat(td[i][j].wavpath,".wav");						
							
					td[i][j].isfirstpkg = NO;
				}
						
				td[i][j].lastpkgtime = sinwavtime;	//ˢ���ϰ�ʱ��

				for(k=0;k<sizeof(wavbuff);k++)
				{
					*td[i][j].p_buff = wavbuff[k];
					td[i][j].p_buff++;
					td[i][j].allrecbyte++;
					if(td[i][j].p_buff-td[i][j].buff == VOCBUFF)
					{
						savelen = td[i][j].p_buff-td[i][j].buff;
						strcpy(wavpath,td[i][j].wavpath);
						bcopy(td[i][j].buff,buff_second_save,td[i][j].p_buff-td[i][j].buff);

						tellsavrun();

						if(td[i][j].allrecbyte >= FILEMAX)
						{
							td[i][j].isfirstpkg = YES;
							td[i][j].allrecbyte = 0;
						}

						td[i][j].p_buff = td[i][j].buff;
					}
				}
			}
		}
	}
}

void dealmix()	//����������
{
	for (i=0;i<sizeof(wavbuff);i++)
	{
		*md.p_buff_mix = wavbuff[i];
		md.p_buff_mix++;
		md.allrecbyte++;
		if(md.p_buff_mix-md.buff_mix == VOCBUFF)
		{
			bcopy(md.wavpath,wavpath,200);
			savelen = md.p_buff_mix-md.buff_mix;
			bcopy(md.buff_mix,buff_second_save,md.p_buff_mix-md.buff_mix);

			tellsavrun();

			if(md.allrecbyte >= FILEMAX)
			{
				md.isfirstpkg = YES;
				md.allrecbyte = 0;
			}
			md.p_buff_mix = md.buff_mix;
		}
	}
}

void nonrecdata()	//��WAV���ݵĴ���
{
	mutesize = ((mixwavtime.tv_sec - md.now_mixtv.tv_sec) * 1000000 + \
		(mixwavtime.tv_usec - md.now_mixtv.tv_usec))/1000000 * 8192;//������ʱ�����뾲����
	md.now_mixtv.tv_sec = mixwavtime.tv_sec;
	md.now_mixtv.tv_usec = mixwavtime.tv_usec;
	for(l=0;l<mutesize;l++)
	{
		*md.p_buff_mix = MUTEPKG;
		md.p_buff_mix++;
		md.allrecbyte++;
		if(md.p_buff_mix - md.buff_mix == VOCBUFF)
		{
			bcopy(md.wavpath,wavpath,200);
			savelen = md.p_buff_mix-md.buff_mix;
			bcopy(md.buff_mix,buff_second_save,md.p_buff_mix-md.buff_mix);

			tellsavrun();

			if(md.allrecbyte >= FILEMAX)
			{
				md.isfirstpkg = YES;
				md.allrecbyte = 0;
			}

			md.p_buff_mix = md.buff_mix;
		}
	}
	
	for(i=0;i<CARNO;i++)	//���������ݴ���10�����
	{
		for(j=0;j<TEMNO;j++)
		{
			if(td[i][j].isfirstpkg == NO && sinwavtime-td[i][j].lastpkgtime >= SIGVOCEND)	
			{
				td[i][j].isfirstpkg = YES;

				savelen = td[i][j].p_buff-td[i][j].buff;
				strcpy(wavpath,td[i][j].wavpath);
				bcopy(td[i][j].buff,buff_second_save,td[i][j].p_buff-td[i][j].buff);

				tellsavrun();

				td[i][j].p_buff = td[i][j].buff;
			}
		}
	}
}

void tellsavrun()	//����save�߳�����
{
	savrun = YES;
}


