#include "../inc/music.h"
#include "../inc/bmp.h"
#include "../inc/dir.h"
#include "../inc/ts.h"

int flag = 0;
int mNum=0;
int loop_count = 0;
char cmd[30]={0};
int music_select=0;

int madplay_music()
{
	printf("\033[36m ���������Ժ� \033[0m\n");
	sleep(2);
	system("clear");//ˢ��
	get_music("../yule/music");
	printf("-------\n");
	while(1)
	{
		music_UI();
		scanf("%d",&music_select);
		switch(music_select)
		{
			case 1:
			music_select = 0;   //��ʼ��
			printf("\033[34m ��ʾ���е����� \033[0m\n");
			int i;
			for ( i = 0; i < 5; ++i)
			{
				if (strlen(music_list[i]) != 0)
				{
					printf("%s\n",music_list[i]);
				}
				
			}
			break;
			case 2:
			music_select = 0;   //��ʼ��
			printf("\033[34m �������� \033[0m\n");
			printf("\033[34m ������Ҫѭ�����ŵ�������� \033[0m\n");

			scanf("%d",&mNum);
			while(mNum>music_count)
			{
				printf("δ�ҵ�����������������\n");
				scanf("%d",&mNum);
			}
			bzero(cmd,30);
			--mNum;
			printf("���ţ�%s\n",music_list[mNum]);
			sprintf(cmd,"madplay music/%s  -r &",music_list[mNum]);
			// system("killall -9 madplay");	
			system(cmd);
			music_touch();
			if (flag == 1)
			{
				break;
			}
			case 3:
			music_select = 0;   //��ʼ��
			printf("\033[34m �������� \033[0m\n");
			printf("\033[34m ������Ҫ���ŵ�������� \033[0m\n");

			scanf("%d",&mNum);
			while(mNum>music_count)
			{
				printf("δ�ҵ�����������������\n");
				scanf("%d",&mNum);
			}
			bzero(cmd,30);
			--mNum;
			printf("���ţ�%s\n",music_list[mNum]);
			sprintf(cmd,"madplay music/%s &",music_list[mNum]);
			system(cmd);
			music_touch();
			if (flag == 1)
			{
				break;
			}
			break;
			case 4:
			music_select = 0;   //��ʼ��
			printf("\033[34m ֹͣ���� \033[0m\n");
			system("killall -9 madplay");	
			break;
			case 5:
			music_select = 0;   //��ʼ��
			system("killall -9 madplay");
			printf("\033[36m ���˳� \033[0m\n");
			flag = 1;
			break;
		}
		if(flag == 1)
		{
			flag = 0;
			break;
		}
	}
	return 0;
}

int music_touch()
{
	while(1)
	{
		get_ts();
		printf("x%dy%d\n",ts_x,ts_y);
		if(120<ts_x&&ts_x<270&&310<ts_y&&ts_y<480)
		{
			--mNum;
			if(mNum<0)
			{
				mNum=0;	
				printf("���ǵ�һ�׸�\n");
			}else
			{
				system("killall -9 madplay");	
				printf("���ţ�%s\n",music_list[mNum]);
				sprintf(cmd,"madplay music/%s  -r &",music_list[mNum]);
				system(cmd);
			}
		}else if(320<ts_x&&ts_x<480&&310<ts_y&&ts_y<480)
		{
			loop_count++;
			if(loop_count<=1)
			{
				printf("\033[34m ��ͣ���� \033[0m\n");
				system("killall -SIGSTOP madplay &");
				// show_bmp("../yule/screen/yinyue2.bmp");
           		// int fdshow;
        		// BitHeader bmp_info;		
            	// fdshow =  open("../yule/screen/quit.bmp",O_RDWR);
            	// read(fdshow,&bmp_info,54);
            	// close(fdshow);
            	// show_bmp_any("../yule/screen/quit.bmp",740,0,bmp_info.biWidth,bmp_info.biHeight);
			}else
			{
				loop_count = 0;
				printf("\033[34m �ָ����� \033[0m\n");
				system("killall -SIGCONT madplay &");
				show_bmp("../yule/screen/yinyue1.bmp");
           		// int fdshow;
            	// BitHeader bmp_info;		
            	// fdshow =  open("../yule/screen/quit.bmp",O_RDWR);
            	// read(fdshow,&bmp_info,54);
            	// close(fdshow);
            	// show_bmp_any("../yule/screen/quit.bmp",740,0,bmp_info.biWidth,bmp_info.biHeight);
			}
		}else if(520<ts_x&&ts_x<660&&310<ts_y&&ts_y<480)
		{
			++mNum;
			if(mNum>music_count-1)
			{
				mNum=music_count-1;
				printf("�������һ�׸�\n");
			}else
			{
				system("killall -9 madplay");	
				printf("���ţ�%s\n",music_list[mNum]);
				sprintf(cmd,"madplay music/%s  -r &",music_list[mNum]);
				system(cmd);
			}
		}
		// else if(720<ts_x&&ts_x<760&&0<ts_y&&ts_y<40)
		// {
		// 	flag = 1;
		// 	break;
		// }
		else if(700<ts_x&&ts_x<800&&0<ts_y&&ts_y<80)
		{
			system("killall -9 madplay");
			printf("\033[36m ���˳� \033[0m\n");
			flag = 1;
			break;
		}

	}
}
/*    //�������� 
    system("madplay 1.mp3 &"); 

    //����ѭ�� 
    // system("madplay 1.mp3 �\r &"); 
    sleep(5); 
    //��ͣ���� 
    system("killall �\SIGSTOP madplay &"); 
    sleep(3); 
    //�ָ����� 
    system("killall �\SIGCONT madplay &"); 
    sleep(10); 
    //ֹͣ���� 
    system("killall �\9 madplay"); 
 */