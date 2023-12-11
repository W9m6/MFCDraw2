
// MFCDrawDlg.h: 头文件
//

#pragma once


// CMFCDrawDlg 对话框
class CMFCDrawDlg : public CDialogEx
{
// 构造
public:
	CMFCDrawDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont myFont;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	// 自己实现的函数
	void UpdateStaticText();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton4();
	
protected:
	CStatic m_canvas;    // 画布
	int r = 300;		 // 圆半径
	int baseX = 450, baseY = 500;  // 圆的初始位置
	int n = 10;				 // 等分个数
	int pointx, pointy;  // 滑块距离
	CSliderCtrl Sliderx;
	CSliderCtrl Slidery;
	CSliderCtrl SliderR;
	CSliderCtrl SliderN;
	CPoint m_point;
	bool bDrawing;
	CArray<CPoint, CPoint&> m_points;  // 存储路径
	CComboBox m_cbLineWidth;    // 线条宽度
	COLORREF selectedPenColor;   // 选择的画笔颜色
	COLORREF selectedBrushColor;  // 选择的画刷颜色

};
