// ImgProcView.h : interface of the CImgProcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPROCVIEW_H__3C29DE44_E2E0_4F42_A354_41E2F69E49B6__INCLUDED_)
#define AFX_IMGPROCVIEW_H__3C29DE44_E2E0_4F42_A354_41E2F69E49B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImgProcView : public CView
{
protected: // create from serialization only
	CImgProcView();
	DECLARE_DYNCREATE(CImgProcView)

// Attributes
public:
	CImgProcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
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

	//添加成员函数
	void ShowBitmap(CDC* pDC,CString BmpName); //显示位图函数
	bool ReadBmp();                            //用来读取bmp个手机图片
	bool SaveBmp(LPCSTR lpFileName);           //用来保存bmp格式图片

	virtual ~CImgProcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImgProcView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnShowHd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImgProcView.cpp
inline CImgProcDoc* CImgProcView::GetDocument()
   { return (CImgProcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROCVIEW_H__3C29DE44_E2E0_4F42_A354_41E2F69E49B6__INCLUDED_)
