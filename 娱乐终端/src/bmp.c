#include "../inc/bmp.h"

BitHeader bmp_info;
int get_bmp_info(char *bmp_name)
{
	
	int fd =  open(bmp_name,O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	printf("sizeof(BitHeader) = %ld\n",sizeof(BitHeader));

	read(fd,&bmp_info,54);
	printf("位图的宽度:%d\t位图的高度:%d\n",bmp_info.biWidth,bmp_info.biHeight);
	printf("水平分辨率:%d\t垂直分辨率:%d\n",bmp_info.biXPelsPerMeter,bmp_info.biYPelsPerMeter);
	close(fd);
	return 0;
}

//显示任意800*480以内的bmp图片
int show_bmp_any(char *name,int x_refe,int y_refe,int wide,int high)
{
	if((x_refe+wide>800) || (y_refe+high>480) || x_refe < 0 || y_refe < 0)
	{
		printf("%s显示设置有误\n", name);
		return -1;
	}
	//打开显示屏的设备文件
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open equipment err!\n");
		return -1;
	}
	
	//打开图片文件
	int fd_bmp = open(name, O_RDWR);
	if(-1 == fd_bmp)
	{
		printf("open picture err!\n");
		return -1;
	}
	
	//偏移54字节文件头
	lseek(fd_bmp, 54, SEEK_SET);
	
	//读取文件中的颜色数据
	char buf[wide*high*3];
	read(fd_bmp, buf, wide*high*3);
	
	int lcd_buf_tmp[wide*high];
	int i;
	for(i=0; i<wide*high; i++)
		//				B		     G			    R
		lcd_buf_tmp[i] = buf[i*3] | buf[i*3+1]<<8 | buf[i*3+2]<<16;
	
	int * mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd_lcd, 0);
	//按行翻转
	int x,y;
	int lcd_buf[800*480] = {0};
	for(y=0; y<high; y++)
		for(x=0; x<wide; x++)
		{
			lcd_buf[x+(high-y-1)*wide]= lcd_buf_tmp[x+y*wide];
		}
		
	
	//根据起始位置写入文件数据	
	for(y=0; y<high; y++)
		for(x=0; x<wide; x++)
		{
			mmap_bmp[x+x_refe+(y+y_refe)*800] = lcd_buf[x+y*wide];
		}
	
	
	
	munmap(mmap_bmp, 800*480*4);
	if(close(fd_lcd))
	{
		printf("显示屏关闭失败\n");
		return -2;
	}

	if (close(fd_bmp))
	{
		printf("图片关闭失败\n");
		return -2;
	}

}

//显示bmp图片
int show_bmp(char *name)
{
	
	//打开显示屏的设备文件
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open equipment err!\n");
		return -1;
	}
	
	//打开图片文件
	int fd_bmp = open(name, O_RDWR);
	if(-1 == fd_bmp)
	{
		printf("open picture err!\n");
		return -1;
	}
	
	//偏移54字节文件头
	lseek(fd_bmp, 54, SEEK_SET);
	
	//读取文件中的颜色数据
	char buf[800*480*3] = {0};
	read(fd_bmp, buf, 800*480*3);
	
	int lcd_buf_tmp[800*480] = {0};
	int i;
	for(i=0; i<800*480; i++)
		//				B		     G			    R
		lcd_buf_tmp[i] = buf[i*3] | buf[i*3+1]<<8 | buf[i*3+2]<<16;
	
	int * mmap_bmp = mmap(	NULL, 
							800*480*4, 
							PROT_READ|PROT_WRITE, 
							MAP_SHARED, 
							fd_lcd, 0);
	//按行翻转
	int lcd_buf[800*480] = {0};
	int x,y;
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)
			mmap_bmp[x+(479-y)*800] = lcd_buf_tmp[x+y*800];
	

	munmap(mmap_bmp, 800*480*4);
	
	if(close(fd_lcd))
	{
		printf("close lcd err!\n");
		return -2;
	}
	if(close(fd_bmp))
	{
		printf("close picture err!\n");
		return -2;
	}
}
