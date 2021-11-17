#ifndef __CAMERA_H
#define __CAMERA_H

/*
	1��ͷ�ļ�
	2���궨��
	3����������
	....
*/
#include <stdio.h>
#include "jpeglib.h"
#include "yuyv.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <linux/input.h>
#include "camera_lcd.h"
#include <pthread.h>

extern int camera_count;
extern int save_count;
extern char camera_filename[50];

//1��������ͷ
int open_camera(char *pathname_camera);
//2����������ͷ
int camera_working(void);
//3���ر�����ͷ
int close_camera(void);

int camera_working1(void);

int save_jpg();

int save_jpg1();

void camera_UI();

#endif /* __CAMERA_H */