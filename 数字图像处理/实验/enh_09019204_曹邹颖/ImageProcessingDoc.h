
// ImageProcessingDoc.h: CImageProcessingDoc 类的接口
//


#pragma once
#include"CImageData.h"
#include"CImageData.cpp"
#include"CGeometricTransform.h"
#include"CGeometricTransform.cpp"
#include"CGrayWindowShow.h"
#include"CGrayWindowShow.cpp"
#include"CImageEnhancement.h"
#include"CImageEnhancement.cpp"

class CImageProcessingDoc : public CDocument
{
protected: // 仅从序列化创建
	CImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 特性
public:
	//对CImageProcessingDoc类添加新的成员变量，用于存放“原始图像”和“处理后的图像”，
	CImageData<BYTE> m_sImage;//BMP原始图像
	CGeometricTransform<BYTE>  m_rImage;//几何变换处理后的图像
	
	CImageData<unsigned short> rawImage;//自定义格式图像文件
	CGrayWindowShow<BYTE> s_rawImage;//灰度窗
	CImageEnhancement<unsigned short> enhancedImage;//图像增强后的图像
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnImageOpen();
	afx_msg void OnRawImageShow();
};
