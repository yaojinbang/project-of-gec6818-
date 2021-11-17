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
	printf("λͼ�Ŀ��:%d\tλͼ�ĸ߶�:%d\n",bmp_info.biWidth,bmp_info.biHeight);
	printf("ˮƽ�ֱ���:%d\t��ֱ�ֱ���:%d\n",bmp_info.biXPelsPerMeter,bmp_info.biYPelsPerMeter);
	close(fd);
	return 0;
}

//��ʾ����800*480���ڵ�bmpͼƬ
int show_bmp_any(char *name,int x_refe,int y_refe,int wide,int high)
{
	if((x_refe+wide>800) || (y_refe+high>480) || x_refe < 0 || y_refe < 0)
	{
		printf("%s��ʾ��������\n", name);
		return -1;
	}
	//����ʾ�����豸�ļ�
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open equipment err!\n");
		return -1;
	}
	
	//��ͼƬ�ļ�
	int fd_bmp = open(name, O_RDWR);
	if(-1 == fd_bmp)
	{
		printf("open picture err!\n");
		return -1;
	}
	
	//ƫ��54�ֽ��ļ�ͷ
	lseek(fd_bmp, 54, SEEK_SET);
	
	//��ȡ�ļ��е���ɫ����
	char buf[wide*high*3];
	read(fd_bmp, buf, wide*high*3);
	
	int lcd_buf_tmp[wide*high];
	int i;
	for(i=0; i<wide*high; i++)
		//				B		     G			    R
		lcd_buf_tmp[i] = buf[i*3] | buf[i*3+1]<<8 | buf[i*3+2]<<16;
	
	int * mmap_bmp = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd_lcd, 0);
	//���з�ת
	int x,y;
	int lcd_buf[800*480] = {0};
	for(y=0; y<high; y++)
		for(x=0; x<wide; x++)
		{
			lcd_buf[x+(high-y-1)*wide]= lcd_buf_tmp[x+y*wide];
		}
		
	
	//������ʼλ��д���ļ�����	
	for(y=0; y<high; y++)
		for(x=0; x<wide; x++)
		{
			mmap_bmp[x+x_refe+(y+y_refe)*800] = lcd_buf[x+y*wide];
		}
	
	
	
	munmap(mmap_bmp, 800*480*4);
	if(close(fd_lcd))
	{
		printf("��ʾ���ر�ʧ��\n");
		return -2;
	}

	if (close(fd_bmp))
	{
		printf("ͼƬ�ر�ʧ��\n");
		return -2;
	}

}

//��ʾbmpͼƬ
int show_bmp(char *name)
{
	
	//����ʾ�����豸�ļ�
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if(-1 == fd_lcd)
	{
		printf("open equipment err!\n");
		return -1;
	}
	
	//��ͼƬ�ļ�
	int fd_bmp = open(name, O_RDWR);
	if(-1 == fd_bmp)
	{
		printf("open picture err!\n");
		return -1;
	}
	
	//ƫ��54�ֽ��ļ�ͷ
	lseek(fd_bmp, 54, SEEK_SET);
	
	//��ȡ�ļ��е���ɫ����
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
	//���з�ת
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
