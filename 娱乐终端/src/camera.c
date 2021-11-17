#include "../inc/camera_lib_inc/camera.h"
#include "../inc/ts.h"

int camera_count=0;
int camera_count1=0;
int save_count=1;
int save_count1=1;
char camera_filename[50]={0};

//定义结构体变量
static struct jpg_data video_buf;
extern int flag_camera_pt;

//1、打开摄像头
int open_camera(char *pathname_camera)
{
	lcd_open_camera();
	mmap_lcd_camera();
	
	//初始化摄像头
	linux_v4l2_yuyv_init(pathname_camera);
	//开启摄像头捕捉
	linux_v4l2_start_yuyv_capturing();
	return 0;
}
void *fun1(void *arg)
{
	camera_count++;
	if(camera_count <= 2)
	{
		get_ts();
	}else
	{
		camera_count = 0;
	}
}

void *fun2(void *arg)
{
	camera_count1++;
	if(camera_count1 <= 2)
	{
		get_ts();
	}else
	{
		camera_count1 = 0;
	}
}


//2、运行摄像头
int camera_working(void)
{
	int i=0;
	while(1)
	{
		//获取摄像头捕捉的画面
		linux_v4l2_get_yuyv_data (&video_buf);
		
		//显示摄像头捕捉的画面
		show_video_data_camera(0, 0, video_buf.jpg_data , video_buf.jpg_size);
		save_jpg();
		pthread_t TID1;
		pthread_create(&TID1, NULL,fun1, NULL);
		if(664<ts_x&&ts_x<750&&200<ts_y&&ts_y<300)
		{
			ts_x = 0;ts_y = 0;
			pthread_cancel(TID1);
			save_count++;
			break;
		}
	}
	return 0;
}


//2、运行摄像头
int camera_working1(void)
{
	int i=0;
	while(1)
	{
		//获取摄像头捕捉的画面
		linux_v4l2_get_yuyv_data (&video_buf);
		
		//显示摄像头捕捉的画面
		show_video_data_camera(0, 0, video_buf.jpg_data , video_buf.jpg_size);
		save_jpg1();
		pthread_t TID2;
		pthread_create(&TID2, NULL,fun2, NULL);
		if(664<ts_x&&ts_x<750&&200<ts_y&&ts_y<300)
		{
			ts_x = 0;ts_y = 0;
			pthread_cancel(TID2);
			break;
		}
	}
	return 0;
}

//3、关闭摄像头
int close_camera(void)
{
	//摄像头解除初始化
	linux_v4l2_yuyv_quit();
	lcd_close_camera();
	return 0;
}

int save_jpg()
{
	sprintf(camera_filename,"/IOT/project/yule/photo/picture%d.jpg",save_count);
	int fd = open(camera_filename,O_RDWR | O_CREAT | O_TRUNC,0777);
	if(fd == -1)
	{
	printf("falename failed\n");
	return -1;
	}
	ssize_t ret = write(fd,video_buf.jpg_data,video_buf.jpg_size);
	
	close(fd);
}

int save_jpg1()
{
	save_count1++;
	sprintf(camera_filename,"/IOT/project/yule/ruxiang/video%d.jpg",save_count1);
	int fd = open(camera_filename,O_RDWR | O_CREAT | O_TRUNC,0777);
	if(fd == -1)
	{
	printf("falename failed\n");
	return -1;
	}
	ssize_t ret = write(fd,video_buf.jpg_data,video_buf.jpg_size);
	
	close(fd);
}
