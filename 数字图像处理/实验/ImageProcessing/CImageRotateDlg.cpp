// CImageRotateDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageProcessing.h"
#include "CImageRotateDlg.h"
#include "afxdialogex.h"


// CImageRotateDlg 对话框

IMPLEMENT_DYNAMIC(CImageRotateDlg, CDialogEx)

CImageRotateDlg::CImageRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Rotate, pParent)
	, degree(0)
	, rotateX(0)
	, rotateY(0)
{

}

CImageRotateDlg::~CImageRotateDlg()
{
}

void CImageRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Degree, degree);
	DDX_Text(pDX, IDC_EDIT_RotateX, rotateX);
	DDX_Text(pDX, IDC_EDIT_RotateY, rotateY);
}


BEGIN_MESSAGE_MAP(CImageRotateDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageRotateDlg 消息处理程序
