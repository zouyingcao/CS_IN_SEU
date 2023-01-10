#pragma once
#include "CImageData.h"
#ifndef CIMAGESEGMENTATION_H
#define CIMAGESEGMENTATION_H

template <class T_DATA>
class CImageSegmentation :virtual public CImageData<T_DATA>
{
public:
	CImageSegmentation();
	~CImageSegmentation();

	T_DATA OtsuThreshold(CImageData<T_DATA>* img);						// �����ֵ
	void GlobalThreshold(CImageData<T_DATA>* img);						// ȫ����ֵ
	//void RegionGrow(CImageData<T_DATA>* img,T_DATA t=30);				// ��������
	T_DATA GrayDiffer(CImageData<T_DATA>* img, T_DATA threshold);		// ���ҶȲ���Ϊ�ɷ��Զ���(�����ֿ���ֵ��)
	void BlockingThreshold(CImageData<T_DATA>* img,int row=9,int col=9);// �ֿ���ֵ
};
#endif