// CGrayWindowDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "ImageProcessing.h"
#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"
#include "CGrayWindowDlg.h"
#include "CImageEnhancementDlg.h"
#include "afxdialogex.h"


// CGrayWindowDlg 对话框

IMPLEMENT_DYNAMIC(CGrayWindowDlg, CDialogEx)

CGrayWindowDlg::CGrayWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GrayWindow, pParent)
	, windowWidth(0)
	, windowLevel(0)
{

}

CGrayWindowDlg::~CGrayWindowDlg()
{
}

void CGrayWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WindowLevel, windowLevel);
	DDX_Text(pDX, IDC_WindowWidth, windowWidth);
}


BEGIN_MESSAGE_MAP(CGrayWindowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_btnLoadRaw, &CGrayWindowDlg::OnBnClickedLoadImage)
	ON_BN_CLICKED(IDC_btnImageEnhancement, &CGrayWindowDlg::OnBnClickedImageEnhancement)
END_MESSAGE_MAP()


// CGrayWindowDlg 消息处理程序


void CGrayWindowDlg::OnBnClickedLoadImage()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CImageProcessingView* View = (CImageProcessingView*)p->GetActiveView();
	CImageProcessingDoc* pDoc = View->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString strFilter;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	if (IDOK != dlg.DoModal())
		return;
	
	// 销毁原有文件内容
	if (pDoc->rawImage.GetData() != NULL)
		pDoc->rawImage.~CImageData();

	pDoc->rawImage.LoadFromRaw(dlg.GetPathName());
}


void CGrayWindowDlg::OnBnClickedImageEnhancement()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CImageProcessingView* View = (CImageProcessingView*)p->GetActiveView();
	CImageProcessingDoc* pDoc = View->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 销毁原有文件内容
	if (pDoc->enhancedImage.GetData() != NULL)
		pDoc->enhancedImage.~CImageEnhancement();
	CImageEnhancementDlg dlg;
	if (dlg.DoModal() == IDOK) {
		switch (dlg.Filter_Ratio) {
		case 0:
			pDoc->enhancedImage.Gaussian(dlg.Gauss_wSize, dlg.sigma, &pDoc->rawImage);
			break;
		case 1:
			pDoc->enhancedImage.AveragingFilter(dlg.avg_wSize, &pDoc->rawImage);
			break;
		case 2:
			pDoc->enhancedImage.MedianFilter(dlg.mid_wSize, &pDoc->rawImage);
			break;
		default:
			break;
		}
		pDoc->enhancedImage.Laplace(dlg.k, &pDoc->enhancedImage);
	}
}
