
// PortScanToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PortScanTool.h"
#include "PortScanToolDlg.h"
#include "afxdialogex.h"
#include "Scanner.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPortScanToolDlg 对话框



CPortScanToolDlg::CPortScanToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PORTSCANTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortScanToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_strIP);
	DDX_Control(pDX, IDC_STATIC_DEFAULT_PORT, m_default_port);
	DDX_Control(pDX, IDC_PROGRESS_SCANNER, m_progress_scanner);
	DDX_Control(pDX, IDC_LIST_DATA, m_list_data);
	DDX_Control(pDX, IDC_EDIT_SINGLE_PORT, m_single_port);
	DDX_Control(pDX, IDC_EDIT_MUL_PORT_FROM, m_from_port);
	DDX_Control(pDX, IDC_EDIT_MUL_PORT_TO, m_to_port);
	DDX_Control(pDX, IDC_EDIT_NUMBER_OF_THREAD, m_thread_number);
	DDX_Control(pDX, IDC_BTN_START_SCAN, m_btn_start);
	DDX_Control(pDX, IDC_BTN_STOP_SCAN, m_btn_stop);
}

BEGIN_MESSAGE_MAP(CPortScanToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_SCAN, &CPortScanToolDlg::OnBnClickedBtnStartScan)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CPortScanToolDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_STOP_SCAN, &CPortScanToolDlg::OnBnClickedBtnStopScan)
END_MESSAGE_MAP()


// CPortScanToolDlg 消息处理程序

BOOL CPortScanToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//默认显示内容

	m_strIP.SetAddress(127, 0, 0, 1);
	m_single_port.SetWindowTextW(TEXT("1"));
	m_from_port.SetWindowTextW(TEXT("1"));
	m_to_port.SetWindowTextW(TEXT("65535"));
	m_thread_number.SetWindowTextW(TEXT("100"));
	UpdateData(FALSE);

	//初始化进度条
	m_progress_scanner.SetRange(0, 100);
	m_progress_scanner.SetPos(0);

	//初始化按键状态
	m_btn_start.EnableWindow(1);
	m_btn_stop.EnableWindow(0);

	//初始化列表
	m_list_data.InsertColumn(0, _T("当前扫描IP地址"), LVCFMT_LEFT, 220, 0);
	m_list_data.InsertColumn(1, _T("开放端口编号"), LVCFMT_LEFT, 220, 1); 
	DWORD dwStyle = m_list_data.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	m_list_data.SetExtendedStyle(dwStyle);

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPortScanToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPortScanToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPortScanToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortScanToolDlg::OnBnClickedBtnStartScan()
{
	// TODO: 在此添加控件通知处理程序代码
	stopit = 0;
	m_list_data.DeleteAllItems();
	m_btn_start.EnableWindow(0);
	m_btn_stop.EnableWindow(1);
	UpdateData(0);
	CString strPortFrom, strPortTo;
	CString IP = GetIPAdds(&m_strIP);
	int portFrom, portTo;
	CString strThreadNumber;
	int threadNumber = 1;
	std::thread* th;
	if (((CButton*)GetDlgItem(IDC_RADIO_SINGLE_PORT))->GetCheck())
	{
		m_single_port.GetWindowTextW(strPortFrom); 
		if (strPortFrom.IsEmpty())
		{
			MessageBoxW(TEXT("请输入端口!"));
			goto End;
		}
		portFrom = portTo= _ttoi(strPortFrom);
		threadNumber = 1;
	}
	else if(((CButton*)GetDlgItem(IDC_RADIO_MUL_PORT))->GetCheck())
	{
		m_from_port.GetWindowTextW(strPortFrom);
		m_to_port.GetWindowTextW(strPortTo);
		if (strPortFrom.IsEmpty() || strPortTo.IsEmpty())
		{
			MessageBoxW(TEXT("请输入端口!"));
			goto End;
		}
		m_thread_number.GetWindowTextW(strThreadNumber);
		if (strThreadNumber.IsEmpty())
		{
			MessageBoxW(TEXT("请输入线程数!"));
			goto End;
		}
		portFrom = _ttoi(strPortFrom);
		portTo = _ttoi(strPortTo);
		threadNumber = _ttoi(strThreadNumber);
	}
	else
	{
		MessageBoxW(TEXT("未勾选端口!"));
		goto End;
	}

	int totalPort = portTo - portFrom + 1;
	m_progress_scanner.SetRange(0, totalPort);
	m_progress_scanner.SetPos(0);
	

	//scant(portFrom, portTo, IP, threadNumber, &stopit, &m_default_port, &m_list_data, &m_progress_scanner);
	th = new std::thread(scant, portFrom, portTo, IP, threadNumber, &stopit, &m_default_port, &m_list_data, &m_progress_scanner,&m_btn_start,&m_btn_stop);
	//th->join();

	return;
	

End:;
	m_progress_scanner.SetPos(0);
	m_default_port.SetWindowTextW(L"当前扫描:");

	m_btn_start.EnableWindow(1);
	m_btn_stop.EnableWindow(0);
}

void scant(int portFrom, int portTo, CString IP,int threadNumber,int * stopit, CStatic *m_default_port, CListCtrl* m_list_data,CProgressCtrl* m_progress_scanner,CButton* m_btn_start,CButton* m_btn_stop)
{
	int totalPort = portTo - portFrom + 1;


	Scanner* scanner = new Scanner();


	int total_open_port = 0;


	{
		std::vector<int>isOpen(portTo + 1);
		for (int i = portFrom; i <= portTo; i += threadNumber)
		{
			if (*stopit)
				goto End;
			int from = i, to = min(portTo, i + threadNumber);
			std::vector<std::thread*>threadList;
			for (int j = from; j <= to; j++)
			{
				CString str;
				str.Format(L"当前扫描:%d", j);
				m_default_port->SetWindowTextW(str);
				std::thread* p = new std::thread(scanner->PortOpen, IP, j, &isOpen[j],stopit);
				threadList.push_back(p);
			}
			for (const auto& th : threadList)
			{
				if (*stopit)
					goto End;
				th->join();
			}
			CString strNum;
			for (int j = from; j <= to; j++)
			{
				if (isOpen[j])
				{
					strNum.Format(L"%d", j);
					m_list_data->InsertItem(total_open_port, IP);
					m_list_data->SetItemText(total_open_port, 1, strNum);
					total_open_port++;
				}
			}
			m_progress_scanner->SetPos(to - portFrom);
		}
	}

End:;
	Sleep(500);
	m_progress_scanner->SetPos(0);
	m_default_port->SetWindowTextW(L"当前扫描:");

	m_btn_start->EnableWindow(1);
	m_btn_stop->EnableWindow(0);
	delete scanner;
}

CString GetIPAdds(CIPAddressCtrl* pIPAddrCtrl)
{


	BYTE byField0;

	BYTE byField1;
	BYTE byField2;
	BYTE byField3;

	pIPAddrCtrl->GetAddress(byField0, byField1, byField2, byField3);
	CString IPStr;

	IPStr.Format(_T("%d.%d.%d.%d"), byField0, byField1, byField2, byField3);

	return IPStr;

}






void CPortScanToolDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CPortScanToolDlg::OnBnClickedBtnStopScan()
{
	// TODO: 在此添加控件通知处理程序代码
	stopit = 1;
	m_btn_start.EnableWindow(1);
	m_btn_stop.EnableWindow(0);
}

void CPortScanToolDlg::OnOK()
{
}

