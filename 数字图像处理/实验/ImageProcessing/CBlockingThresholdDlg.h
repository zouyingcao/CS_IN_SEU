#pragma once


// CBlockingThresholdDlg 对话框

class CBlockingThresholdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBlockingThresholdDlg)

public:
	CBlockingThresholdDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBlockingThresholdDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Blocking };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int col;
	int row;
};
