#include "head.h"
#include <sys/types.h>
//#include<sqlite3.h>
#include <dirent.h>
#include <termios.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include"input.h"
#include"input-event-codes.h"
volatile unsigned int cardid ;
static struct timeval timeout;
#define DEV_PATH   "/dev/ttySAC1"
int readRFID();
int show_bmp_any(int fd);
int read_input();
int a[10]={0};
char b[10]={0};
int bmp1();
int bmp2();
int bmp3();
int bmp4();
int bmp5();
int bmp6();
int ok();
void fengmingqi();
typedef struct RFID
{
	int id;
	int money;
}card;

int main(int argc, char const *argv[])
{
	int x=0,y=0;
	// //打开数据库
	// sqlite3 *db;
 //    char *errmsg = NULL;
 //    int ret = sqlite3_open("card_inf.db",&db);
 //    ret = sqlite3_exec(db,"create table if not exists card(id text primary key,money int);",NULL,NULL,&errmsg);
 //    ret = sqlite3_exec(db,"insert or replace into card values('a77b7ee7',100);",NULL,NULL,&errmsg);
 //    ret = sqlite3_exec(db,"insert or replace into card values('a65b8a97',100);",NULL,NULL,&errmsg);
 //    ret = sqlite3_exec(db,"insert or replace into card values('a71b8b57',100);",NULL,NULL,&errmsg);
	// //将数据库数据读取
	// char **resultp = NULL;
	// int nrow,ncolumn;
	// ret = sqlite3_get_table(db, "select *from card;",&resultp,&nrow,&ncolumn,&errmsg);		
	// for(int i = 0;i<(nrow+1);i++)
	// {	
	// 	for (int j = 0; j < ncolumn; j++)
	// 	{
	// 		/* code */
	// 	}
	// }
 //    sqlite3_free(errmsg);
 //    sqlite3_free_table(resultp);	
		struct RFID card[3];

		card[0].id = 0xa77b7ee7;
		card[0].money = 100;
		card[1].id = 0xa71b8b57;
		card[1].money = 100;
		card[2].id = 0xa65b8a97;
		card[2].money = 100;
	//判断识别成功与否
	// char **resultp = NULL;
	// int nrow,ncolumn;
	// ret = sqlite3_get_table(db, "select *from card;",&resultp,&nrow,&ncolumn,&errmsg);
	// sleep(2);	
	// int  i;		
	// for(i = 2;i<=6;i = i+2)
	// {	

	// 	if(strcmp(b,resultp[i]) == 0 )
	// 	{
	// 		printf("RFID open!\n");

	// 	}
	// 	else
	// 	{
	// 		printf("RFID false!\n");
	// 	}
	// }
 //    sqlite3_free(errmsg);
 //    sqlite3_free_table(resultp);














	//操作界面
	while(1)
	{
		//打开初始界面
		bmp1();
		//打开LCD并读取触摸屏数据
		read_input();
		x=a[0];y=a[1];
		//读卡比对id花钱
		int id = readRFID();
		int i,m;	
		for ( i = 0; i < 3; i++)
		{
			if (id==card[i].id)
			{
				m=card[i].money;
				break;
			}
		}
		//printf("x=%d,y=%d\n",x,y );
		//判断充值与刷卡界面选择
		if (x>400)   
		{	
			m-=10;
			card[i].money=m;
			printf("balace:%d\n",card[i].money);	
			//刷卡5s后返回初始界面
			
			bmp3();	
			fengmingqi();
			sleep(5);
			bmp1();
		}else         //充值
		{	
			//打开充值界面
			bmp2();
			read_input();
			x=a[0];y=a[1];
			printf("x = %d, y = %d", x, y);
			if ( x<400 &&  y<240)
			{	
				m+=5;
				//printf("Be recharged successfully:%d\n",m);
				ok();
				// break;
			}else if (x>400 && y<240)
			{
				m+=10;
				//printf("Be recharged successfully:%d\n",m);
				ok();
				// break;
			}else if (x<400 && y>240)
			{
				m+=20;
				//printf("Be recharged successfully:%d\n",m);
				ok();
				// break;
			}else
			{
				m+=50;
				//printf("Be recharged successfully:%d\n",m);
				ok();
				// break;
			}	
			card[i].money=m;  
			printf("Be recharged successfully:%d\n",card[i].money);		

			
		}
	}
	
	

	
	return 0;
}

