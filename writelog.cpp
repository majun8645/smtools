#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define PATH "./data/gps/"
int writeLog( int num,FILE ** fs)
{
	char path[256] ={0};
	struct tm stUtcTime;
	if(*fs ==NULL)
	{
		time_t utcTime = 0;
		if(time(&utcTime) == -1)
		{
			printf("获取时间失败\n");
			return -1;
		}
		if(	localtime_r(&utcTime,&stUtcTime) == NULL)
		{	
			printf("时间转换失败\n");
			return -1;
		}
		snprintf(path
				,sizeof(path)
				,"%s%04d%02d%02d%02d%02d.log"
				,PATH,stUtcTime.tm_year+1900
				,stUtcTime.tm_mon + 1
				,stUtcTime.tm_mday
				,stUtcTime.tm_hour
				,stUtcTime.tm_min);
		*fs = fopen(path,"ab+");
		if(*fs == NULL) 
		{
			printf("open error\n");
			return -1;
		}
	}
	else
	{
	}
	fwrite(&num,1,sizeof(num),*fs);
	return 0;
}
int main(int agec,char*argv[])
{
	int num = 0;
	FILE * fs = NULL;
	while(1)
	{
		if(fopen("./over.txt","r"))
		{
			if(fs) fclose(fs);
			printf("stop writelog\n");
			break;
		}
		if(writeLog(num,&fs) != 0)
		{
				printf("writeLog error\n");
		}
		usleep(100*1000);
		num++;
	}
	
	return 0;
}