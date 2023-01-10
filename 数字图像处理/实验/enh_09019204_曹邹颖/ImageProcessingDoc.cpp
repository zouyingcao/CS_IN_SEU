
// ImageProcessingDoc.cpp: CImageProcessingDoc 类的实现
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "CImageData.h"
#include "CGeometricTransform.h"
#include "CGrayWindowDlg.h"
#include "CGrayWindowShow.h"
#include <propkey.h>
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CImageProcessingDoc::OnImageOpen)
	ON_COMMAND(ID_FILE_NEW, &CImageProcessingDoc::OnRawImageShow)
END_MESSAGE_MAP()


// CImageProcessingDoc 构造/析构

CImageProcessingDoc::CImageProcessingDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CImageProcessingDoc 序列化

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 诊断

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 命令


void CImageProcessingDoc::OnImageOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString strFilter;
	HRESULT hResult=NULL;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;

	// 销毁原有文件内容
	if (m_sImage.GetData() != NULL)
		m_sImage.~CImageData();
	/*
	if (m_rImage.GetData() != NULL)
		m_rImage.~CImageData();
	*/

	// 通过CImage类将外部图像文件装载到m_sImage中
	hResult = m_sImage.Load(dlg.GetPathName());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("图像文件加载失败！"));
		return;
	}

	// 设置主窗口标题栏内容
	CString str;
	str.LoadString(AFX_IDS_APP_TITLE);
	AfxGetMainWnd()->SetWindowText(str + " - " + dlg.GetFileName());
	InvalidateRect(NULL, NULL, FALSE);	// 刷新窗口

}


void CImageProcessingDoc::OnRawImageShow()
{
	CGrayWindowDlg dlg;

	if (dlg.DoModal() == IDOK) //显示对话框
	{
		if (rawImage.GetData() == NULL)
		{
			AfxMessageBox(_T("请先载入灰度图像文件！"));
			return;
		}
		if(enhancedImage.GetData() !=NULL)
			s_rawImage.GrayMapping(dlg.windowWidth, dlg.windowLevel, &enhancedImage);
		else
			s_rawImage.GrayMapping(dlg.windowWidth, dlg.windowLevel,&rawImage);
	}
}
