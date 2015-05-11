#include <opencv2\opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <process.h>
#include "Music.h"

#include "ReadResource.h"


using namespace cv;
using namespace std;






int main(_In_ int _Argc, _In_reads_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env)
{
	

	HANDLE handle[2];
	//启动音乐
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, Music, NULL, 0, NULL);
	
	
	VideoCapture capture("ImageRes\\2.avi");

	//【2】循环显示每一帧
	while(1)  
	{  
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		capture>>frame;//读取当前帧
		if (!frame.data)
		{
			break;
		}
		imshow("读取视频",frame);  //显示当前帧
		waitKey(30);  //延时30ms
	}  


	handle[1] = (HANDLE)_beginthreadex(NULL, 0, 预处理, NULL, 0, NULL);

	
	
	
	
	WaitForMultipleObjects(2,handle,TRUE,INFINITE);  

	return 0;
}