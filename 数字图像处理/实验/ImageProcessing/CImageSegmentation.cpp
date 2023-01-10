#include "pch.h"
#include "CImageSegmentation.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <ctime>
using namespace std;
struct Point
{
	int x;
	int y;
};

template <class T_DATA>
CImageSegmentation<T_DATA>::CImageSegmentation()
{
}

template <class T_DATA>
CImageSegmentation<T_DATA>::~CImageSegmentation()
{
}

template<class T_DATA>
T_DATA CImageSegmentation<T_DATA>::OtsuThreshold(CImageData<T_DATA>* img)
{
	int T = 0;							//Otsu算法阈值
	double w0 = 0;						//前景像素点数占比
	double w1 = 0;						//背景像素点数占比
	double u0 = 0;						//前景平均灰度
	double u1 = 0;						//背景平均灰度
	double sigma0 = 0;					//前景方差
	double sigma1 = 0;					//背景方差
	double Histogram[256] = { 0 };		//灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数

	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			Histogram[*(img->GetData() + i * img->GetWidth() + j)]++;

	int totalNum = img->GetHeight() * img->GetWidth();
	double tempT = 0x3f3f3f3f;					
	for (int i = 0; i < 255; i++)
	{
		w1 = 0; u1 = 0; w0 = 0; u0 = 0; sigma0 = 0; sigma1 = 0;
		for (int j = 0; j <= i; j++)	//背景各值计算
		{
			w1 += Histogram[j];			//背景像素点总数
			u1 += j * Histogram[j];		//背景像素总灰度和
		}
		if (w1 == 0)					//背景像素点数为0时跳过
			continue;
		for (int j = i + 1; j < 256; j++)
		{
			w0 += Histogram[j];			//前景像素点总数
			u0 += j * Histogram[j];		//前景像素总灰度和
		}
		if (w0 == 0)					//前景像素点数为0时跳过
			continue;
		u1 = u1 / w1;					//背景像素平均灰度
		u0 = u0 / w0;					//前景像素平均灰度
		for (int j = 0; j <= i; j++)
			sigma1 += pow((j - u1), 2) * Histogram[j] / w1;
		for (int j = i + 1; j < 256; j++)
			sigma0 += pow((j - u0), 2) * Histogram[j] / w0;
		w1 = w1 / totalNum;				//背景像素点数占比
		w0 = w0 / totalNum;				//前景像素点数占比
		w0 = 1 - w1;
		double temp = w1 * sigma1 + w0 * sigma0;
		if (tempT > temp)
		{
			tempT = temp;
			T = i;
		}
	}
	return T;
}

template<class T_DATA>
T_DATA CImageSegmentation<T_DATA>::GrayDiffer(CImageData<T_DATA>* img,T_DATA threshold)// 类间灰度差作为可分性度量
{
	double w0 = 0;						//前景像素点数占比
	double w1 = 0;						//背景像素点数占比
	double u0 = 0;						//前景平均灰度
	double u1 = 0;						//背景平均灰度
	double Histogram[256] = { 0 };		//灰度直方图
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			Histogram[*(img->GetData() + i * img->GetWidth() + j)]++;
	for (int j = 0; j <= (int)threshold; j++)
	{
		w1 += Histogram[j];				//背景像素点总数
		u1 += j * Histogram[j];			//背景像素总灰度和
	}
	for (int j = (int)threshold + 1; j < 256; j++)
	{
		w0 += Histogram[j];				//前景像素点总数
		u0 += j * Histogram[j];			//前景像素总灰度和
	}
	u1 = u1 / w1;						//背景像素平均灰度
	u0 = u0 / w0;						//前景像素平均灰度
	return u0 - u1;
}

