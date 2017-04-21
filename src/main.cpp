#include<stdio.h>
#define GPS 0001
#define CAN 0002
#define PULSE 0003
void OnGPS(char* data, int length);
void OnCAN(char* data, int length);
void OnPULSE(char* data, int length);
void OnRecord(char* data, int length);
int writeGPS(char* data, int length,FILE** fs);
int writeCAN(char* data, int length,FILE** fs);
int writePULSE(char* data, int length,FILE** fs);
bool bRecord =false;
int main(int argc ,char*argv[])
{
	HANDLE m_hMsgClientFd = N9M_MSGCreateMessageClient();
	FILE *gps = NULL;
	FILE *can = NULL;
	FILE *pulse = NULL;
 	if(m_hMsgClientFd == NULL)
	{
		PRINT_ERROR("N9M_MSGCreateMessageClient FAILED\n");
		exit(1);
	}
	N9M_MSGEventRegister(m_hMsgClientFd, GPS, N9M_Bind(NULL,&OnGPS));
	N9M_MSGEventRegister(m_hMsgClientFd, CAN, N9M_Bind(NULL,&OnCAN));
	N9M_MSGEventRegister(m_hMsgClientFd, PULSE, N9M_Bind(NULL,&OnPULSE));
	N9M_MSGEventRegister(m_hMsgClientFd, PULSE, N9M_Bind(NULL,&OnRecord));
	while(1);
	{
		N9M_MSGWaitForEvent(m_hMsgClientFd);
		usleep(100*1000);	
	}
	
}
void OnGPS(char* data, int length)
{
	writeGPS(data, length,&gps);
}
void OnCAN(char* data, int length)
{
	writeCAN(data, length,&can);
}
void OnPULSE(char* data, int length)
{
	writePULSE(data, length,&pulse);
}
void OnRecord(char* data, int length)
{
	bRecord = !bRecord;
}
int writeGPS(char* data, int length,FILE** fs)
{
	if (data == NULL) return -1;
	if(*fs)//文件已经打开
	{
		if(!bRecord)//停止记录
		{
			close(*fs);
			*fs == NULL;
			return 0;
		}
	}
	else
	{
		if(!bRecord)//停止记录
		{
			return 0;
		}
		else//需要记录，则创建文件
		{
			
		}
		
	}
	//解析data将数据记录到文件中
	
}