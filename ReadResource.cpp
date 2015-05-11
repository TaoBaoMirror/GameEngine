/***
*ReadResource.cpp - 读取资源
*
*       版权自由.
*
*Purpose:
*       详细介绍
*       头文件:ReadResource.h
*
*******************************************************************************/
#include <opencv2\opencv.hpp>
#include <Windows.h>
#include "ReadResource.h"
#include <iostream>




using namespace cv;
using namespace std;

//ROIA的左上角H,R,Y
int g_ROIA_LH=(WINDOW_W-ROIA_W)/2;
//ROIA的左上角W,C,X
int g_ROIA_LW=(WINDOW_H-ROIA_H)/2;

double angle = 0;  // 旋转角度
double scale = 1; // 缩放尺度

POINT zuobiao[2];
int ID=0;

const String csPathA="zmlm2.jpg";
const String csPathB="smallhu2.jpg";
const String csPathC="green2.jpg";
const String csPathD="tiger02s.jpg";

//创建全白背景
Mat matA(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//它是初始化完毕的地图,这张地图不允许旋转重写.这里这张地图不允许任何重写.
Mat matB(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//碰撞ID图
Mat matWork(WINDOW_H,WINDOW_W,CV_8UC3,Scalar(groudcolor,groudcolor,groudcolor));//操作都在work上面哟,旋转更新重新深拷贝.深拷贝来自初始化结束的matA地图


int ShowROIA(Mat &matWork);
int 映射资源(const String& resourceName,POINT coordinate[2],Mat &objMatA,Mat &objMatB,int ID);
void DrawFilledCircle( Mat img, Point center );

//预处理的线程
unsigned int __stdcall 预处理(PVOID pM)
{
	printf("ID号为%4x说：预处理开始\n", GetCurrentThreadId()); 

	POINT zuobiao[2];
	int ID=0;

	const String csPathA="zmlm2.jpg";
	const String csPathB="smallhu2.jpg";
	const String csPathC="green2.jpg";
	const String csPathD="zjk.png";

	zuobiao[0].y=10;
	zuobiao[0].x=10;
	ID=1;

	

	if(!映射资源(csPathA,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}

	zuobiao[0].y=200;
	zuobiao[0].x=200;
	ID=6;

	//namedWindow("输出",WINDOW_NORMAL);

	if(!映射资源(csPathA,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}



	zuobiao[0].y=200;
	zuobiao[0].x=200;
	ID=2;

	if(!映射资源(csPathB,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	zuobiao[0].y=600;
	zuobiao[0].x=600;
	ID=3;

	if(!映射资源(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	zuobiao[0].y=500;
	zuobiao[0].x=500;
	ID=4;

	if(!映射资源(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	zuobiao[0].y=200;
	zuobiao[0].x=600;
	ID=5;

	if(!映射资源(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	zuobiao[0].y=600;
	zuobiao[0].x=100;
	ID=6;

	if(!映射资源(csPathC,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	zuobiao[0].y=400;
	zuobiao[0].x=800;
	ID=7;

	if(!映射资源(csPathD,zuobiao,matA,matB,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}



	imshow("碰撞图",matB);
	//映射资源结束.
	imshow("你好",matA);

	matA.copyTo(matWork);


	Point2f center =Point2f(matWork.cols / 2, g_ROIA_LH+(ROIA_H / 2));  // 旋转中心



	Mat	rotateMat; 
	



	int key =0;

	//轮询获取按键信息
	while(1)
	{
		key=waitKey(20) ;//读取键值到key变量中

		//根据key变量的值，进行不同的操作
		switch(key)
		{
			//======================【程序退出相关键值处理】=======================  
		case 27://按键ESC
			return 0;
			break; 

		case 'w'://按键w
			if(g_ROIA_LH>0)
			{--g_ROIA_LH;}

			ShowROIA(matWork);

			break; 
		case 's':
			if(g_ROIA_LH<WINDOW_H)
			{++g_ROIA_LH;}
			
			ShowROIA(matWork);
			

			break;
			//左转弯
		case 'a':
			--angle;

			rotateMat = getRotationMatrix2D(center, angle, scale);
			warpAffine(matA,matWork, rotateMat, matA.size());
			ShowROIA(matWork);
			break;
			//右转弯
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

	cout<<endl<<"起始地址:X,W,宽"<<g_ROIA_LW<<"起始地址:Y,H,高"<<
		g_ROIA_LH<<"角度是:"<<angle<<endl;

	Mat resultMat(imageROI.rows,imageROI.cols,imageROI.depth(),Scalar(255,255,255));
	imageROI.copyTo(resultMat);

	//在ROIA上+一张坦克
	
	zuobiao[0].y=(resultMat.rows-100)/2;
	zuobiao[0].x=(resultMat.cols-220)/2;
	ID=200;

	//确保坦克的ID不会被写入错误的mat中
	Mat matnull;
	if(!映射资源(csPathD,zuobiao,resultMat,matnull,ID))
	{
		//imshow("输出",matA);
	}
	else
	{
		("载入ID为:%d的资源出错",ID);
	}


	//在ROIA上+一张圆形(方形)整体缩略图
	//1对matWork进行金字塔缩小到指定深拷贝.
	//2在ROIA上画出小地图ROI位置
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
*映射资源	 - 将指定资源映射到目标Mat的指定位置
*
*Purpose:
*      	映射指定图片到指定位置
*
*
*
*
*Entry:
*       const	String&	-资源名:name+扩展名.路径在ImageRes下面
*		POINT	[2]		-[0]为待放资源位置方形左上坐标.-[1]为右下角坐标暂时不用
*		Mat&			-对Mat的引用
*		int		ID		-标记对象在objMatB
*Exit:
*       returns non-zero	= 正常执行
*						1	= 读取数据为空错误
*						2	= POINT[0]参数不合法
*Exceptions:
*       None.
*
*Warming:
*		引用的objMatA,B可能导致对全局Mat的多线程操作出错
*
*
*******************************************************************************/
int 映射资源(const String& resourceName,POINT coordinate[2],Mat &objMatA,Mat &objMatB,int ID)
{
	printf("线程ID号为%4x的子线程说：映射资源%d开始\n", GetCurrentThreadId(),ID); 


	//合法性检查
	if ((coordinate[0].y>=objMatA.rows)||(coordinate[0].x>=objMatA.cols))
	{
		return 2;//POINT[0]参数出错
	}
	String newResName="ImageRes\\"+resourceName;

	Mat resA=imread(newResName);//flags必须是默认1
	if (NULL==resA.data)
	{
		return 1;
	}

	Mat imageROI=objMatA(Rect(coordinate[0].x,coordinate[0].y,resA.cols,resA.rows));
	Mat mask=imread(newResName,0);
	resA.copyTo(imageROI,mask);

	//objMatB没有数据则不需要进行历遍替换标记操作
	if(NULL!=objMatB.data)
	{
		//历遍目标区域像素找到非背景元素标记在objMatB中
		for (int i=coordinate[0].y;i<coordinate[0].y+resA.rows;i++)
		{
			for (int j=coordinate[0].x;j<coordinate[0].x+resA.cols;j++)
			{
				if ((groudcolor!=objMatA.at<Vec3b>(i,j)[0])||(groudcolor!=objMatA.at<Vec3b>(i,j)[1])||(groudcolor!=objMatA.at<Vec3b>(i,j)[2]))//不是背景则标记为ID
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