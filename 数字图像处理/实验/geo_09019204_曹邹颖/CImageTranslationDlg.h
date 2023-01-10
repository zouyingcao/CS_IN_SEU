#pragma once


// CImageTranslationDlg 对话框

class CImageTranslationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageTranslationDlg)

public:
	CImageTranslationDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageTranslationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Translation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	double translationX;
	double translationY;
	
};
