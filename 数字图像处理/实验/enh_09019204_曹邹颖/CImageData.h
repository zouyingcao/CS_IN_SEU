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
	HRESULT Load(CString& imagePath);		// ����ͼ��
	HRESULT Save(CString& imagePath);		// ��ָ���ļ�·��imagePath����ͼ��
	void LoadFromRaw(CString& imagePath);

	int GetWidth();							// ͼ����(������Ϊ��λ)
	int GetHeight();						// ͼ��߶�(������Ϊ��λ)
	void SetWidth(int);						
	void SetHeight(int);
	T_DATA FindMaxVal();
	T_DATA FindMinVal();
	T_DATA* GetData();						// ���ص�ǰͼ����������

	void Draw(HDC, int, int);				// ����

protected:
	int mHeight;
	int mWidth;
	T_DATA* mpPixels;
};
#endif