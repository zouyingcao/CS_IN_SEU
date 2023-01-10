#pragma once
#include "CImageData.h"
#ifndef CGEOMETRICTRANSFORM_H
#define CGEOMETRICTRANSFORM_H

template <class T_DATA>
class CGeometricTransform:virtual public CImageData<T_DATA>
{
public:
	CGeometricTransform();
	~CGeometricTransform();

	void Translation(double,double, CImageData<T_DATA>*);
	void Rotate(double, double, double, CImageData<T_DATA>*);
	void Scaling(double,double, CImageData<T_DATA>*);
	void AffineTransformation(double A00, double A01, double A02, double A10, double A11, double A12, T_DATA* pOldBits, int OldWidth, int OldHeight);
};
#endif