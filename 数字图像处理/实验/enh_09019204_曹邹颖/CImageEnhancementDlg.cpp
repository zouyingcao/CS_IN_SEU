// CImageEnhancementDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageProcessing.h"
#include "CImageEnhancementDlg.h"
#include "afxdialogex.h"


// CImageEnhancementDlg 对话框

IMPLEMENT_DYNAMIC(CImageEnhancementDlg, CDialogEx)

CImageEnhancementDlg::CImageEnhancementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Enhancement, pParent)
	, Filter_Ratio(-1)
	, avg_wSize(3)
	, mid_wSize(3)
	, Gauss_wSize(3)
	, sigma(1)
	, k(1)
{

}

CImageEnhancementDlg::~CImageEnhancementDlg()
{
}

void CImageEnhancementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_Gaussian, Filter_Ratio);
	DDX_Text(pDX, IDC_sigma, sigma);
	DDX_Text(pDX, IDC_Gauss_wSize, Gauss_wSize);
	DDX_Text(pDX, IDC_avg_wSize, avg_wSize);
	DDX_Text(pDX, IDC_mid_wSize, mid_wSize);
	DDX_Text(pDX, IDC_alpha, k);
}


BEGIN_MESSAGE_MAP(CImageEnhancementDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_Gaussian, &CImageEnhancementDlg::OnBnClickedRadioGaussian)
	ON_BN_CLICKED(IDC_RADIO_AveragingFilter, &CImageEnhancementDlg::OnBnClickedRadioAveragingfilter)
	ON_BN_CLICKED(IDC_RADIO_MedianFilter, &CImageEnhancementDlg::OnBnClickedRadioMedianfilter)
END_MESSAGE_MAP()


// CImageEnhancementDlg 消息处理程序

void CImageEnhancementDlg::OnBnClickedRadioGaussian()
{
	Filter_Ratio = 0;
}


void CImageEnhancementDlg::OnBnClickedRadioAveragingfilter()
{
	Filter_Ratio = 1;
}


void CImageEnhancementDlg::OnBnClickedRadioMedianfilter()
{
	Filter_Ratio = 2;
}
