#include "../inc/ts.h"
struct input_event touch_info;
int ts_x,ts_y;
int get_ts()
{
	//�򿪴�����
	int fd = open("/dev/input/event0",O_RDWR);
	if (fd == -1)
	{
		printf("��������ʧ��\n");
		return -1;
	}
    
	//��ȡ����������
	int count = 0;
	while(1)
	{	
		read(fd,&touch_info,sizeof(touch_info));
		//��ӡ����������
		if(touch_info.type == EV_ABS)//�ж��Ƿ�Ϊ������
		{
			if(touch_info.code == ABS_X)//�ж��Ƿ�ΪX
			{
				ts_x = touch_info.value*800/1024;
				printf("X:%d\n",touch_info.value*800/1024);
				count++;
			}
			else if(touch_info.code == ABS_Y)//�ж��Ƿ�ΪY
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
		// 	printf("��ָ�뿪������\n");
		// }	
	}
	
	//�رմ�����
	close(fd);
	return 0;
}