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
	printf("\033[36m ���������Ժ� \033[0m\n");
	sleep(2);
	system("clear");//ˢ��
	get_video("../yule/video");
	printf("-------\n");
	while(1)
	{
		video_UI();
		scanf("%d",&video_select);
		switch(video_select)
		{
			case 1:
			video_select = 0;   //��ʼ��
			printf("\033[34m ��ʾ���е���Ƶ \033[0m\n");
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
			video_select = 0;   //��ʼ��
			printf("\033[34m ������Ƶ \033[0m\n");
			printf("\033[34m ������Ҫ���ŵ���Ƶ��� \033[0m\n");

			scanf("%d",&mNum1);
			while(mNum1>video_count)
			{
				printf("δ�ҵ���Ƶ������������\n");
				scanf("%d",&mNum1);
			}
			bzero(cmd1,30);
			--mNum1;
			printf("���ţ�%s\n",video_list[mNum1]);
			sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
			system(cmd1);
			video_touch();
			if (flag1 == 1)
			{
				break;
			}
			case 3:
			video_select = 0;   //��ʼ��
			system("killall -KILL mplayer ");
			printf("\033[36m ���˳� \033[0m\n");
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
				printf("���ǵ�һ����Ƶ\n");
			}else
			{
				system("killall -KILL mplayer ");	
				printf("���ţ�%s\n",video_list[mNum1]);
				sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
				system(cmd1);
            	show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(350<ts_x&&ts_x<450&&400<ts_y&&ts_y<480)
		{
			loop_count1++;		
			if(loop_count1<=1)
			{
				printf("\033[34m ��ͣ���� \033[0m\n");
				system("killall -STOP mplayer & ");
            	// fdshow =  open("../yule/screen/video3.bmp",O_RDWR);
            	// show_bmp_any("../yule/screen/video3.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}else
			{
				loop_count1 = 0;
				printf("\033[34m �ָ����� \033[0m\n");
				system("killall -CONT mplayer & ");
            	// show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(705<ts_x&&ts_x<770&&400<ts_y&&ts_y<480)
		{
			++mNum1;
			if(mNum1>video_count-1)
			{
				mNum1=video_count-1;
				printf("�������һ����Ƶ\n");
			}else
			{
				system("killall -KILL mplayer ");	
				printf("���ţ�%s\n",video_list[mNum1]);
				sprintf(cmd1,"mplayer -loop 0 -slave -quiet -geometry 0:0 -zoom -x 700 -y 380 video/%s &",video_list[mNum1]);
				system(cmd1);
            	show_bmp_any("../yule/screen/video2.bmp",640,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(700<ts_x&&ts_x<800&&0<ts_y&&ts_y<100)
		{
			system("killall -KILL mplayer ");
			printf("\033[36m ���˳� \033[0m\n");
			flag1 = 1;
			break;
		}

	}
}

/*   
mplayer �\loop 0 �\slave �\quiet �\geometry 0:0 �\zoom �\x 400 �\y 300 .mp4 & 
# �\zoom :�����ţ�Ȩ�ޣ� 
#�\x :���ŵ�֡��� 
#�\y :���ŵ�֡�߶� 
#�\geometry :��ʾ���ŵ���ʼλ�� ��ʾ��������


system("mplayer 1.avi "); //�������� 
system("mplayer 1.avi &"); //��̨�������� 
system("killall �\STOP mplayer & "); //��ͣ 
system("killall �\CONT mplayer & "); //���� 
system("killall �\KILL mplayer "); //���� 

 */