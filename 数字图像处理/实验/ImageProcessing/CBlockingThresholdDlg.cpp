// CBlockingThresholdDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageProcessing.h"
#include "CBlockingThresholdDlg.h"
#include "afxdialogex.h"


// CBlockingThresholdDlg 对话框

IMPLEMENT_DYNAMIC(CBlockingThresholdDlg, CDialogEx)

CBlockingThresholdDlg::CBlockingThresholdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Blocking, pParent)
	, col(0)
	, row(0)
{

}

CBlockingThresholdDlg::~CBlockingThresholdDlg()
{
}

void CBlockingThresholdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Col, col);
	DDX_Text(pDX, IDC_Row, row);
}


BEGIN_MESSAGE_MAP(CBlockingThresholdDlg, CDialogEx)
END_MESSAGE_MAP()


// CBlockingThresholdDlg 消息处理程序
