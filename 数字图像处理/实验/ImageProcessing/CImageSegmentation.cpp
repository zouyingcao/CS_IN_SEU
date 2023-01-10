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
	int T = 0;							//Otsu�㷨��ֵ
	double w0 = 0;						//ǰ�����ص���ռ��
	double w1 = 0;						//�������ص���ռ��
	double u0 = 0;						//ǰ��ƽ���Ҷ�
	double u1 = 0;						//����ƽ���Ҷ�
	double sigma0 = 0;					//ǰ������
	double sigma1 = 0;					//��������
	double Histogram[256] = { 0 };		//�Ҷ�ֱ��ͼ���±��ǻҶ�ֵ�����������ǻҶ�ֵ��Ӧ�����ص�����

	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			Histogram[*(img->GetData() + i * img->GetWidth() + j)]++;

	int totalNum = img->GetHeight() * img->GetWidth();
	double tempT = 0x3f3f3f3f;					
	for (int i = 0; i < 255; i++)
	{
		w1 = 0; u1 = 0; w0 = 0; u0 = 0; sigma0 = 0; sigma1 = 0;
		for (int j = 0; j <= i; j++)	//������ֵ����
		{
			w1 += Histogram[j];			//�������ص�����
			u1 += j * Histogram[j];		//���������ܻҶȺ�
		}
		if (w1 == 0)					//�������ص���Ϊ0ʱ����
			continue;
		for (int j = i + 1; j < 256; j++)
		{
			w0 += Histogram[j];			//ǰ�����ص�����
			u0 += j * Histogram[j];		//ǰ�������ܻҶȺ�
		}
		if (w0 == 0)					//ǰ�����ص���Ϊ0ʱ����
			continue;
		u1 = u1 / w1;					//��������ƽ���Ҷ�
		u0 = u0 / w0;					//ǰ������ƽ���Ҷ�
		for (int j = 0; j <= i; j++)
			sigma1 += pow((j - u1), 2) * Histogram[j] / w1;
		for (int j = i + 1; j < 256; j++)
			sigma0 += pow((j - u0), 2) * Histogram[j] / w0;
		w1 = w1 / totalNum;				//�������ص���ռ��
		w0 = w0 / totalNum;				//ǰ�����ص���ռ��
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
T_DATA CImageSegmentation<T_DATA>::GrayDiffer(CImageData<T_DATA>* img,T_DATA threshold)// ���ҶȲ���Ϊ�ɷ��Զ���
{
	double w0 = 0;						//ǰ�����ص���ռ��
	double w1 = 0;						//�������ص���ռ��
	double u0 = 0;						//ǰ��ƽ���Ҷ�
	double u1 = 0;						//����ƽ���Ҷ�
	double Histogram[256] = { 0 };		//�Ҷ�ֱ��ͼ
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			Histogram[*(img->GetData() + i * img->GetWidth() + j)]++;
	for (int j = 0; j <= (int)threshold; j++)
	{
		w1 += Histogram[j];				//�������ص�����
		u1 += j * Histogram[j];			//���������ܻҶȺ�
	}
	for (int j = (int)threshold + 1; j < 256; j++)
	{
		w0 += Histogram[j];				//ǰ�����ص�����
		u0 += j * Histogram[j];			//ǰ�������ܻҶȺ�
	}
	u1 = u1 / w1;						//��������ƽ���Ҷ�
	u0 = u0 / w0;						//ǰ������ƽ���Ҷ�
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
void CImageSegmentation<T_DATA>::RegionGrow(CImageData<T_DATA>* img,T_DATA threshold)	// threshold:����ʱ����������ֵ
{
	vector<Point> seedVector;     //����ջ
	int neighbour[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };	//����8����
	Point waitSeed;    //���������ӵ�

	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
	mpPixels = new T_DATA[mHeight * mWidth];
	for (int i = 0; i < mHeight; i++)
		for (int j = 0; j < mWidth; j++)
			*(mpPixels + i * mWidth + j) = (T_DATA)255;// ��ʼȫ��Ϊǰ����255��ɫ��
	
	//int* pRegion = new int[mWidth * mHeight];				// ������ǵ�ǰ���ص���û�б�����
	//memset(pRegion, 0, sizeof(int) * mWidth * mHeight);
	
	// ��ֵ��������
	T_DATA T = OtsuThreshold(img);
	
	int temp1 = 0, temp2 = 0;
	while (1) {
		srand(time(0));
		int x = rand() % img->GetHeight();
		int y = rand() % img->GetWidth();
		CString str;
		str.Format(_T("%d"), (int)x);
		AfxMessageBox(str);
		if (*(img->GetData() + x * img->GetWidth() + y) < T) {		// ����(��ͨ)
			temp1++;
			Point seed;
			seed.x = x;
			seed.y = y;
			seedVector.push_back(seed);
			//*(mpPixels + x * mWidth + y) = (T_DATA)0;
		}
		//else if (*(img->GetData() + x * img->GetWidth() + y) > T){	// ǰ��
		//	temp2++;
		//	Point seed = Point(x, y);
		//	seedVector.push_back(seed);
		//}
		//if (temp1 >= 1 && temp2 >= 1)	// �������������һ������
		//	break;
		if (temp1 >= 1)	// ����������һ������
			break;
	}
	
	while (!seedVector.empty())     //����ջ��Ϊ������������
	{
		Point curSeed = seedVector.back();
		T_DATA curValue = *(img->GetData() + curSeed.x * mWidth + curSeed.y);
		seedVector.pop_back();      
		for (int i = 0; i < 8; i++)    //�������ӵ��8����
		{
			waitSeed.x = curSeed.x + neighbour[i][0];   
			waitSeed.y = curSeed.y + neighbour[i][1];

			if (waitSeed.x < 0 || waitSeed.y < 0 || waitSeed.x >mHeight - 1 || waitSeed.y > mWidth - 1)
				continue;

			//if (*(pRegion+ waitSeed.x* mWidth+ waitSeed.y) == 0)     //�ж�waitSeed�Ƿ��Ѿ�������
			if(*(mpPixels + waitSeed.x * mWidth + waitSeed.y) == 255 )
			{
				T_DATA grayDiff = abs((int)curValue - (int)(*(img->GetData() + waitSeed.x * mWidth + waitSeed.y)));
				T_DATA curRegion = *(mpPixels + curSeed.x * mWidth + curSeed.y);
				if (grayDiff <= threshold)    // ͬ�࣬Ĭ�ϼ��Ҷȼ�������15���ڵĶ���Ϊͬ��
				{
					//*(pRegion + waitSeed.x * mWidth + waitSeed.y) = 1;
					//*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = curRegion;	// ͬ��
					*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = 0;
					seedVector.push_back(waitSeed);    //���������������Ĵ��������ӵ��������ջ��
				}
				//else {
				//	*(pRegion + waitSeed.x * mWidth + waitSeed.y) = 1;
				//	*(mpPixels + waitSeed.x * mWidth + waitSeed.y) = 255 - curRegion;	// ��ͬ��
				//	seedVector.push_back(waitSeed);    //���������������Ĵ��������ӵ��������ջ��
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
			else if (m != row - 1 && n == col - 1) 	// �������ұ�һ��ͼ���Ĵ���(��ȥ���һ��)
			{
				regionImg.SetHeight(regionHeight);
				regionImg.SetWidth(mWidth - n * regionWidth);
			}
			else if (m == row - 1 && n != col - 1) 	// ����������һ��ͼ���Ĵ���(��ȥ���һ��)
			{
				regionImg.SetHeight(mHeight - m * regionHeight);
				regionImg.SetWidth(regionWidth);
			}
			else									// �������һ��ͼ���ĵ�������
			{
				regionImg.SetHeight(mHeight - m * regionHeight);
				regionImg.SetWidth(mWidth - n * regionWidth);
			}
			regionImg.SetData();					// ��regionImg��mpPixels�������곤�������ڴ�
			for (int i = 0; i < regionImg.GetHeight(); i++)
				for (int j = 0; j < regionImg.GetWidth(); j++)
				{
					int x = m * regionHeight, y = n * regionWidth;
					*(regionImg.GetData() + i * regionImg.GetWidth() + j) = *(img->GetData() + (i + x) * img->GetWidth() + (j + y));
				}
			T_DATA T = OtsuThreshold(&regionImg);	// �����ֵ����ȡ�ӿ�ͼ�����ֵ
			if (GrayDiffer(&regionImg, T) > 20) {	// ���ҶȲ���Ϊ�ɷ��Զ���
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
