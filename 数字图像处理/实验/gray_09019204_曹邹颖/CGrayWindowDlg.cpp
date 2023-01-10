// CGrayWindowDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "ImageProcessing.h"
#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"
#include "CGrayWindowDlg.h"
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
	ON_BN_CLICKED(IDC_BUTTON1, &CGrayWindowDlg::OnBnClickedLoadImage)
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
