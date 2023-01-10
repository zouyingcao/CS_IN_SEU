#include "pch.h"
#include "CImageEnhancement.h"
#include "CImageData.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

template <class T_DATA>
CImageEnhancement<T_DATA>::CImageEnhancement()
{
}

template <class T_DATA>
CImageEnhancement<T_DATA>::~CImageEnhancement()
{
}
/*
    ͨ��������˹�����ı�׼��(sigma)������ƽ���̶�
    wSizeΪ���ڴ�С��������
*/
template <class T_DATA>
void CImageEnhancement<T_DATA>::Gaussian(int wSize, double sigma, CImageData<T_DATA> *img)
{
	mHeight = img->GetHeight();
	mWidth = img->GetWidth();
	mpPixels = new T_DATA[mHeight * mWidth];
    // ��ʼ��
    for (int i = 0; i < mHeight; i++)
        for (int j = 0; j < mWidth; j++)
            *(mpPixels + i * mWidth + j) = *(img->GetData() + i * mWidth + j);
    // ���ڶ�λ�������ģ�Ҳ����ȷ��border
	int center = (wSize - 1)/2; 
	double Pi;
	Pi = atan(1) * 4; // pi
	// ����weight��ά������һά�洢
	double* weight = new double[wSize * wSize];
    double tempSum = 0;
    int x, y;
    for (int i = 0; i < wSize; i++){
        x = (i - center) * (i - center);
        for (int j = 0; j < wSize; j++){
            y = (j - center) * (j - center);
            // ��Ϊ���Ҫ��һ���ģ��������ֿ��Բ����㣬Ҳ������������
            *(weight + i * wSize + j) = exp(-(x + y) / (2 * sigma * sigma));
            tempSum += *(weight + i * wSize + j);
        }
    }
    // ��һ��
    for (int i = 0; i < wSize; i++)
        for (int j = 0; j < wSize; j++)
            *(weight + i * wSize + j) /= tempSum; 

    // ͼ��������˹�˲���
    for (int i = center; i < mHeight-center; i++)
        for (int j = center; j < mWidth-center; j++){
            tempSum = 0;
            for (int a = -center; a <= center; a++)
                for (int b = -center; b <= center; b++)
                    tempSum += (*(weight + (center + a) * wSize + (center + b))) * (*(img->GetData() + (i + a) * mWidth + (j + b)));
            if (tempSum < 0)tempSum = 0;
            if (tempSum > 4095)tempSum = 4095;
            *(mpPixels + i * mWidth + j) = (T_DATA)tempSum;
        }
    delete[] weight;
}
/*
    ��ֵ�˲�
*/
template<class T_DATA>
void CImageEnhancement<T_DATA>::AveragingFilter(int wSize, CImageData<T_DATA>* img)
{
    mHeight = img->GetHeight();
    mWidth = img->GetWidth();
    mpPixels = new T_DATA[mHeight * mWidth];
    // ��ʼ��
    for (int i = 0; i < mHeight; i++)
        for (int j = 0; j < mWidth; j++)
            *(mpPixels + i * mWidth + j) = *(img->GetData() + i * mWidth + j);
    // ���ڶ�λ�������ģ�Ҳ����ȷ��border
    int center = (wSize - 1) / 2;
    for (int i = center; i < mHeight- center; i++)
        for (int j = center; j < mWidth- center; j++)
        {
            int tempSum = 0;
            for (int a = -center; a <= center; a++)
                for (int b = -center; b <= center; b++)
                    tempSum += *(img->GetData() + (i + a) * mWidth + (j + b));
            *(mpPixels + i * mWidth + j) = tempSum / (wSize * wSize);
        }
}

/*
    �������ϸ��С����ֵ�˲��Ĵ���һ�룬��ᱻ�˵���
    ����Ĭ��ѡ�񴰿�Ϊ3*3
*/
template<class T_DATA>
void CImageEnhancement<T_DATA>::MedianFilter(int wSize, CImageData<T_DATA>* img)
{
    mHeight = img->GetHeight();
    mWidth = img->GetWidth();
    mpPixels = new T_DATA[mHeight * mWidth];
    int center = (wSize - 1) / 2;
    for (int i = 0; i < mHeight; i++)
        for (int j = 0; j < mWidth; j++)
        {
            if (i < center || j < center || i >= mHeight - center || j >= mWidth - center)
                *(mpPixels + i * mWidth + j) = *(img->GetData() + i * mWidth + j);
            else {
                vector<T_DATA> temp;
                for (int a = -center; a <= center; a++)
                    for (int b = -center; b <= center; b++)
                        temp.push_back(*(img->GetData() + (i + a) * mWidth + (j + b)));
                sort(temp.begin(), temp.end());
                *(mpPixels + i * mWidth + j) = temp[wSize * wSize / 2 + 1];
            }
        }
}

template <class T_DATA>
void CImageEnhancement<T_DATA>::Laplace(double k, CImageData<T_DATA>* img)
{
    double secondDerivative;
    double* pOldBits; // ��ԭͼ���е����ݿ�����pOldBits��
    pOldBits = new double[img->GetHeight() * img->GetWidth()];
    for (int i = 0; i < img->GetHeight(); i++)
        for (int j = 0; j < img->GetWidth(); j++)
            *(pOldBits + i * img->GetWidth() + j) = *(img->GetData() + i * img->GetWidth() + j);

    for (int i = 0; i < mHeight; i++)
        for (int j = 0; j < mWidth; j++) {
            if (i == 0 || j == 0 || i == mHeight - 1 || j == mWidth - 1)
                secondDerivative = 0;
            else
                secondDerivative = *(pOldBits + (i + 1) * mWidth + j) + *(pOldBits + (i - 1) * mWidth + j)
                                   + *(pOldBits + i * mWidth + j + 1) + *(pOldBits + i * mWidth + j - 1)
                                   - 4 * (*(pOldBits + i * mWidth + j));
            double temp = *(pOldBits + i * mWidth + j) - k * secondDerivative;
            if (temp < 0) 
                temp = 0;
            else if (temp > 4095) 
                temp = 4095;
            *(mpPixels + i * mWidth + j) = (T_DATA)temp;
        }
    delete[] pOldBits;
}