template<class T_DATA>
void CImageSegmentation<T_DATA>::GlobalThreshold(CImageData<T_DATA>* img)
{
	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
	mpPixels = new T_DATA[img->GetHeight() * img->GetWidth()];
	T_DATA T = OtsuThreshold(img);
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			if (*(img->GetData() + i * img->GetWidth() + j) > T)
				*(mpPixels + i * mWidth + j) = 255;
			else
				*(mpPixels + i * mWidth + j) = 0;
}
/*
template<class T_DATA>
void CImageSegmentation<T_DATA>::RegionGrow(CImageData<T_DATA>* img,T_DATA threshold)	// threshold:生长时的相似性阈值
{
	vector<Point> seedVector;     //种子栈
	int neighbour[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };	//定义8邻域
	Point waitSeed;    //待生长种子点

	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
	mpPixels = new T_DATA[mHeight * mWidth];
	for (int i = 0; i < mHeight; i++)
		for (int j = 0; j < mWidth; j++)
			*(mpPixels + i * mWidth + j) = (T_DATA)255;// 初始全设为前景（255白色）
	
	//int* pRegion = new int[mWidth * mHeight];				// 用来标记当前像素点有没有被处理
	//memset(pRegion, 0, sizeof(int) * mWidth * mHeight);
	
	// 阈值法求种子
	T_DATA T = OtsuThreshold(img);
	
	int temp1 = 0, temp2 = 0;
	while (1) {
		srand(time(0));
		int x = rand() % img->GetHeight();
		int y = rand() % img->GetWidth();
		CString str;
		str.Format(_T("%d"), (int)x);
		AfxMessageBox(str);
		if (*(img->GetData() + x * img->GetWidth() + y) < T) {		// 背景(连通)
			temp1++;
			Point seed;
			seed.x = x;
			seed.y = y;
			seedVector.push_back(seed);
			//*(mpPixels + x * mWidth + y) = (T_DATA)0;
		}
		//else if (*(img->GetData() + x * img->GetWidth() + y) > T){	// 前景
		//	temp2++;
		//	Point seed = Point(x, y);
		//	seedVector.push_back(seed);
		//}
		//if (temp1 >= 1 && temp2 >= 1)	// 二个类别都至少有一个种子
		//	break;
		if (temp1 >= 1)	// 背景至少有一个种子
			break;
	}
	
	while (!seedVector.empty())     //种子栈不为空则区域增长
	{
		Point curSeed = seedVector.back();
		T_DATA curValue = *(img->GetData() + curSeed.x * mWidth + curSeed.y);
		seedVector.pop_back();      
		for (int i = 0; i < 8; i++)    //遍历种子点的8邻域
		{
			waitSeed.x = curSeed.x + neighbour[i][0];   
			waitSeed.y = curSeed.y + neighbour[i][1];

			if (waitSeed.x < 0 || waitSeed.y < 0 || waitSeed.x >mHeight - 1 || waitSeed.y > mWidth - 1)
				continue;

			//if (*(pRegion+ waitSeed.x* mWidth+ waitSeed.y) == 0)     //判断waitSeed是否已经被生长
			if(*(mpPixels + waitSeed.x * mWidth + waitSeed.y) == 255 )
			{
				T_DATA grayDiff = abs((int)curValue - (int)(*(img->GetData() + waitSeed.x * mWidth + waitSeed.y)));
				T_DATA curRegion = *(mpPixels + curSeed.x * mWidth + curSeed.y);
				if (grayDiff <= threshold)    // 同类，默认即灰度级不相差超过15以内的都算为同类
				{
					//*(pRegion + waitSeed.x * mWidth + waitSeed.y) = 1;
					//*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = curRegion;	// 同类
					*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = 0;
					seedVector.push_back(waitSeed);    //将满足生长条件的待生长种子点放入种子栈中
				}
				//else {
				//	*(pRegion + waitSeed.x * mWidth + waitSeed.y) = 1;
				//	*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = 255 - curRegion;	// 不同类
				//	seedVector.push_back(waitSeed);    //将满足生长条件的待生长种子点放入种子栈中
				//}
			}
		}
	}
}
*/

template<class T_DATA>
void CImageSegmentation<T_DATA>::BlockingThreshold(CImageData<T_DATA>* img,int row,int col)
{
	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
	mpPixels = new T_DATA[img->GetHeight() * img->GetWidth()];
	memset(mpPixels, 0, sizeof(T_DATA)* mWidth* mHeight);

	int regionWidth = mWidth / col;
	int regionHeight = mHeight / row;

	for (int m = 0; m < row; m++)
		for (int n = 0; n < col; n++) {
			CImageData<T_DATA> regionImg;
			if (m != row - 1 && n != col - 1)
			{
				regionImg.SetHeight(regionHeight);
				regionImg.SetWidth(regionWidth);
			}
			else if (m != row - 1 && n == col - 1) 	// 对于最右边一列图像块的处理(除去最后一块)
			{
				regionImg.SetHeight(regionHeight);
				regionImg.SetWidth(mWidth - n * regionWidth);
			}
			else if (m == row - 1 && n != col - 1) 	// 对于最下面一行图像块的处理(除去最后一块)
			{
				regionImg.SetHeight(mHeight - m * regionHeight);
				regionImg.SetWidth(regionWidth);
			}
			else									// 对于最后一块图像块的单独处理
			{
				regionImg.SetHeight(mHeight - m * regionHeight);
				regionImg.SetWidth(mWidth - n * regionWidth);
			}
			regionImg.SetData();					// 给regionImg的mpPixels在设置完长宽后分配内存
			for (int i = 0; i < regionImg.GetHeight(); i++)
				for (int j = 0; j < regionImg.GetWidth(); j++)
				{
					int x = m * regionHeight, y = n * regionWidth;
					*(regionImg.GetData() + i * regionImg.GetWidth() + j) = *(img->GetData() + (i + x) * img->GetWidth() + (j + y));
				}
			T_DATA T = OtsuThreshold(&regionImg);	// 大津阈值法，取子块图像的阈值
			if (GrayDiffer(&regionImg, T) > 20) {	// 类间灰度差作为可分性度量
				for (int i = 0; i < regionImg.GetHeight(); i++)
					for (int j = 0; j < regionImg.GetWidth(); j++)
					{
						int x = m * regionHeight, y = n * regionWidth;
						if (*(regionImg.GetData() + i * regionImg.GetWidth() + j) > T)
							*(mpPixels + (i + x) * mWidth + (j + y)) = 255;
						else
							*(mpPixels + (i + x) * mWidth + (j + y)) = 0;
					}
			}
		}
}
