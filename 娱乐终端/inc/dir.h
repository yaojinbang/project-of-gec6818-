#ifndef _DIR_H_
#define _DIR_H_
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
extern char music_list[20][30];
extern char video_list[20][30];
extern char bmp_list[20][30];
extern int video_count;
extern int music_count;
extern int bmp_count;

int get_video(char *pathname);
int get_music(char *pathname);
int get_bmp(char *pathname);
#endif

/* 
    struct dirent { 
        ino_t d_ino;    // �ļ�������
        off_t d_off;    // Ŀ¼��ƫ���� 
        unsigned short d_reclen; // ��Ŀ¼����? 
        unsigned char d_type;   // �ļ����� 
        char d_name[256];   // �ļ��� }; 
*/

