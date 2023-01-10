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

	T_DATA OtsuThreshold(CImageData<T_DATA>* img);						// 大津阈值
	void GlobalThreshold(CImageData<T_DATA>* img);						// 全局阈值
	//void RegionGrow(CImageData<T_DATA>* img,T_DATA t=30);				// 区域增长
	T_DATA GrayDiffer(CImageData<T_DATA>* img, T_DATA threshold);		// 类间灰度差作为可分性度量(辅助分块阈值法)
	void BlockingThreshold(CImageData<T_DATA>* img,int row=9,int col=9);// 分块阈值
};
#endif