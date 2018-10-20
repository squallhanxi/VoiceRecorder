
/*  Squall Hon   2015.11.5  */

/*  串口代码头文件  */

#include "global.h"

extern int UART0_Open(int fd,char* port);

extern void UART0_Close(int fd);

extern int UART0_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);

extern int UART0_Init(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity);

extern int UART0_Recv(int fd, char *rcv_buf,int data_len);

extern int UART0_Send(int fd, char *send_buf,int data_len);


