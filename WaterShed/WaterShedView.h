// WaterShedView.h : interface of the CWaterShedView class

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATERSHEDVIEW_H__26511C8F_CCD4_4B5F_8B6E_468807A22287__INCLUDED_)
#define AFX_WATERSHEDVIEW_H__26511C8F_CCD4_4B5F_8B6E_468807A22287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WaterShedDoc.h"

class CWaterShedView : public CScrollView
{
protected: // create from serialization only
	CWaterShedView();
	DECLARE_DYNCREATE(CWaterShedView)

// Attributes
public:
	CWaterShedDoc* GetDocument();

// Operations
public:
	INT sX, sY;//卷屏位置；
	INT iX, iY;//图像显示位置, 这四个变量用来将当前光标位置转换为图像栅格位置；
	INT cX, cY;//当前光标在图像中的位置；
	INT neiWidth, neiHeight;//邻域宽高；
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaterShedView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//添加成员变量
	CBitmap m_bitmap;      //创建位图对象
	CString BmpName;       //图像文件名称
	CString EntName;       //图像文件扩展名

	CString BmpNameLin;    //保存图像副本文件
	CBitmap m_bitmaplin;   //创建临时位图对象进行处理

	int	m_nWidth;          //图像实际宽度
	int	m_nHeight;         //图像实际高度
	int	m_nDrawWidth;      //图像显示宽度
	int	m_nDrawHeight;     //图像显示高度
	DWORD m_nImage;        //图像数据的字节数 只含位图
	DWORD m_nSize;         //图像文件大小
	int m_nLineByte;       //图像一行所占字节数
	int	m_nBitCount;       //图像每个像素所占位数
	int	m_nPalette;        //位图实际使用的颜色表中的颜色数
	
	BYTE *m_pImage;        //读入图片数据后的指针
	BITMAPFILEHEADER bfh;  //全局变量文件头
	BITMAPINFOHEADER bih;  //全局变量信息头
	RGBQUAD m_pPal;        //颜色表指针

	bool ReadBmp();
	void ShowBitmap(CDC *pDC, CString BmpName);

	virtual ~CWaterShedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaterShedView)
	afx_msg void OnShowHd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WaterShedView.cpp
inline CWaterShedDoc* CWaterShedView::GetDocument()
   { return (CWaterShedDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERSHEDVIEW_H__26511C8F_CCD4_4B5F_8B6E_468807A22287__INCLUDED_)
