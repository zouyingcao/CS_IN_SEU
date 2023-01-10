// CImageScalingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageProcessing.h"
#include "CImageScalingDlg.h"
#include "afxdialogex.h"


// CImageScalingDlg 对话框

IMPLEMENT_DYNAMIC(CImageScalingDlg, CDialogEx)

CImageScalingDlg::CImageScalingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Scaling, pParent)
	, ratioY(1)
	, ratioX(1)
{

}

CImageScalingDlg::~CImageScalingDlg()
{
}

void CImageScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RatioY, ratioY);
	DDX_Text(pDX, IDC_EDIT_RatioX, ratioX);
}


BEGIN_MESSAGE_MAP(CImageScalingDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageScalingDlg 消息处理程序
