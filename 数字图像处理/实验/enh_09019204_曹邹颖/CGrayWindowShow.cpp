#include "pch.h"
#include "CGrayWindowShow.h"
#include <iostream>
using namespace std;

template <class T_DATA>
CGrayWindowShow<T_DATA>::CGrayWindowShow()
{

}

template <class T_DATA>
CGrayWindowShow<T_DATA>::~CGrayWindowShow()
{

}

template <class T_DATA>
void CGrayWindowShow<T_DATA>::GrayMapping(int windowWidth,int windowLevel,CImageData<unsigned short>*img)
{
	mHeight = img->GetHeight();
	mWidth = img->GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];

	for (int j = 0; j < mHeight; j++)
		for (int i = 0; i < mWidth; i++)
		{
			double oldPixel = *(img->GetData()+j * mWidth + i);
			double upper = double(windowLevel) + double(windowWidth) / 2.0;
			double lower = double(windowLevel) - double(windowWidth) / 2.0;
			if (oldPixel > upper)
				mpPixels[j * mWidth + i] = T_DATA(255);
			else if (oldPixel < lower)
				mpPixels[j * mWidth + i] = T_DATA(0);
			else
				mpPixels[j * mWidth + i] = 255.0 * (oldPixel - lower) / double(windowWidth);
		}
}