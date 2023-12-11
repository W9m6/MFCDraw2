
// MFCDrawDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCDraw.h"
#include "MFCDrawDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265358979323846

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


// CMFCDrawDlg 对话框



CMFCDrawDlg::CMFCDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DRAW, m_canvas);
}

BEGIN_MESSAGE_MAP(CMFCDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDrawDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDrawDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCDrawDlg 消息处理程序

BOOL CMFCDrawDlg::OnInitDialog()
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

	UpdateStaticText();
	// 设置时钟频率 每秒更新一次时间
	SetTimer(1, 1000, NULL);

	// 设置字体
	myFont.CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"宋体");
	GetDlgItem(IDC_STATIC_YEAR)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_MONTH)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_DAY)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC1)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC2)->SetFont(&myFont);
	GetDlgItem(IDC_STATIC3)->SetFont(&myFont);
	
	// 设置画布大小 // x,y,nWidth,nHeight
	m_canvas.MoveWindow(baseX - r, baseY - r, r * 2, r * 2);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

}

void CMFCDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDrawDlg::OnPaint()
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
		CPaintDC dc(this); // 设备描述符

		// 获取静态文本框处的矩形
		CRect rectView;
		GetDlgItem(IDC_STATIC_DRAW)->GetWindowRect(&rectView);
		ScreenToClient(&rectView);

		// 选择画刷和画笔
		CBrush brush(RGB(255, 0, 0)); // 创建一个红色画刷
		dc.SelectObject(&brush);

		CPen pen(PS_SOLID, 2, RGB(255, 255, 255)); // 创建一个白色画笔
		dc.SelectObject(&pen);

		// 在设备上下文中绘制一个圆
		dc.Ellipse(rectView);

		//横坐标=圆半径×cos(圆心角)
		//纵坐标 = 圆半径×sin(圆心角)
		//i 个圆心角 = i × 2 × PI / N;
		n = 10;
		for (int i = 0; i <= n-2; ++i) {
			double angle1 = i * 2 * PI / n;
			int x1 = baseX + r * cos(angle1);
			int y1 = baseY + r * sin(angle1);
			for (int j = i + 1; j <= n-1; ++j) {
				double angle2 = j * 2 * PI / n;
				int x2 = baseX + r * cos(angle2);
				int y2 = baseY + r * sin(angle2);
				// 连线
				dc.MoveTo(x1, y1);
				dc.LineTo(x2, y2);
			}
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 获取当前系统时间
void CMFCDrawDlg::UpdateStaticText() 
{
	CTime currentTime = CTime::GetCurrentTime();

	// 获取年、月、时、分、秒
	int year = currentTime.GetYear();
	int month = currentTime.GetMonth();
	int day = currentTime.GetDay();
	int hour = currentTime.GetHour();
	int minute = currentTime.GetMinute();
	int second = currentTime.GetSecond();

	// 将年、月、日、时、分、秒分别更新到对应的static text控件
	SetDlgItemInt(IDC_STATIC_YEAR, year);
	SetDlgItemInt(IDC_STATIC_MONTH, month);
	SetDlgItemInt(IDC_STATIC_DAY, day);
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), hour, minute, second);
	SetDlgItemText(IDC_STATIC_TIME, strTime);
}

void CMFCDrawDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UpdateStaticText();
}

// 设置时间字体颜色
HBRUSH CMFCDrawDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_YEAR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MONTH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DAY)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

// 画刷颜色
void CMFCDrawDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colorDlg;
	 // 设置颜色对话框的初始颜色
	COLORREF initialColor = RGB(255, 0, 0); // 例如，初始颜色为红色
	colorDlg.m_cc.rgbResult = initialColor;
	colorDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;

	// 显示颜色对话框
	if (colorDlg.DoModal() == IDOK)
	{
		// 用户点击了确定按钮，获取选择的颜色
		COLORREF selectedColor = colorDlg.GetColor();
	}
}

// 画笔颜色
void CMFCDrawDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colorDlg;
	// 设置颜色对话框的初始颜色
	COLORREF initialColor = RGB(0, 0, 0); // 例如，初始颜色为红色
	colorDlg.m_cc.rgbResult = initialColor;
	colorDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;

	// 显示颜色对话框
	if (colorDlg.DoModal() == IDOK)
	{
		// 用户点击了确定按钮，获取选择的颜色
		COLORREF selectedColor = colorDlg.GetColor();
	}

}
