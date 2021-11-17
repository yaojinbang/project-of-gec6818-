#ifndef _BMP_H_
#define _BMP_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h>
#include <dirent.h>
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;

#pragma pack(1) //����1�ֽڶ���
typedef struct BitFileHeader{
	uint16 bfType;//λͼ��𣬸��ݲ�ͬ�Ĳ���ϵͳ����ͬ����Windows�У����ֶε�ֵ��Ϊ��BM��BMP
	uint32 bfSize;//BMPͼ���ļ��Ĵ�С
	uint16 bfReserved1; 
	uint16 bfReserved2;
	uint32 bfOffBits;//BMPͼ�����ݵĵ�ַ
	uint32 biSize; //��ʾ���ṹ�Ĵ�С
	uint32 biWidth; //λͼ�Ŀ��
	uint32 biHeight; //λͼ�ĸ߶�
	uint16 biPlanes; 
	uint16 biBitCount;//BMPͼ���ɫ���һ�������ö���λ��ʾ��������1��4��8��16��24��32���ֱ��Ӧ��ɫ��16ɫ��256ɫ��16λ�߲�ɫ��24λ���ɫ��32λ��ǿ�����ɫ
	uint32 biCompression; //ѹ����ʽ��0��ʾ��ѹ����1��ʾRLE8ѹ����2��ʾRLE4ѹ����3��ʾÿ������ֵ��ָ�����������
	uint32 biSizeImage; //BMPͼ�����ݴ�С��������4�ı�����ͼ�����ݴ�С����4�ı���ʱ��0��䲹��
	uint32 biXPelsPerMeter; //ˮƽ�ֱ��ʣ���λ����/m
	uint32 biYPelsPerMeter; //��ֱ�ֱ��ʣ���λ����/m
	uint32 biClrUsed; //BMPͼ��ʹ�õ���ɫ��0��ʾʹ��ȫ����ɫ������256ɫλͼ��˵����ֵΪ100h=256
	uint32 biClrImportant;//��Ҫ����ɫ������ֵΪ0ʱ������ɫ����Ҫ������ʹ�õ�ɫ���BMPͼ����˵�����Կ����ܹ���ʾ������ɫʱ����ֵ����������������ʾ��ɫ
} BitHeader;
#pragma pack(0)//����ΪĬ���ֽڶ���

int show_bmp_any(char *name,int x_refe,int y_refe,int wide,int high);
int get_bmp_info(char *bmp_name);
int show_bmp(char *name);


#endif