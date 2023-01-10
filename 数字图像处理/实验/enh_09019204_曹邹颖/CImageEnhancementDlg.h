#pragma once


// CImageEnhancementDlg 对话框

class CImageEnhancementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageEnhancementDlg)

public:
	CImageEnhancementDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageEnhancementDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Enhancement };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Filter_Ratio;
	int Gauss_wSize;
	int avg_wSize;
	int mid_wSize;
	double sigma;
	double k;
	afx_msg void OnBnClickedRadioGaussian();
	afx_msg void OnBnClickedRadioAveragingfilter();
	afx_msg void OnBnClickedRadioMedianfilter();
};
