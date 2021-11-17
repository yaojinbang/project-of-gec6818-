#include "../inc/ts.h"
struct input_event touch_info;
int ts_x,ts_y;
int get_ts()
{
	//打开触摸屏
	int fd = open("/dev/input/event0",O_RDWR);
	if (fd == -1)
	{
		printf("触摸屏打开失败\n");
		return -1;
	}
    
	//读取触摸屏数据
	int count = 0;
	while(1)
	{	
		read(fd,&touch_info,sizeof(touch_info));
		//打印触摸屏数据
		if(touch_info.type == EV_ABS)//判断是否为触摸屏
		{
			if(touch_info.code == ABS_X)//判断是否为X
			{
				ts_x = touch_info.value*800/1024;
				printf("X:%d\n",touch_info.value*800/1024);
				count++;
			}
			else if(touch_info.code == ABS_Y)//判断是否为Y
			{
				printf("Y:%d\n",touch_info.value*480/600);
				ts_y = touch_info.value*480/600;
				count++;
			}
		}
		
		if(count == 2)
		{
			break;
		}
		// if(touch_info.type == EV_KEY && touch_info.code == BTN_TOUCH && touch_info.value == 0)
		// {
		// 	printf("手指离开触摸屏\n");
		// }	
	}
	
	//关闭触摸屏
	close(fd);
	return 0;
}