#include "pch.h"
#include "CImageData.h"
#include <iostream>
#include <afxwin.h>
#include <atlimage.h>
using namespace std;
#define OUT_MAX_VAL 255;

template <class T_DATA>
CImageData<T_DATA>::CImageData()
{
	mHeight = 0;
	mWidth = 0;
	mpPixels = NULL;
}

template <class T_DATA>
CImageData<T_DATA>::CImageData(int height,int width)
{
	mHeight = height;
	mWidth = width;
	mpPixels = new T_DATA[mHeight* mWidth];
}

template <class T_DATA>
CImageData<T_DATA>::~CImageData()
{
	if (mpPixels != NULL) {
		delete []mpPixels;
	}
}

template <class T_DATA>
bool CImageData<T_DATA>::Create(int width,int height)
{
	if (width == 0 || height == 0)
		return false;
	mHeight = height;
	mWidth = width;
	mpPixels = new T_DATA[mHeight * mWidth];
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			*(mpPixels + y * mWidth + x) = T_DATA(0);
	return true;
}

template <class T_DATA>
bool CImageData<T_DATA>::Copy(CImageData* cImageData)
{
	if (cImageData == NULL || cImageData->GetHeight() == 0 || cImageData->GetWidth() == 0 || cImageData->GetData() == NULL)
		return false;
	mHeight = cImageData->GetHeight();
	mWidth = cImageData->GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];
	for (int y = 0; y < mHeight; y++)
		for (int x = 0; x < mWidth; x++)
			*(mpPixels + y * mWidth + x) = *(cImageData->GetData()+ y * mWidth + x);//T_DATA����
	return true;
}

template <class T_DATA>
HRESULT CImageData<T_DATA>::Load(CString& imagePath)
{
	CImage mpImage;
	HRESULT hResult = mpImage.Load(imagePath);
	mHeight = mpImage.GetHeight();
	mWidth = mpImage.GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];

	T_DATA* pData = (T_DATA*)mpImage.GetBits();	//ͼ���һ��head
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
			*(mpPixels + y * mWidth + x) = *(pData + x);
		pData += mpImage.GetPitch();//���ڴ��е��Ŷ�
	}
	return hResult;
}

template <class T_DATA>
HRESULT CImageData<T_DATA>::Save(CString& imagePath)
{
	CImage mpImage;
	mpImage.Create(mWidth, -mHeight, 8*sizeof(T_DATA));

	//�ؼ���8λͼ������ɫ�壬����ͼ��ȫ��
	if (sizeof(T_DATA) == 1) {
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		ColorTable = new RGBQUAD[MaxColors];
		mpImage.GetColorTable(0, MaxColors, ColorTable);
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		mpImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	int rowBytes = mpImage.GetPitch();
	T_DATA* pData = (T_DATA*)mpImage.GetBits();

	T_DATA MaxVal = FindMaxVal();
	T_DATA MinVal = FindMinVal();

	if (MaxVal > MinVal)
	{
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
				// �ȹ�һ����0-255֮�� # define OUT_MAX_VAL 255
				*(pData + x) = (*(mpPixels + y * mWidth + x) - MinVal) * 255 /(MaxVal - MinVal);
			pData += rowBytes;
		}
	}
	return mpImage.Save(imagePath);
}

template <class T_DATA>
int CImageData<T_DATA>::GetWidth()
{
	return mWidth;
}

template <class T_DATA>
int CImageData<T_DATA>::GetHeight()
{
	return mHeight;
}

template <class T_DATA>
void CImageData<T_DATA>::SetWidth(int w)
{
	mWidth=w;
}

template <class T_DATA>
void CImageData<T_DATA>::SetHeight(int h)
{
	mHeight=h;
}

template <class T_DATA>
T_DATA CImageData<T_DATA>::FindMaxVal()
{
	T_DATA max = 0;
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (*(mpPixels + y * mWidth + x) > max)
				max = *(mpPixels + y * mWidth + x);
		}
	}
	return max;
}

template <class T_DATA>
T_DATA CImageData<T_DATA>::FindMinVal()
{
	T_DATA min = *mpPixels;
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (*(mpPixels + y * mWidth + x) < min)
				min = *(mpPixels + y * mWidth + x);
		}
	}
	return min;
}

template <class T_DATA>
T_DATA* CImageData<T_DATA>::GetData()
{
	return mpPixels;
}

template <class T_DATA>
void CImageData<T_DATA>::Draw(HDC hDC, int x, int y)
{
	if (mpPixels == NULL)
		return;
	else {
		CImage mpImage;
		mpImage.Create(mWidth, -mHeight, 8 * sizeof(T_DATA));//-mHeight(����)��ӦGetPitch()Ϊ��,����ԭ��
		
		//�ؼ���8λͼ������ɫ�壬����ͼ��ȫ��
		if (sizeof(T_DATA) == 1) {
			RGBQUAD* ColorTable;
			int MaxColors = 256;
			ColorTable = new RGBQUAD[MaxColors];
			mpImage.GetColorTable(0, MaxColors, ColorTable);
			for (int i = 0; i < MaxColors; i++)
			{
				ColorTable[i].rgbBlue = (BYTE)i;
				ColorTable[i].rgbGreen = (BYTE)i;
				ColorTable[i].rgbRed = (BYTE)i;
			}
			mpImage.SetColorTable(0, MaxColors, ColorTable);
			delete[]ColorTable;
		}

		int rowBytes = mpImage.GetPitch();//����
		T_DATA* pData = (T_DATA*)(mpImage.GetBits());// �ڴ�head��ͼ���һ��head
		T_DATA MaxVal = FindMaxVal();
		T_DATA MinVal = FindMinVal();

		if (MaxVal > MinVal)
		{
			for (int y = 0; y < mHeight; y++)
			{
				for (int x = 0; x < mWidth; x++)
				{
					// �ȹ�һ����0-255֮��
					*(pData + x) = (*(mpPixels + y * mWidth + x) - MinVal) * 255 / (MaxVal - MinVal);
				}
				pData += rowBytes;
			}
		}
		mpImage.Draw(hDC, x, y);
	}
}