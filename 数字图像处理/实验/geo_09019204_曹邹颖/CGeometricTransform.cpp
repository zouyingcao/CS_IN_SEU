#include "pch.h"
#include "CGeometricTransform.h"
#include <iostream>
using namespace std;

template <class T_DATA>
CGeometricTransform<T_DATA>::CGeometricTransform()
{
}

template <class T_DATA>
CGeometricTransform<T_DATA>::~CGeometricTransform()
{
}

template <class T_DATA>
void CGeometricTransform<T_DATA>::Translation(double x, double y, CImageData<T_DATA>* img)
{
	T_DATA* pOldBits; // 把原图像中的数据拷贝到pOldBits里
	pOldBits = new T_DATA[img->GetHeight() * img->GetWidth()];
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			*(pOldBits + i * img->GetWidth() + j) = *(img->GetData() + i * img->GetWidth() + j);

	mHeight = img->GetHeight();
	mWidth = img->GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];

	AffineTransformation(1.0, 0, -x, 0, 1.0, -y, pOldBits, img->GetWidth(), img->GetHeight());

	delete[]pOldBits;
}

template<class T_DATA>
void CGeometricTransform<T_DATA>::Rotate(double degree, double rotateX, double rotateY,CImageData<T_DATA>* img)
{
	T_DATA* pOldBits; // 把原图像中的数据拷贝到pOldBits里
	pOldBits = new T_DATA[img->GetHeight() * img->GetWidth()];
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			*(pOldBits + i * img->GetWidth() + j) = *(img->GetData() + i * img->GetWidth() + j);

	double Pi;
	Pi = atan(1) * 4;	//pi
	degree = Pi * degree / 180;

	mHeight = img->GetHeight();
	mWidth = img->GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];

	AffineTransformation(cos(degree), sin(degree), -rotateX* cos(degree)- rotateY* sin(degree)+ rotateX, -sin(degree), cos(degree), rotateX* sin(degree) - rotateY* cos(degree) + rotateY, pOldBits, img->GetWidth(), img->GetHeight());
	/*AffineTransformation(cos(degree), sin(degree), -mWidth/2 * cos(degree) - mHeight/2 * sin(degree) + mWidth/2, -sin(degree), cos(degree), mWidth/2 * sin(degree) - mHeight/2 * cos(degree) + mHeight/2, pOldBits, img->GetWidth(), img->GetHeight());*/
	delete[]pOldBits;
}

template<class T_DATA>
void CGeometricTransform<T_DATA>::Scaling(double ratioX,double ratioY,CImageData<T_DATA>* img)
{
	T_DATA* pOldBits; // 把原图像中的数据拷贝到pOldBits里
	pOldBits = new T_DATA[img->GetHeight() * img->GetWidth()];
	for (int i = 0; i < img->GetHeight(); i++)
		for (int j = 0; j < img->GetWidth(); j++)
			*(pOldBits + i * img->GetWidth() + j) = *(img->GetData() + i * img->GetWidth() + j);

	//缩放后的图像宽高
	mHeight = (int)(1.0 * img->GetHeight() * ratioY + 0.5);	//处理为整数
	mWidth = (int)(1.0 * img->GetWidth() * ratioX + 0.5);
	mpPixels = new T_DATA[mHeight * mWidth];

	AffineTransformation(1.0 / ratioX, 0, 0, 0, 1.0 / ratioY, 0, pOldBits, img->GetWidth(), img->GetHeight());
	
	delete[]pOldBits;
}

template<class T_DATA>
void CGeometricTransform<T_DATA>::AffineTransformation(double A00, double A01, double A02, double A10, double A11, double A12, T_DATA* pOldBits,int OldWidth, int OldHeight)
{
	for (int j = 0; j < mHeight; j++)
	{
		for (int i = 0; i < mWidth; i++)
		{
			double x = A00 * i + A01 * j + A02;
			double y = A10 * i + A11 * j + A12;

			int x1, x2, y1, y2;//原图中映射点周围四个点的坐标

			x1 = (int)x;//左x
			x2 = x1 + 1;//右x					
			y1 = (int)y;//上y
			y2 = y1 + 1;//下y

			T_DATA f1, f2, f3, f4;
			double u, v;
			u = x - x1;
			v = y - y1;

			if (x<0 || x>OldWidth - 1 || y<0 || y>OldHeight - 1)
				mpPixels[j * mWidth + i] = T_DATA(0);
			//对x2、y2越界的情况单独讨论
			else if (i == mWidth - 1 && j == mHeight - 1)//右下顶点
				mpPixels[j * mWidth + i] = pOldBits[y1 * OldWidth + OldWidth - 1];
			else if (i == mWidth - 1)//最后一列除右下顶点部分
			{
				f1 = pOldBits[y1 * OldWidth + x1];//左上
				f3 = pOldBits[y2 * OldWidth + x1];//左下
				mpPixels[j * mWidth + i] = (T_DATA)(f1 * (1 - v) + f3 * v);
			}
			else if (j == mHeight - 1)//最后一行除右下顶点部分
			{
				f1 = pOldBits[y1 * OldWidth + x1];//左上
				f2 = pOldBits[y1 * OldWidth + x2];//右上
				mpPixels[j * mWidth + i] = (T_DATA)(f1 * (1 - u) + f2 * u);
			}
			else//其他部分
			{
				f1 = pOldBits[y1 * OldWidth + x1];//左上
				f2 = pOldBits[y1 * OldWidth + x2];//右上
				f3 = pOldBits[y2 * OldWidth + x1];//左下
				f4 = pOldBits[y2 * OldWidth + x2];//右下
				mpPixels[j * mWidth + i] = (T_DATA)((u * f2 + (1 - u) * f1) * (1 - v) + ((1 - u) * f3 + u * f4) * v);
			}
		}
	}
}