int ok()//充值成功并返回初始界面
{
	bmp4();
	sleep(1);
}
int bmp1()//选择充值与刷卡界面
{
	int fd =  open("1.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int bmp2()//选择充值金额
{
	int fd =  open("2.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int bmp3()//刷卡界面
{
	int fd =  open("3.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int bmp4()//充值成功
{
	int fd =  open("7.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int bmp5()//刷卡成功
{
	int fd =  open("5.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int bmp6()//刷卡失败
{
	int fd =  open("6.bmp",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	show_bmp_any(fd);
	close(fd);
}
int show_bmp_any(int fd)//显示图片
{
	
	//打开显示屏的设备文件
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open err!\n");
		return -1;
	}
	
	// //打开图片文件
	// int fd_bmp = open(name, O_RDWR);
	// if(-1 == fd_bmp)
	// {
	// 	printf("open err!\n");
	// 	return -1;
	// }
	
	//偏移54字节文件头
	lseek(fd, 54, SEEK_SET);
	
	//读取文件中的颜色数据
	char buf[800*480*3];
	read(fd, buf, 800*480*3);
	
	int lcd_buf_tmp[800*480];
	int i;
	for(i=0; i<800*480; i++)
		//				B		     G			    R
		lcd_buf_tmp[i] = buf[i*3] | buf[i*3+1]<<8 | buf[i*3+2]<<16;
	
	int * mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd_lcd, 0);
	//按行翻转
	int x,y;
	int lcd_buf[800*480] = {0};
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)
		{
			lcd_buf[x+(479-y)*800]= lcd_buf_tmp[x+y*800];
		}
		
	
	//根据起始位置写入文件数据	
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)
		{
			mmap_bmp[x+y*800] = lcd_buf[x+y*800];
		}
	
	munmap(mmap_bmp, 800*480*4);
    if(close(fd_lcd))
	{
		printf("显示屏关闭失败\n");
		return -2;
	}

	if (close(fd))
	{
		printf("图片关闭失败\n");
		return -2;
	}
}

int read_input()//读取触摸屏数据
{	
	//打开LCD
	int fd = open("/dev/input/event0",O_RDWR);
	if (fd == -1)
	{
		printf("open LCD faulse\n");
		return -1;
	}
	struct input_event touch_info;
	int count = 0;

	while(1){
		
		read(fd,&touch_info,sizeof(touch_info));
		//打印触摸屏数据
		if(touch_info.type == EV_ABS)//判断是否为触摸屏
		{
			if(touch_info.code == ABS_X)//判断是否为X
			{
				printf("LCD.X:%d\n", touch_info.value*800/1024);
				a[0]=touch_info.value*800/1024;
				count++;
			}
			else if(touch_info.code == ABS_Y)//判断是否为Y
			{
				printf("LCD.Y:%d\n", touch_info.value*480/600);
				a[1]=touch_info.value*480/600;
				count++;
			}
		}
		 if(count == 2)
		 {
		
		 	break;
		 }
	}

	//关闭触摸屏
	close(fd);
}
//设置窗口参数，读卡器:9600速率 
void init_tty(int fd)
{    
	//声明设置串口的结构体
	struct termios termios_new;
	//先清空该结构体
	bzero( &termios_new, sizeof(termios_new));
	//	cfmakeraw()设置终端属性，就是设置termios结构中的各个参数。
	cfmakeraw(&termios_new);
	//设置波特率
	//termios_new.c_cflag=(B9600);
	cfsetispeed(&termios_new, B9600);
	cfsetospeed(&termios_new, B9600);
	//CLOCAL和CREAD分别用于本地连接和接受使能，因此，首先要通过位掩码的方式激活这两个选项。    
	termios_new.c_cflag |= CLOCAL | CREAD;
	//通过掩码设置数据位为8位
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 
	//设置无奇偶校验
	termios_new.c_cflag &= ~PARENB;
	//一位停止位
	termios_new.c_cflag &= ~CSTOPB;
	tcflush(fd,TCIFLUSH);
	// 可设置接收字符和等待时间，无特殊要求可以将其设置为0
	termios_new.c_cc[VTIME] = 1;
	termios_new.c_cc[VMIN] = 1;
	// 用于清空输入/输出缓冲区
	tcflush (fd, TCIFLUSH);
	//完成配置后，可以使用以下函数激活串口设置
	if(tcsetattr(fd,TCSANOW,&termios_new) )
		printf("Setting the serial1 failed!\n");

}
//计算校验和
unsigned char CalBCC(unsigned char *buf, int n)
{
	int i;
	unsigned char bcc=0;
	for(i = 0; i < n; i++)
	{
		bcc ^= *(buf+i);
	}
	return (~bcc);
}
//  发送A命令
int PiccRequest(int fd)
{
	unsigned char WBuf[128], RBuf[128];
	int  ret, i;
	fd_set rdfd;
	
	memset(WBuf, 0, 128);
	memset(RBuf,1,128);
	WBuf[0] = 0x07;	//帧长= 7 Byte
	WBuf[1] = 0x02;	//包号= 0 , 命令类型= 0x01
	WBuf[2] = 0x41;	//命令= 'A'
	WBuf[3] = 0x01;	//信息长度= 1
	WBuf[4] = 0x52;	//请求模式:  ALL=0x52
	WBuf[5] = CalBCC(WBuf, WBuf[0]-2);		//校验和
	WBuf[6] = 0x03; 	//结束标志

	FD_ZERO(&rdfd);
	FD_SET(fd,&rdfd);

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	write(fd, WBuf, 7);;
	ret = select(fd + 1,&rdfd, NULL,NULL,&timeout);// select什么情况返回-1 ？返回0？返回其它值？
	switch(ret)
	{
		case -1: 
			perror("select error\n");
			break;
		case  0:
			printf("Request timed out.\n");
			break;
		default:
			ret = read(fd, RBuf, 8);
			if (ret < 0)
			{
				printf("ret = %d, 0x%x\n", ret, errno);
				break;
			}
			if (RBuf[2] == 0x00)	 	//应答帧状态部分为0 则请求成功
			{
				// 卡的类型
				return 0;
			}
			break;
	}
	return -1;}

//防碰撞，获取范围内最大ID
int PiccAnticoll(int fd)
{
	unsigned char WBuf[128], RBuf[128];
	int ret, i;
	fd_set rdfd;;
	memset(WBuf, 0, 128);
	memset(RBuf,0,128);
	WBuf[0] = 0x08;	//帧长= 8 Byte
	WBuf[1] = 0x02;	//包号= 0 , 命令类型= 0x01
	WBuf[2] = 0x42;	//命令= 'B'
	WBuf[3] = 0x02;	//信息长度= 2
	WBuf[4] = 0x93;	//防碰撞0x93 --一级防碰撞
	WBuf[5] = 0x00;	//位计数0
	WBuf[6] = CalBCC(WBuf, WBuf[0]-2);		//校验和
	WBuf[7] = 0x03; 	//结束标志
	
	FD_ZERO(&rdfd);
	FD_SET(fd,&rdfd);
	write(fd, WBuf, 8);

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	ret = select(fd + 1,&rdfd, NULL,NULL,&timeout);
	switch(ret)
	{
		case -1:
			perror("select error\n");
			break;
		case  0:
			perror("Timeout:");
			break;
		default:
			ret = read(fd, RBuf, 10);
			if (ret < 0)
			{
				printf("ret = %d, 0x%x\n", ret, errno);
				break;
			}
			
			for(i=0; i<10 ;i++)
				//printf("[%d] %x \n", i,RBuf[i]);
			
			if (RBuf[2] == 0x00) //应答帧状态部分为0 则获取ID 成功
			{
				// 卡号
				cardid = (RBuf[7]<<24) | (RBuf[6]<<16) | (RBuf[5]<<8) | RBuf[4];//保存得到的卡ID
				return 0;
			}
	}
	return -1;
}
//读取RFID卡信息
int readRFID()
{
	int ret, i;
	int fd;

	fd = open(DEV_PATH, O_RDWR | O_NOCTTY | O_NONBLOCK);//非阻塞,发送完命令后即使没有卡回应，也不会阻塞
	if (fd < 0)
	{
		fprintf(stderr, "Open Gec210_ttySAC1 fail!\n");
		return -1;
	}
	//初始化串口
	init_tty(fd);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while(1) //多次请求
	{
		//请求天线范围的卡   发送A命令
		if ( PiccRequest(fd)==-1 )
		{
			printf("The request failed!\n");
			tcflush (fd, TCIFLUSH);
			sleep(1);
			continue; // 没有卡回应，说明不需要读卡ID，则可以继续去发送A命令寻卡
		}
		
		//进行防碰撞，获取天线范围内最大的ID   发送B命令
		if( PiccAnticoll(fd)==-1 )
		{
			printf("Couldn't get card-id!\n");
			tcflush (fd, TCIFLUSH);
		}
		else
			break;
		
		usleep(500000);
	}
		
	printf("card ID = %x\n", cardid);
	return cardid;
	close(fd);
}

void fengmingqi()
{
	int fd = open("/dev/beep", O_RDWR);
		if(fd == -1)
	{
		perror("open:");
		exit(0);
	}
	ioctl(fd, ON, 1);
	usleep(5000);
	// 关闭蜂鸣器
	ioctl(fd, OFF, 1);
	
}