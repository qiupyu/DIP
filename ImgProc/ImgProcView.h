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
	//��ӳ�Ա����
	CBitmap m_bitmap;      //����λͼ����
	CString BmpName;       //ͼ���ļ�����
	CString EntName;       //ͼ���ļ���չ��

	CString BmpNameLin;    //����ͼ�񸱱��ļ�
	CBitmap m_bitmaplin;   //������ʱλͼ������д���

	int	m_nWidth;          //ͼ��ʵ�ʿ��
	int	m_nHeight;         //ͼ��ʵ�ʸ߶�
	int	m_nDrawWidth;      //ͼ����ʾ���
	int	m_nDrawHeight;     //ͼ����ʾ�߶�
	DWORD m_nImage;        //ͼ�����ݵ��ֽ��� ֻ��λͼ
	DWORD m_nSize;         //ͼ���ļ���С
	int m_nLineByte;       //ͼ��һ����ռ�ֽ���
	int	m_nBitCount;       //ͼ��ÿ��������ռλ��
	int	m_nPalette;        //λͼʵ��ʹ�õ���ɫ���е���ɫ��
	
	BYTE *m_pImage;        //����ͼƬ���ݺ��ָ��
	BITMAPFILEHEADER bfh;  //ȫ�ֱ����ļ�ͷ
	BITMAPINFOHEADER bih;  //ȫ�ֱ�����Ϣͷ
	RGBQUAD m_pPal;        //��ɫ��ָ��

	//��ӳ�Ա����
	void ShowBitmap(CDC* pDC,CString BmpName); //��ʾλͼ����
	bool ReadBmp();                            //������ȡbmp���ֻ�ͼƬ
	bool SaveBmp(LPCSTR lpFileName);           //��������bmp��ʽͼƬ

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
