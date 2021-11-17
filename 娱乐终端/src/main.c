#include "../inc/bmp.h"
#include "../inc/ts.h"
#include "../inc/dir.h"
#include "../inc/music.h"
#include "../inc/video.h"
#include "../inc/camera_lib_inc/camera.h"
#include <pthread.h>

char filename[50]={0};
int camera_flag = 0;
int camera_select=0;
int xiangce_flag = 0;
int i = 0;

void *xiangce_fun(void *arg)
{
    for(i = 0;i < 20; )
            {
                if(strlen(bmp_list[i]))
                {  
                    int fdshow;
                    int fdshow1;
                    BitHeader bmp_info;	
                    BitHeader bmp_info1;
                    sprintf(filename,"../yule/image/%s",bmp_list[i]);	
                    fdshow =  open(filename,O_RDWR);
                    read(fdshow,&bmp_info,54);
                    close(fdshow);
	                show_bmp_any(filename,100,50,bmp_info.biWidth,bmp_info.biHeight);	
                    fdshow1 =  open("../yule/screen/back.bmp",O_RDWR);
                    read(fdshow1,&bmp_info1,54);
                    close(fdshow1);
                    show_bmp_any("../yule/screen/back.bmp",700,0,bmp_info1.biWidth,bmp_info1.biHeight);
                    show_bmp_any("../yule/screen/front.bmp",0,180,bmp_info1.biWidth,bmp_info1.biHeight);
                    show_bmp_any("../yule/screen/next.bmp",700,180,bmp_info1.biWidth,bmp_info1.biHeight);
                    show_bmp_any(filename,100,50,bmp_info.biWidth,bmp_info.biHeight);	
                    get_ts();
                    if(0<ts_x&&ts_x<60&&210<ts_y&&ts_y<270)
                    {
                        i--;
                        if(i<0)
                        {
                            printf("前面已经没有图片了\n");
                            i=0;
                        }
                    }else if(740<ts_x&&ts_x<800&&210<ts_y&&ts_y<270)
                    {
                        i++;
                        if(i>bmp_count-1)
                        {
                            printf("后面已经没有图片了\n");
                            i=bmp_count-1;
                        }
                    }else if(740<ts_x&&ts_x<800&&0<ts_y&&ts_y<60)
                    {
                        xiangce_flag=1;
                        ts_x=0;ts_y=0;
                        break;
                    }
                }
            }
}

void *shoushi_fun(void *arg)
{
    int fd = open("/dev/IIC_drv",O_RDWR);
    if(fd == -1)
    {
        perror("open");
        return 0;
    }
    
    char buf;
    int j = 0;
    for(i = 0;i < 20; )
    {
        if(strlen(bmp_list[i]))
        {
            int fdshow;
            BitHeader bmp_info;	
            sprintf(filename,"../yule/image/%s",bmp_list[i]);
            fdshow =  open(filename,O_RDWR);
            read(fdshow,&bmp_info,54);
            close(fdshow);
            show_bmp_any(filename,100,50,bmp_info.biWidth,bmp_info.biHeight);	
            read(fd,&buf,1);
            if(buf>=1 && buf<=9)
            {
                printf("buf = %x\n",buf);
                switch (buf)
                {
                    case 1:j=1;printf("进行上操作：下一张\n");break;
                    case 2:j=2;printf("进行下操作：上一张\n");break;
                    case 3:printf("左\n");break;
                    case 4:j=3;printf("进行右操作：退出\n");break;
                    case 5:printf("前\n");break;
                    case 6:printf("后\n");break;
                    case 7:printf("顺时针\n");break;
                    case 8:printf("逆时针\n");break;
                    case 9:printf("挥手\n");break;  
                    default:printf("==============\n");break;
                }
            }
            if(j == 1)
            {
                j = 0;
                i--;
                if(i<0)
                {
                    printf("前面已经没有图片了\n");
                    i=0;
                }
            }else if(j == 2)
            {
                j = 0;
                i++;
                if(i>bmp_count-1)
                {
                    printf("后面已经没有图片了\n");
                    i=bmp_count-1;
                }
            }else if(j == 3)
            {
                j = 0;
                xiangce_flag=1;
                break;
            }
        }
    }
    close(fd);
}

int main(int argc, char const *argv[])
{
    //显示开始界面
    // show_bmp("欢迎使用娱乐终端1.0版本.bmp");

    
    // // 初始化，将音乐与视频信息存入数组
    // get_music("../music");
    // get_video("../video");

    while (1)
    {
        show_bmp("../yule/screen/shouye.bmp");
        get_ts();
        // 将触摸屏划分为四块
        if (54<ts_x&&ts_x<190&&175<ts_y&&ts_y<320)
        {
            /*相册 */
            ts_x=0;ts_y=0;
            get_bmp("../yule/image");
            pthread_t TID1,TID2;
            pthread_create(&TID1, NULL,xiangce_fun, NULL);
            pthread_create(&TID2, NULL,shoushi_fun, NULL);
            while(1)
            {
                if(xiangce_flag == 1)
                {
                    xiangce_flag = 0;
                    break;
                }
            }
            pthread_cancel(TID1); 
            pthread_cancel(TID2); 
        }
        else if (235<ts_x&&ts_x<360&&175<ts_y&&ts_y<320)
        {
            /*音乐 */
            ts_x=0;ts_y=0;
            for(int i = 0;i < 1; ++i)
            {
            show_bmp("../yule/screen/yinyue1.bmp");
            // int fdshow;
            // BitHeader bmp_info;		
            // fdshow =  open("../yule/screen/quit.bmp",O_RDWR);
            // read(fdshow,&bmp_info,54);
            // close(fdshow);
            // show_bmp_any("../yule/screen/quit.bmp",740,0,bmp_info.biWidth,bmp_info.biHeight);
            madplay_music();
            if(720<ts_x&&ts_x<800&&0<ts_y&&ts_y<40)
            {
                ts_x=0;ts_y=0;
                break;
            }
            }
        }
        else if (420<ts_x&&ts_x<550&&175<ts_y&&ts_y<320)
        {
            ts_x=0;ts_y=0;
            for(int i = 0;i < 1; ++i)
            {
            show_bmp("../yule/screen/video1.bmp");
            mplayer_video();
            if(720<ts_x&&ts_x<800&&0<ts_y&&ts_y<40)
            {
                ts_x=0;ts_y=0;
                break;
            }
            }
        }
        else if (590<ts_x&&ts_x<720&&175<ts_y&&ts_y<320)
        {
            /*相机 */
            ts_x = 0;ts_y = 0;
            save_count=1;
	        printf("\033[36m 启动中请稍后 \033[0m\n");
	        sleep(2);
	        system("clear");//刷屏
	        printf("-------\n");
            camera_UI();
			scanf("%d",&camera_select);
            if (camera_select == 1)
            {
                while(1)
                {
                    camera_select == 0;
                    show_bmp("../yule/screen/xiangji.bmp");
                    //1、打开摄像头
	                open_camera("/dev/video7");
	                //2、运行摄像头
	                camera_working();	
	                //3、关闭摄像头
	                close_camera();	
                    while(1)
                    {
                        get_ts();
                        if(664<ts_x&&ts_x<750&&200<ts_y&&ts_y<300)
                        {
                            ts_x = 0;ts_y = 0;
                            break;
                        }else if(710<ts_x&&ts_x<800&&0<ts_y&&ts_y<80)
                        {
                            ts_x = 0;ts_y = 0;
                            camera_flag = 1;
                            break;
                        }
                    }
                    if(camera_flag == 1)
                    {
                        camera_flag = 0;
                        break;
                    }
                }
            }else if(camera_select == 2)
            {
               camera_select == 0;
                while(1)
                {
                    show_bmp("../yule/screen/xiangji.bmp");
                    while(1)
                    {
                        get_ts();
                        if(700<ts_x&&ts_x<800&&200<ts_y&&ts_y<300)
                        {
                            ts_x = 0;ts_y = 0;
                            break;
                        }
                    }
                    show_bmp("../yule/screen/ruxiang.bmp");
                    //1、打开摄像头
	                open_camera("/dev/video7");
	                //2、运行摄像头
	                camera_working1();	
	                //3、关闭摄像头
	                close_camera();	
                    while(1)
                    {
                        get_ts();
                        if(700<ts_x&&ts_x<800&&200<ts_y&&ts_y<300)
                        {
                            ts_x = 0;ts_y = 0;
                            break;
                        }else if(710<ts_x&&ts_x<800&&0<ts_y&&ts_y<80)
                        {
                            ts_x = 0;ts_y = 0;
                            camera_flag = 1;
                            break;
                        }
                    }
                    if(camera_flag == 1)
                    {
                        camera_flag = 0;
                        break;
                    }
                }
            }
        }
    }
    



    return 0;
}


