
/*  Squall Hon   2015.11.7  */

/*  功能函数  */

#include "func.h"

void analysevoc(char *buff , IP_HEADER *ip , int n , char *databuf)	//去掉IP头
{
	int i;
	for (i=0;i<n-(ip->h_verlen&0x0f)*4;i++)
	{
		databuf[i] = buff[(ip->h_verlen&0x0f)*4+i];
	}	
}

void setIP(char *ipaddr)	//设置IP地址
{
	printf("setIP()\n");
}

void initcom(int combps)	//初始化串口速率
{
	comfd = UART0_Open(fd,COMNO); 	//打开串口，返回文件描述符
	UART0_Set(fd,combps,0,8,1,'N');		//设置串口
}

void syntime(char *udptime)		//时间同步
{
	struct tm *st_tm;	//时间相关变量
	time_t st_timep;	//时间相关变量
	SYN_TIME *st;	//定义时间数据结构实例

	time(&st_timep);
	st_tm = localtime(&st_timep);

	st = (SYN_TIME *)(udptime);

	printf("Server time: %d-%02d-%02d %02d:%02d:%02d\n",ntohs(st->year),st->mon,st->day,st->hour,st->min,st->sec);

	st_tm->tm_year = ntohs(st->year) - 1900;
	st_tm->tm_mon = st->mon - 1;
	st_tm->tm_mday = st->day;
	st_tm->tm_hour = st->hour;
	st_tm->tm_min = st->min;
	st_tm->tm_sec = st->sec;

	st_timep = mktime(st_tm);
	stime(&st_timep);
}

void alive()		//保活
{
	printf("alive()\n");
}

void slipsend(char *uartdata,int n)		//串口slip协议发送
{
	int i;	
	char slipdata[MAXSLIPDATA];
	char *ps;
	ps = slipdata;
	*ps = 0xc0;
	ps++;
	for(i=0;i<n;i++)
	{
		if((*uartdata) == 0xc0)
		{
			*ps ==0xdb;
			ps++;
			*ps == 0xdc;
			ps++;
			uartdata++;
		}
		else if((*uartdata) == 0xdb)
		{
			*ps ==0xdb;
			ps++;
			*ps == 0xdd;
			ps++;
			uartdata++;
		}
		else
		{
			*ps = *uartdata;
			ps++;
			uartdata++;
		}
	}
	*ps = 0xc0;
	UART0_Send(fd,slipdata,sizeof(slipdata));
}

void wavdirsize(char *dir_name)  	//测试WAV目录总大小
{  
	DIR *dirp = opendir(dir_name);
	if(!dirp)
	{
		perror("opendir");
	}
	struct stat st;
	struct dirent *dir;
	char fullpath[MAXWAVPATH];
	while((dir = readdir(dirp)) != NULL)
	{
		if(!strcmp(dir->d_name, ".") || // 考虑当前目录和上级目录，否则会死循环
         !strcmp(dir->d_name, "..")) 
		{
			continue;
		}
		sprintf(fullpath, "%s/%s", dir_name, dir->d_name); //获取全局路径
		if(lstat(fullpath, &st) < 0) 
		{
     	perror("lstat");
     	continue;
  	}
		else
		{
			wavtotalsize = wavtotalsize + (unsigned long long)(st.st_size);
		}
  	if(S_ISDIR(st.st_mode)) 
		{
    	wavdirsize(fullpath); // 递归遍历子目录
  	}
  }	
  closedir(dirp);
}

