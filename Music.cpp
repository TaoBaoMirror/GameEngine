/***
*CheckKey.cpp - ��ȡ��Դ
*
*       ��Ȩ����.
*
*Purpose:
*       ��ϸ����
*       ͷ�ļ�:CheckKey.h
*
*******************************************************************************/


#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <conio.h>
#include <mmsystem.h>


using namespace cv;





unsigned int __stdcall Music(PVOID pM)
{
	printf("ID��Ϊ%4x˵��Music is start\n", GetCurrentThreadId());  

	
	PlaySound("music\\��ʼ.wav",NULL,SND_FILENAME|SND_SYNC);
	PlaySound("music\\ս��.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	return 0;
}