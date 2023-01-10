#pragma once
#pragma once
#include "CImageData.h"
#ifndef CGRAYWINDOWSHOW_H
#define CGRAYWINDOWSHOW_H

template <class T_DATA>
class CGrayWindowShow :virtual public CImageData<T_DATA>
{
public:
	CGrayWindowShow();
	~CGrayWindowShow();

	void GrayMapping(int, int, CImageData<unsigned short>*);
};
#endif
