#include "../inc/dir.h"
char bmp_list[20][30];
int bmp_count;
int get_bmp(char *pathname)
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
	bmp_count = 0;
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
    	strcpy(bmp_list[i++],ep->d_name);
        bmp_count++;
    }



    return 0;
}
