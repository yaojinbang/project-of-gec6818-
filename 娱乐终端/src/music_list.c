#include "../inc/dir.h"
char music_list[20][30];
int music_count;
int get_music(char *pathname)
{
    //��Ŀ¼
    DIR *dp = opendir(pathname);
    if(dp == NULL)
    {
    	printf("��ʧ��\n");
    	return -1;
    }
    struct dirent *ep = NULL;
    int i = 0;
	music_count = 0;
    while(1)
    {
    	//��ȡĿ¼��
    	ep = readdir(dp);
    	if(ep == NULL)
    	{
    		break;
    	}
    	if(strncmp((*ep).d_name,".",1) == 0 || strncmp((*ep).d_name,"..",2) == 0 )
    	{
    		continue;
    	}
    	strcpy(music_list[i++],ep->d_name);
		music_count++;
    }



    return 0;
}
