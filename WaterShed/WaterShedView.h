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
	INT sX, sY;//����λ�ã�
	INT iX, iY;//ͼ����ʾλ��, ���ĸ�������������ǰ���λ��ת��Ϊͼ��դ��λ�ã�
	INT cX, cY;//��ǰ�����ͼ���е�λ�ã�
	INT neiWidth, neiHeight;//�����ߣ�
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
