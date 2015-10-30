// ImgProcDoc.h : interface of the CImgProcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPROCDOC_H__6ED4BF44_3FA0_4892_AD97_34AB4E15C9B5__INCLUDED_)
#define AFX_IMGPROCDOC_H__6ED4BF44_3FA0_4892_AD97_34AB4E15C9B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImgProcDoc : public CDocument
{
protected: // create from serialization only
	CImgProcDoc();
	DECLARE_DYNCREATE(CImgProcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgProcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImgProcDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROCDOC_H__6ED4BF44_3FA0_4892_AD97_34AB4E15C9B5__INCLUDED_)
