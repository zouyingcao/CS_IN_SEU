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

	void Gaussian(int wSize, double sigma, CImageData<T_DATA>*);//��˹�˲�
	void AveragingFilter(int wSize, CImageData<T_DATA>*);//��ֵ�˲���
	void MedianFilter(int wSize, CImageData<T_DATA>*);//��ֵ�˲���
	void Laplace(double k, CImageData<T_DATA>*);//����Laplace������
};
#endif
