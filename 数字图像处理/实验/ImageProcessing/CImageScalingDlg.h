#pragma once


// CImageScalingDlg 对话框

class CImageScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageScalingDlg)

public:
	CImageScalingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageScalingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Scaling };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double ratioY;
	double ratioX;
};
