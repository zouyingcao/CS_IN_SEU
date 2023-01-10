#pragma once
#include "CImageData.h"
#ifndef CIMAGEENHANCEMENT_H
#define CIMAGEENHANCEMENT_H

template <class T_DATA>
class CImageEnhancement :virtual public CImageData<T_DATA>
{
public:
	CImageEnhancement();
	~CImageEnhancement();

	void Gaussian(int wSize, double sigma, CImageData<T_DATA>*);//高斯滤波
	void AveragingFilter(int wSize, CImageData<T_DATA>*);//均值滤波器
	void MedianFilter(int wSize, CImageData<T_DATA>*);//中值滤波器
	void Laplace(double k, CImageData<T_DATA>*);//利用Laplace算子锐化
};
#endif
