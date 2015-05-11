/***
*CheckKey.cpp - 读取资源
*
*       版权自由.
*
*Purpose:
*       详细介绍
*       头文件:CheckKey.h
*
*******************************************************************************/


#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <conio.h>
#include <mmsystem.h>


using namespace cv;





unsigned int __stdcall Music(PVOID pM)
{
	printf("ID号为%4x说：Music is start\n", GetCurrentThreadId());  

	
	PlaySound("music\\开始.wav",NULL,SND_FILENAME|SND_SYNC);
	PlaySound("music\\战斗.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	return 0;
}