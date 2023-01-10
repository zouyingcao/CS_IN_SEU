#pragma once


// CImageRotateDlg 对话框

class CImageRotateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageRotateDlg)

public:
	CImageRotateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageRotateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Rotate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double degree;
	double rotateX;
	double rotateY;
};
