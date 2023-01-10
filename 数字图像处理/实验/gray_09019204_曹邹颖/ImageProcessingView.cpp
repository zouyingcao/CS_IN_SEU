
// ImageProcessingView.cpp: CImageProcessingView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"
#include "CGeometricTransform.h"
#include "CImageTranslationDlg.h"
#include "CImageRotateDlg.h"
#include "CImageScalingDlg.h"
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Translation, &CImageProcessingView::OnTranslation)
	ON_COMMAND(ID_Scaling, &CImageProcessingView::OnScaling)
	ON_COMMAND(ID_Rotation, &CImageProcessingView::OnRotation)
END_MESSAGE_MAP()

// CImageProcessingView 构造/析构

CImageProcessingView::CImageProcessingView() noexcept
{
	// TODO: 在此处添加构造代码

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImageProcessingView 绘图

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	// BMP原始图像显示在窗口左上角
	if (pDoc->m_sImage.GetData() != NULL)
		(pDoc->m_sImage).Draw(pDC->m_hDC, 0, 0);
	
	// 几何变换目标图像从原始图像右边100个像素的位置开始显示
	if (pDoc->m_rImage.GetData() != NULL )
		(pDoc->m_rImage).Draw(pDC->m_hDC, pDoc->m_sImage.GetWidth() + 100, 0);

	// 自定义格式图像灰度窗显示在窗口左上角
	if (pDoc->s_rawImage.GetData() != NULL)
		(pDoc->s_rawImage).Draw(pDC->m_hDC, 0, 0);
}

void CImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	//sizeTotal.cx = sizeTotal.cy = 100;
	sizeTotal.cx = 4000; sizeTotal.cy = 2000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProcessingView 打印


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessingView 诊断

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 消息处理程序


void CImageProcessingView::OnTranslation()
{
	// TODO: 在此添加命令处理程序代码
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CImageTranslationDlg dlg;

	if (dlg.DoModal() == IDOK) //显示对话框
	{
		if (dlg.translationX > pDoc->m_sImage.GetWidth() || dlg.translationY > pDoc->m_sImage.GetHeight()) {
			AfxMessageBox(_T("图片平移不能为超过原图长宽!"));
			return;
		}
		pDoc->m_rImage.Translation(dlg.translationX, dlg.translationY, &(pDoc->m_sImage));
		Invalidate();
	}
}


void CImageProcessingView::OnScaling()
{
	// TODO: 在此添加命令处理程序代码
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CImageScalingDlg dlg;
	if (dlg.DoModal() == IDOK) //显示对话框
	{
		pDoc->m_rImage.Scaling(dlg.ratioX, dlg.ratioY,&(pDoc->m_sImage));
		Invalidate();
	}
}


void CImageProcessingView::OnRotation()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CImageRotateDlg dlg;
	if (dlg.DoModal() == IDOK) //显示对话框
	{
		pDoc->m_rImage.Rotate(dlg.degree,dlg.rotateX,dlg.rotateY, &(pDoc->m_sImage));
		Invalidate();
	}
}
