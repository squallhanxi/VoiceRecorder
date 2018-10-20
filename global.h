
/*  Squall Hon   2015.11.11  */

/*  ȫ�����ݽṹ�����  */

#include "config.h"
#include "include.h"

#pragma pack(1)	//���ֶ��ڴ����
typedef struct _terminaldata 	//����������ն����ݽṹ
{
	unsigned long int lastpkgtime;		//���ն���һ���ݰ�ʱ��(��)
	unsigned int isfirstpkg;		//�Ƿ��װ�
	unsigned char wavpath[MAXWAVPATH];	//��ǰ��¼wav�ļ�·��
	unsigned int ipaddr;			//���ն�IP��ַ
	unsigned int cartype;			//������������
	unsigned int terminalno;		//�ն˱��
	unsigned char buff[VOCBUFF];		//ʵʱ�������ݻ���
	unsigned char *p_buff;			//ʵʱ�������ݻ���ָ��
	unsigned int allrecbyte;		//�ܼ�¼�ֽ���
}TERMINAL_DATA;

typedef struct _iphdr //����IP�ײ� 
{
	unsigned char h_verlen; 		//4λ�ײ�����+4λIP�汾�� 
	unsigned char tos; 			//8λ��������TOS 
	unsigned short total_len; 		//16λ�ܳ��ȣ��ֽڣ� 
	unsigned short ident; 			//16λ��ʶ 
	unsigned short frag_and_flags; 		//3λ��־λ 
	unsigned char ttl; 			//8λ����ʱ�� TTL 
	unsigned char proto; 			//8λЭ�� (TCP, UDP ������) 
	unsigned short checksum; 		//16λIP�ײ�У��� 
	unsigned int sourceIP; 			//32λԴIP��ַ 
	unsigned int destIP; 			//32λĿ��IP��ַ 
}IP_HEADER; 

typedef struct _wavheader //����WAV�ײ� 
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

typedef struct _mixdata 	//����������ݽṹ 
{
	unsigned char buff_mix[VOCBUFF];		//�����������ռ�
	unsigned char *p_buff_mix;			//�����������ռ�ָ��
	//unsigned long int MIX_basetime;			//���������׼ʱ��(΢��)
	struct timeval now_mixtv;
	unsigned int isfirstpkg;			//�Ƿ��װ�
	unsigned char wavpath[MAXWAVPATH];		//��ǰ��¼����wav�ļ�·��
	unsigned int allrecbyte;			//�ܼ�¼�ֽ���
}MIX_DATA;

typedef struct _udphdr		//����UDPͷ�ṹ
{
	unsigned short int source;	//UDPԴ�˿�
	unsigned short int dest;	//UDPĿ�Ķ˿�
	unsigned short int len;		//UDP����
	unsigned short int check;
}UDP_HEADER;

typedef struct _syntime 	//����ʱ��ͬ�����ݽṹ 
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

typedef struct _playdata	//���岥�����ݽṹ
{
	char *pathname;
	int nSampleRate;
	int nChannels;
	int fmt;
	int isStopplay;  //�ⲿ���ã��Ƿ�ֹͣ����
	int playpos;   //��ǰ����λ�ã���λ ��
	int playstatu;  //״̬��
}PLAY_DATA;
#pragma pack()	//�ر��ֶ��ڴ����

pthread_t id_record,id_alive,id_save,id_play,id_recv;
//sigset_t sigs;
unsigned int recrun,savrun;

TERMINAL_DATA td[CARNO][TEMNO];		//���������ն˵����ݽṹʵ��
MIX_DATA md;	//����������ݽṹʵ��

PLAY_DATA PWD;	//���岥�����ݽṹʵ��

unsigned char wavpath[MAXWAVPATH];	//���嵱ǰ�洢�ļ�·������
unsigned int savelen;		//���嵱ǰ�����ļ������ݴ�С
unsigned char buff_second_save[VOCBUFF];	//��������ļ�����������

unsigned char wavbuff[MAXRECVDATA];	//��WAV���ݻ���,���ڽ����̴߳��ݸ���¼�߳�
unsigned long int sinwavtime;	//�������ݰ�����ʱ�䣬���ڽ����̴߳��ݸ���¼�߳�
unsigned int sinwavIP;	//�������ݰ�IP��ַ�����ڽ����̴߳��ݸ���¼�߳�
unsigned short int wavport;	//�������ݰ��˿ڣ����ڽ����̴߳��ݸ���¼�߳�
struct timeval mixwavtime;	//�������ݰ�����ʱ�䣬���ڽ����̴߳��ݸ���¼�߳�
unsigned int playtime;	//���ſ�ʼʱ��
unsigned char playstr[200];	//�����ļ�·������

unsigned char *dirname[CARNO];	//�ļ�����������

unsigned int isrecording;	//¼��״̬
unsigned int iswavfull40;	//wav�ļ��Ƿ񳬹�4g

unsigned int wavtotalsize;	//WAV�ļ��ܴ�С

unsigned int comfd; 	//��ʾ����fd

extern void *Save_thread(void *arg);	//�����߳�
extern void *Record_thread(void *arg);	//��¼�߳�
extern void *Alive_thread(void *arg);	//�����߳�
extern void *Play_thread(void *arg);	//�����߳�
extern void *Recv_thread(void *arg);	//�����߳�
