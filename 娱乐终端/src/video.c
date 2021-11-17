#include "../inc/video.h"
#include "../inc/bmp.h"
#include "../inc/dir.h"
#include "../inc/ts.h"

int flag1 = 0;
int mNum1=0;
int loop_count1 = 0;
char cmd1[30]={0};
int video_select=0;

int mplayer_video()
{
	printf("\033[36m 启动中请稍后 \033[0m\n");
	sleep(2);
	system("clear");//刷屏
	get_video("../yule/video");
	printf("-------\n");
	while(1)
	{
		video_UI();
		scanf("%d",&video_select);
		switch(video_select)
		{
			case 1:
			video_select = 0;   //初始化
			printf("\033[34m 显示所有的视频 \033[0m\n");
			int i;
			for ( i = 0; i < 5; ++i)
			{
				if (strlen(video_list[i]) != 0)
				{
					printf("%s\n",video_list[i]);
				}
				
			}
			break;
			case 2:
			video_select = 0;   //初始化
			printf("\033[34m 播放视频 \033[0m\n");
			printf("\033[34m 请输入要播放的视频序号 \033[0m\n");

			scanf("%d",&mNum1);
			while(mNum1>video_count)
			{
				printf("未找到视频，请重新输入\n");
				scanf("%d",&mNum1);
			}
			bzero(cmd1,30);
			--mNum1;
			printf("播放：%s\n",video_list[mNum1]);
			sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
			system(cmd1);
			video_touch();
			if (flag1 == 1)
			{
				break;
			}
			case 3:
			video_select = 0;   //初始化
			system("killall -KILL mplayer ");
			printf("\033[36m 已退出 \033[0m\n");
			flag1 = 1;
			break;
		}
		if(flag1 == 1)
		{
			flag1 = 0;
			break;
		}
	}
	return 0;
}

int video_touch()
{
	while(1)
	{
		int fdshow;           		
        BitHeader bmp_info;
		fdshow =  open("../yule/screen/video3.bmp",O_RDWR);
        read(fdshow,&bmp_info,54);
        close(fdshow);
		get_ts();
		printf("x%dy%d\n",ts_x,ts_y);
		if(0<ts_x&&ts_x<100&&400<ts_y&&ts_y<480)
		{
			--mNum1;
			if(mNum1<0)
			{
				mNum1=0;	
				printf("这是第一个视频\n");
			}else
			{
				system("killall -KILL mplayer ");	
				printf("播放：%s\n",video_list[mNum1]);
				sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
				system(cmd1);
            	show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(350<ts_x&&ts_x<450&&400<ts_y&&ts_y<480)
		{
			loop_count1++;		
			if(loop_count1<=1)
			{
				printf("\033[34m 暂停播放 \033[0m\n");
				system("killall -STOP mplayer & ");
            	// fdshow =  open("../yule/screen/video3.bmp",O_RDWR);
            	// show_bmp_any("../yule/screen/video3.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}else
			{
				loop_count1 = 0;
				printf("\033[34m 恢复播放 \033[0m\n");
				system("killall -CONT mplayer & ");
            	// show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(705<ts_x&&ts_x<770&&400<ts_y&&ts_y<480)
		{
			++mNum1;
			if(mNum1>video_count-1)
			{
				mNum1=video_count-1;
				printf("这是最后一个视频\n");
			}else
			{
				system("killall -KILL mplayer ");	
				printf("播放：%s\n",video_list[mNum1]);
				sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
				system(cmd1);
            	show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(700<ts_x&&ts_x<800&&0<ts_y&&ts_y<100)
		{
			system("killall -KILL mplayer ");
			printf("\033[36m 已退出 \033[0m\n");
			flag1 = 1;
			break;
		}

	}
}

/*   
mplayer ‐loop 0 ‐slave ‐quiet ‐geometry 0:0 ‐zoom ‐x 400 ‐y 300 .mp4 & 
# ‐zoom :允许播放（权限） 
#‐x :播放的帧宽度 
#‐y :播放的帧高度 
#‐geometry :表示播放的起始位置 显示屏的坐标


system("mplayer 1.avi "); //播放视屏 
system("mplayer 1.avi &"); //后台播放视屏 
system("killall ‐STOP mplayer & "); //暂停 
system("killall ‐CONT mplayer & "); //继续 
system("killall ‐KILL mplayer "); //结束 

 */