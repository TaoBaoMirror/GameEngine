/***
*ReadResource.cpp - ��ȡ��Դ
*
*       ��Ȩ����.
*
*Purpose:
*       ��ϸ����
*       ͷ�ļ�:ReadResource.h
*
*******************************************************************************/
#include <opencv2\opencv.hpp>
#include <Windows.h>
#include "ReadResource.h"
#include <iostream>




using namespace cv;
using namespace std;

//ROIA�����Ͻ�H,R,Y
int g_ROIA_LH=(WINDOW_W-ROIA_W)/2;
//ROIA�����Ͻ�W,C,X
int g_ROIA_LW=(WINDOW_H-ROIA_H)/2;

double angle = 0;  // ��ת�Ƕ�
double scale = 1; // ���ų߶�

POINT zuobiao[2];
int ID=0;

const String csPathA="zmlm2.jpg";
const String csPathB="smallhu2.jpg";
const String csPathC="green2.jpg";
const String csPathD="tiger02s.jpg";

//����ȫ�ױ���
Mat matA(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//���ǳ�ʼ����ϵĵ�ͼ,���ŵ�ͼ��������ת��д.�������ŵ�ͼ�������κ���д.
Mat matB(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//��ײIDͼ
Mat matWork(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//��������work����Ӵ,��ת�����������.������Գ�ʼ��������matA��ͼ


int ShowROIA(Mat &matWork);
int ӳ����Դ(const String& resourceName,POINT coordinate[2],Mat &objMatA,Mat &objMatB,int ID);
void DrawFilledCircle( Mat img, Point center );

//Ԥ������߳�
unsigned int __stdcall Ԥ����(PVOID pM)
{
	printf("ID��Ϊ%4x˵��Ԥ����ʼ\n", GetCurrentThreadId()); 

	POINT zuobiao[2];
	int ID=0;

	const String csPathA="zmlm2.jpg";
	const String csPathB="smallhu2.jpg";
	const String csPathC="green2.jpg";
	const String csPathD="zjk.png";

	zuobiao[0].y=10;
	zuobiao[0].x=10;
	ID=1;

	

	if(!ӳ����Դ(csPathA,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}

	zuobiao[0].y=200;
	zuobiao[0].x=200;
	ID=6;

	//namedWindow("���",WINDOW_NORMAL);

	if(!ӳ����Դ(csPathA,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}



	zuobiao[0].y=200;
	zuobiao[0].x=200;
	ID=2;

	if(!ӳ����Դ(csPathB,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	zuobiao[0].y=600;
	zuobiao[0].x=600;
	ID=3;

	if(!ӳ����Դ(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	zuobiao[0].y=500;
	zuobiao[0].x=500;
	ID=4;

	if(!ӳ����Դ(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	zuobiao[0].y=200;
	zuobiao[0].x=600;
	ID=5;

	if(!ӳ����Դ(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	zuobiao[0].y=600;
	zuobiao[0].x=100;
	ID=6;

	if(!ӳ����Դ(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	zuobiao[0].y=400;
	zuobiao[0].x=800;
	ID=7;

	if(!ӳ����Դ(csPathD,zuobiao,matA,matB,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}



	imshow("��ײͼ",matB);
	//ӳ����Դ����.
	imshow("���",matA);

	matA.copyTo(matWork);


	Point2f center =Point2f(matWork.cols / 2, g_ROIA_LH+(ROIA_H / 2));  // ��ת����



	Mat	rotateMat; 
	



	int key =0;

	//��ѯ��ȡ������Ϣ
	while(1)
	{
		key=waitKey(20) ;//��ȡ��ֵ��key������

		//����key������ֵ�����в�ͬ�Ĳ���
		switch(key)
		{
			//======================�������˳���ؼ�ֵ����=======================  
		case 27://����ESC
			return 0;
			break; 

		case 'w'://����w
			if(g_ROIA_LH>0)
			{--g_ROIA_LH;}

			ShowROIA(matWork);

			break; 
		case 's':
			if(g_ROIA_LH<WINDOW_H)
			{++g_ROIA_LH;}
			
			ShowROIA(matWork);
			

			break;
			//��ת��
		case 'a':
			--angle;

			rotateMat = getRotationMatrix2D(center, angle, scale);
			warpAffine(matA,matWork, rotateMat, matA.size());
			ShowROIA(matWork);
			break;
			//��ת��
		case 'd':
			++angle;
			rotateMat = getRotationMatrix2D(center, angle, scale);
			warpAffine(matA,matWork, rotateMat, matA.size());
			ShowROIA(matWork);
			break;
		}

	}//from while



	return 0;
}
int ShowROIA(Mat &matWork)
{

	Mat imageROI;
	imageROI=matWork(Rect(g_ROIA_LW,g_ROIA_LH,ROIA_W,ROIA_H));

	cout<<endl<<"��ʼ��ַ:X,W,��"<<g_ROIA_LW<<"��ʼ��ַ:Y,H,��"<<
		g_ROIA_LH<<"�Ƕ���:"<<angle<<endl;

	Mat resultMat(imageROI.rows,imageROI.cols,imageROI.depth(),Scalar(255,255,255));
	imageROI.copyTo(resultMat);

	//��ROIA��+һ��̹��
	
	zuobiao[0].y=(resultMat.rows-100)/2;
	zuobiao[0].x=(resultMat.cols-220)/2;
	ID=200;

	//ȷ��̹�˵�ID���ᱻд������mat��
	Mat matnull;
	if(!ӳ����Դ(csPathD,zuobiao,resultMat,matnull,ID))
	{
		//imshow("���",matA);
	}
	else
	{
		("����IDΪ:%d����Դ����",ID);
	}


	//��ROIA��+һ��Բ��(����)��������ͼ
	//1��matWork���н�������С��ָ�����.
	//2��ROIA�ϻ���С��ͼROIλ��
	//3smallmapROI.copyTo(resultMat)
	//Mat tmpImage;
	Mat smallmapMat;
	resize(matWork,smallmapMat,Size(matWork.rows/9,matWork.cols/9),(0,0),(0,0),3);


	Mat imageROI2=resultMat(Rect(ROIA_W-150,ROIA_H-150,smallmapMat.cols,smallmapMat.rows));
	
	imwrite("ImageRes\\temp.jpg",smallmapMat);
	Mat imageROI3=imread("ImageRes\\temp.jpg",0);

	smallmapMat.copyTo(imageROI2,imageROI3);

	DrawFilledCircle(resultMat,Point((ROIA_W-150+(smallmapMat.cols/2)),(ROIA_H-150+(smallmapMat.rows/2))));

	imshow("resultMat",resultMat);


	return 0;
}

void DrawFilledCircle( Mat img, Point center )
{
	int thickness = 2;
	int lineType = 8;

	circle( img,
		center,
		75,
		Scalar( 0, 255,0),
		thickness,
		lineType );
}

/***
*ӳ����Դ	 - ��ָ����Դӳ�䵽Ŀ��Mat��ָ��λ��
*
*Purpose:
*      	ӳ��ָ��ͼƬ��ָ��λ��
*
*
*
*
*Entry:
*       const	String&	-��Դ��:name+��չ��.·����ImageRes����
*		POINT	[2]		-[0]Ϊ������Դλ�÷�����������.-[1]Ϊ���½�������ʱ����
*		Mat&			-��Mat������
*		int		ID		-��Ƕ�����objMatB
*Exit:
*       returns non-zero	= ����ִ��
*						1	= ��ȡ����Ϊ�մ���
*						2	= POINT[0]�������Ϸ�
*Exceptions:
*       None.
*
*Warming:
*		���õ�objMatA,B���ܵ��¶�ȫ��Mat�Ķ��̲߳�������
*
*
*******************************************************************************/
int ӳ����Դ(const String& resourceName,POINT coordinate[2],Mat &objMatA,Mat &objMatB,int ID)
{
	printf("�߳�ID��Ϊ%4x�����߳�˵��ӳ����Դ%d��ʼ\n", GetCurrentThreadId(),ID); 


	//�Ϸ��Լ��
	if ((coordinate[0].y>=objMatA.rows)||(coordinate[0].x>=objMatA.cols))
	{
		return 2;//POINT[0]��������
	}
	String newResName="ImageRes\\"+resourceName;

	Mat resA=imread(newResName);//flags������Ĭ��1
	if (NULL==resA.data)
	{
		return 1;
	}

	Mat imageROI=objMatA(Rect(coordinate[0].x,coordinate[0].y,resA.cols,resA.rows));
	Mat mask=imread(newResName,0);
	resA.copyTo(imageROI,mask);

	//objMatBû����������Ҫ���������滻��ǲ���
	if(NULL!=objMatB.data)
	{
		//����Ŀ�����������ҵ��Ǳ���Ԫ�ر����objMatB��
		for (int i=coordinate[0].y;i<coordinate[0].y+resA.rows;i++)
		{
			for (int j=coordinate[0].x;j<coordinate[0].x+resA.cols;j++)
			{
				if ((groudcolor!=objMatA.at<Vec3b>(i,j)[0])||(groudcolor!=objMatA.at<Vec3b>(i,j)[1])||(groudcolor!=objMatA.at<Vec3b>(i,j)[2]))//���Ǳ�������ΪID
				{
					objMatB.at<Vec3b>(i,j)[0]=ID;
				}
			}

		}
	};

	//imshow("hi objMatA",objMatA);

	//waitKey(0);

	return 0;

}