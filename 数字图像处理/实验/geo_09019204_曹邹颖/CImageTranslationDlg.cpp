// CImageTranslationDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageProcessing.h"
#include "CImageTranslationDlg.h"
#include "afxdialogex.h"


// CImageTranslationDlg 对话框

IMPLEMENT_DYNAMIC(CImageTranslationDlg, CDialogEx)

CImageTranslationDlg::CImageTranslationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Translation, pParent)
	, translationX(0)
	, translationY(0)
{

}

CImageTranslationDlg::~CImageTranslationDlg()
{
}

void CImageTranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TranslationX, translationX);
	DDX_Text(pDX, IDC_EDIT_TranslationY, translationY);
}


// CImageTranslationDlg 消息处理程序

BEGIN_MESSAGE_MAP(CImageTranslationDlg, CDialogEx)
END_MESSAGE_MAP()
