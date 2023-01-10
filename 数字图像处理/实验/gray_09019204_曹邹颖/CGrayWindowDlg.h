#pragma once


// CGrayWindowDlg 对话框

class CGrayWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGrayWindowDlg)

public:
	CGrayWindowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGrayWindowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GrayWindow };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int windowWidth;
	int windowLevel;
	afx_msg void OnBnClickedLoadImage();
};