void delfirstfile(char *dir_name)	//删除该目录下最早的一个文件
{
	time_t firsttime = 0;
	DIR *dirp = opendir(dir_name);
  if(!dirp)
	{
		perror("opendir");
	}
	struct stat st;
	struct dirent *dir;
	char fullpath[MAXWAVPATH];
	char firstfile[MAXWAVPATH];
	while((dir = readdir(dirp)) != NULL)
	{
		if(!strcmp(dir->d_name, ".") || // 考虑当前目录和上级目录，否则会死循环
          !strcmp(dir->d_name, "..")) 
		{
			continue;
		}
		sprintf(fullpath, "%s/%s", dir_name, dir->d_name); //获取全局路径
		if(lstat(fullpath, &st) < 0) 
		{
			perror("lstat");
			continue;
		}
		else
		{
			if(firsttime > st.st_mtime || firsttime == 0)
			{
				firsttime = st.st_mtime;
				bcopy(fullpath,firstfile,MAXWAVPATH);
			}			
		}
	}
	remove(firstfile);
	memset(firstfile,'\0',MAXWAVPATH);
	closedir(dirp);
}

int initplay(char *pathname,int nSampleRate,int nChannels,int fmt) 	//初始化播放
{
	PWD.pathname = pathname;
	PWD.nSampleRate = nSampleRate;
	PWD.nChannels = nChannels;
	PWD.fmt = fmt;
	PWD.isStopplay = PLAY_NO_STOP;
	PWD.playpos = 0;
	PWD.playstatu = PLAY_NO_STOP;
	return 0;
}

int audioplay(int playtime)	//播放函数
{
	int writenum;	
	PWD.playstatu = PLAY_NO_STOP;	
	int dsp_fd,mix_fd,status,arg; 
	dsp_fd = open("/dev/dsp" , O_WRONLY);
	if(dsp_fd < 0) 
	{   
		return  OPEN_DSP_FAILED; 
	} 
	arg = PWD.nSampleRate; 
	status = ioctl(dsp_fd,SOUND_PCM_WRITE_RATE,&arg);
	if(status < 0) 
	{   
		close(dsp_fd);   
		return SAMPLERATE_STATUS; 
	} 
	if(arg != PWD.nSampleRate) 
	{   
		close(dsp_fd);   
		return SET_SAMPLERATE_FAILED; 
	} 
	arg = PWD.nChannels; 
	status = ioctl(dsp_fd, SOUND_PCM_WRITE_CHANNELS, &arg); 
	if(status < 0) 
	{   
		close(dsp_fd);   
		return CHANNELS_STATUS; 
	} 
	if( arg != PWD.nChannels) 
	{   
		close(dsp_fd);   
		return SET_CHANNELS_FAILED; 
	} 
	arg = PWD.fmt;
	status = ioctl(dsp_fd, SOUND_PCM_WRITE_BITS, &arg); 
	if(status < 0) 
	{   
		close(dsp_fd);   
		return FMT_STATUS; 
	} 
	if(arg != PWD.fmt) 
	{   
		close(dsp_fd);   
		return SET_FMT_FAILED; 
	}

									
	FILE *file_fd = fopen(PWD.pathname,"r"); 
	if(file_fd == NULL) 
	{   
		close(dsp_fd);  
		return OPEN_FILE_FAILED; 
	} 
	
	if(playtime == PLAY_GOON)
	{
		fseek(file_fd,8192*PWD.playpos,SEEK_SET);
	}
	else
	{
		fseek(file_fd,8192*playtime,SEEK_SET);
		PWD.playpos = playtime;
	}

	int get_num; 
	char buf[NUM]; 
	while(feof(file_fd) == 0) 
	{   
		if(PWD.isStopplay == PLAY_STOP)
		{
			close(dsp_fd);    
			fclose(file_fd);
			PWD.playstatu = PLAY_STOP;    
			return 0;
		}		
		get_num = fread(buf,1,NUM,file_fd);
		writenum = write(dsp_fd,buf,get_num);
		PWD.playpos++;
		sleep(NUM/8192);
		fprintf(stderr,"%d:%d.....%d.....%d\n",writenum,PWD.isStopplay,PWD.playpos,PWD.playstatu);
		if(get_num != NUM)
		{    
			close(dsp_fd);    
			fclose(file_fd);
			PWD.playstatu = PLAY_STOP;    
			return 0;   
		} 
	} 
	close(dsp_fd); 
	fclose(file_fd);
	PWD.playstatu = PLAY_STOP; 
	return 0; 
}


