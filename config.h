
/*  Squall Hon   2015.11.8  */

/*  ȫ�ֺ궨��  */

#define S 0		//��������
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
#define CARNO 13	//��������
#define TEMNO 4		//ÿ���ն���
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
	}while (0)	//�ļ�ϵͳ�ṹ����������

#define VOCBUFF 15*8192		//����15�뻺���С���ֽڣ�
#define MAXRECVDATA 10240	//�հ������С���ֽڣ�

#define MAXWAVPATH 200		//wav�ļ�·�����ֵ���ֽڣ�
#define MAXSLIPDATA 100		//slip�������ֵ���ֽڣ�

#define SIGVOCEND 10		//��·ģʽ10����޻������ʹ��̣��룩
//#define MIXVOCMUTE 100	  	//����ģʽ100�����޻���������ݣ����룩

#define FILEMAX 8192*3600	//�������ļ�����������ֽڣ�

#define MUTEPKG 0		//��������

#define DEFIP 0x0100007f	//��ʼIP��ַ���ѷ���127.0.0.1
#define DEFMASK 0x00ffffff	//��ʼ����,�ѷ���24λ

#define COMBPS	115200		//��ʾ��������
#define COMNO "/dev/ttyS0"  	//���ں�

#define SYNUDPPORT 60003	//ʱ��ͬ��UDP�˿�
#define ZBUDPPORT 62001		//�鲥UDP�˿�
#define GBUDPPORT 62002		//�㲥UDP�˿�
#define CNGBUDPPORT 62003	//���ڹ㲥UDP�˿�
#define HYUDPPORT 62004		//����UDP�˿�
#define	WSUDPPORT 63001		//����UDP�˿�

#define DIRALARMSIZE 4096	//���̿ռ�澯�ٽ�ֵ���ף�
#define DIRDELSIZE 4301		//���̿ռ�ɾ���ļ��ٽ�ֵ���ף�
#define KEEPSIZE 130		//����ʣ���ļ���С�ٽ�ֵ���ף�

#define T1T2DELTATIME 1000	//�Ƿ�ͬ��ʱ�����룩
#define ALIVEDELTATIME 5	//������Ϣʱ�������룩
#define ALIVERESEND 3		//������Ϣ�ط�����

#define TIMEOUT 1		//���ճ�ʱʱ��

#define UDISKPATH "/UDISK/"	//u��·��
#define WAVDIRPATH "/root/vr/WAV"	//WAV�ļ��о���·��

#define YES 0	//��
#define NO 1	//��

#define TRUE 0	//��
#define FALSE -1	//��

#define OPEN_DSP_FAILED 1
#define SAMPLERATE_STATUS 2
#define SET_SAMPLERATE_FAILED 3
#define CHANNELS_STATUS 4
#define SET_CHANNELS_FAILED 5 
#define FMT_STATUS 6 
#define SET_FMT_FAILED 7
#define OPEN_FILE_FAILED 8  
#define NUM 8192  //һ�ζ�ȡwav���ֽ���
#define PLAY_NO_STOP 0
#define PLAY_STOP 1
#define PLAY_GOON -1

