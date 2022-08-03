
// PortScanToolDlg.h: 头文件
//

#pragma once


// CPortScanToolDlg 对话框
class CPortScanToolDlg : public CDialogEx
{
// 构造
public:
	CPortScanToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTSCANTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_strIP;
	CStatic m_default_port;
	CProgressCtrl m_progress_scanner;
	CListCtrl m_list_data;
	CEdit m_single_port;
	CEdit m_from_port;
	CEdit m_to_port;
	CEdit m_thread_number;
};
