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
	//��������
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, Music, NULL, 0, NULL);
	
	
	VideoCapture capture("ImageRes\\2.avi");

	//��2��ѭ����ʾÿһ֡
	while(1)  
	{  
		Mat frame;//����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		capture>>frame;//��ȡ��ǰ֡
		if (!frame.data)
		{
			break;
		}
		imshow("��ȡ��Ƶ",frame);  //��ʾ��ǰ֡
		waitKey(30);  //��ʱ30ms
	}  


	handle[1] = (HANDLE)_beginthreadex(NULL, 0, Ԥ����, NULL, 0, NULL);

	
	
	
	
	WaitForMultipleObjects(2,handle,TRUE,INFINITE);  

	return 0;
}