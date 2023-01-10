#pragma once
#ifndef CIMAGEDATA_H
#define CIMAGEDATA_H

template <class T_DATA>
class CImageData
{
public:
	CImageData();
	CImageData(int, int);
	virtual ~CImageData();

	bool Create(int, int);
	bool Copy(CImageData*);
	HRESULT Load(CString& imagePath);		// 加载图像
	HRESULT Save(CString& imagePath);		// 按指定文件路径imagePath保存图像
	void LoadFromRaw(CString& imagePath);

	int GetWidth();							// 图像宽度(以像素为单位)
	int GetHeight();						// 图像高度(以像素为单位)
	void SetWidth(int);						
	void SetHeight(int);
	T_DATA FindMaxVal();
	T_DATA FindMinVal();
	T_DATA* GetData();						// 返回当前图像像素数据

	void Draw(HDC, int, int);				// 绘制

protected:
	int mHeight;
	int mWidth;
	T_DATA* mpPixels;
};
#endif