
/*  Squall Hon   2015.11.11  */

/*  全局数据结构与变量  */

#include "config.h"
#include "include.h"

#pragma pack(1)	//打开手动内存对齐
typedef struct _terminaldata 	//定义各车各终端数据结构
{
	unsigned long int lastpkgtime;		//本终端上一数据包时间(秒)
	unsigned int isfirstpkg;		//是否首包
	unsigned char wavpath[MAXWAVPATH];	//当前记录wav文件路径
	unsigned int ipaddr;			//本终端IP地址
	unsigned int cartype;			//所属车辆类型
	unsigned int terminalno;		//终端编号
	unsigned char buff[VOCBUFF];		//实时话音数据缓存
	unsigned char *p_buff;			//实时话音数据缓存指针
	unsigned int allrecbyte;		//总记录字节数
}TERMINAL_DATA;

typedef struct _iphdr //定义IP首部 
{
	unsigned char h_verlen; 		//4位首部长度+4位IP版本号 
	unsigned char tos; 			//8位服务类型TOS 
	unsigned short total_len; 		//16位总长度（字节） 
	unsigned short ident; 			//16位标识 
	unsigned short frag_and_flags; 		//3位标志位 
	unsigned char ttl; 			//8位生存时间 TTL 
	unsigned char proto; 			//8位协议 (TCP, UDP 或其他) 
	unsigned short checksum; 		//16位IP首部校验和 
	unsigned int sourceIP; 			//32位源IP地址 
	unsigned int destIP; 			//32位目的IP地址 
}IP_HEADER; 

typedef struct _wavheader //定义WAV首部 
{ 
	unsigned char RIFF[4];
	unsigned int size;
	unsigned char WAVEfmt[8];
	unsigned int ALAW; 
  unsigned short int fmttag;
	unsigned short int channel;
	unsigned int samplespersec;
	unsigned int bytepersec;
	unsigned short int blockalign;
	unsigned int bitpersamples;
	unsigned char wavefact[4];
	unsigned char temp[8];
	unsigned char wavedata[4];
	unsigned int allsize;
}WAV_HEADER;

typedef struct _mixdata 	//定义混音数据结构 
{
	unsigned char buff_mix[VOCBUFF];		//定义混音缓存空间
	unsigned char *p_buff_mix;			//定义混音缓存空间指针
	//unsigned long int MIX_basetime;			//定义混音基准时间(微秒)
	struct timeval now_mixtv;
	unsigned int isfirstpkg;			//是否首包
	unsigned char wavpath[MAXWAVPATH];		//当前记录混音wav文件路径
	unsigned int allrecbyte;			//总记录字节数
}MIX_DATA;

typedef struct _udphdr		//定义UDP头结构
{
	unsigned short int source;	//UDP源端口
	unsigned short int dest;	//UDP目的端口
	unsigned short int len;		//UDP长度
	unsigned short int check;
}UDP_HEADER;

typedef struct _syntime 	//定义时间同步数据结构 
{
	unsigned short int year;
	unsigned char mon;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned char oth;
	unsigned short int usec;
}SYN_TIME;

typedef struct _playdata	//定义播放数据结构
{
	char *pathname;
	int nSampleRate;
	int nChannels;
	int fmt;
	int isStopplay;  //外部设置，是否停止播放
	int playpos;   //当前播放位置，单位 秒
	int playstatu;  //状态机
}PLAY_DATA;
#pragma pack()	//关闭手动内存对齐

pthread_t id_record,id_alive,id_save,id_play,id_recv;
//sigset_t sigs;
unsigned int recrun,savrun;

TERMINAL_DATA td[CARNO][TEMNO];		//定义所有终端的数据结构实例
MIX_DATA md;	//定义混音数据结构实例

PLAY_DATA PWD;	//定义播放数据结构实例

unsigned char wavpath[MAXWAVPATH];	//定义当前存储文件路径名称
unsigned int savelen;		//定义当前存入文件的数据大小
unsigned char buff_second_save[VOCBUFF];	//定义存入文件的数据内容

unsigned char wavbuff[MAXRECVDATA];	//纯WAV数据缓存,用于接收线程传递给记录线程
unsigned long int sinwavtime;	//单音数据包接收时间，用于接收线程传递给记录线程
unsigned int sinwavIP;	//单音数据包IP地址，用于接收线程传递给记录线程
unsigned short int wavport;	//单音数据包端口，用于接收线程传递给记录线程
struct timeval mixwavtime;	//混音数据包接收时间，用于接收线程传递给记录线程
unsigned int playtime;	//播放开始时间
unsigned char playstr[200];	//播放文件路径名称

unsigned char *dirname[CARNO];	//文件夹名称数组

unsigned int isrecording;	//录音状态
unsigned int iswavfull40;	//wav文件是否超过4g

unsigned int wavtotalsize;	//WAV文件总大小

unsigned int comfd; 	//显示串口fd

extern void *Save_thread(void *arg);	//存盘线程
extern void *Record_thread(void *arg);	//记录线程
extern void *Alive_thread(void *arg);	//保活线程
extern void *Play_thread(void *arg);	//播放线程
extern void *Recv_thread(void *arg);	//接收线程
