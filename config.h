
/*  Squall Hon   2015.11.8  */

/*  全局宏定义  */

#define S 0		//车辆类型
#define F1 1
#define F2 2
#define F3 3
#define F4 4
#define YF1 5
#define YF2 6
#define YF3 7
#define YF4 8
#define P1 9
#define P2 10
#define P3 11
#define P4 12
#define CARNO 13	//车辆总数
#define TEMNO 4		//每车终端数
#define DIRSYS()\
	do{\
	dirname[0]="S";\
	dirname[1]="F1";\
	dirname[2]="F2";\
	dirname[3]="F3";\
	dirname[4]="F4";\
	dirname[5]="YF1";\
	dirname[6]="YF2";\
	dirname[7]="YF3";\
	dirname[8]="YF4";\
	dirname[9]="P1";\
	dirname[10]="P2";\
	dirname[11]="P3";\
	dirname[12]="P4";\
	dirname[13]="HUN";\
	}while (0)	//文件系统结构及车辆类型

#define VOCBUFF 15*8192		//话音15秒缓存大小（字节）
#define MAXRECVDATA 10240	//收包缓存大小（字节）

#define MAXWAVPATH 200		//wav文件路径最大值（字节）
#define MAXSLIPDATA 100		//slip命令最大值（字节）

#define SIGVOCEND 10		//单路模式10秒后无话音包就存盘（秒）
//#define MIXVOCMUTE 100	  	//混音模式100毫秒无话音填静音数据（毫秒）

#define FILEMAX 8192*3600	//话音单文件最大容量（字节）

#define MUTEPKG 0		//静音数据

#define DEFIP 0x0100007f	//初始IP地址，已反向，127.0.0.1
#define DEFMASK 0x00ffffff	//初始掩码,已反向，24位

#define COMBPS	115200		//显示串口速率
#define COMNO "/dev/ttyS0"  	//串口号

#define SYNUDPPORT 60003	//时间同步UDP端口
#define ZBUDPPORT 62001		//组播UDP端口
#define GBUDPPORT 62002		//广播UDP端口
#define CNGBUDPPORT 62003	//车内广播UDP端口
#define HYUDPPORT 62004		//混音UDP端口
#define	WSUDPPORT 63001		//握手UDP端口

#define DIRALARMSIZE 4096	//磁盘空间告警临界值（兆）
#define DIRDELSIZE 4301		//磁盘空间删除文件临界值（兆）
#define KEEPSIZE 130		//保持剩余文件大小临界值（兆）

#define T1T2DELTATIME 1000	//是否同步时间差（毫秒）
#define ALIVEDELTATIME 5	//保活消息时间间隔（秒）
#define ALIVERESEND 3		//保活消息重发次数

#define TIMEOUT 1		//接收超时时间

#define UDISKPATH "/UDISK/"	//u盘路径
#define WAVDIRPATH "/root/vr/WAV"	//WAV文件夹绝对路径

#define YES 0	//是
#define NO 1	//否

#define TRUE 0	//是
#define FALSE -1	//否

#define OPEN_DSP_FAILED 1
#define SAMPLERATE_STATUS 2
#define SET_SAMPLERATE_FAILED 3
#define CHANNELS_STATUS 4
#define SET_CHANNELS_FAILED 5 
#define FMT_STATUS 6 
#define SET_FMT_FAILED 7
#define OPEN_FILE_FAILED 8  
#define NUM 8192  //一次读取wav的字节数
#define PLAY_NO_STOP 0
#define PLAY_STOP 1
#define PLAY_GOON -1

