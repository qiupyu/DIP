// ImgProc.h : main header file for the IMGPROC application
//

#if !defined(AFX_IMGPROC_H__036984A8_6ACF_4814_8C5C_91872AE00A1D__INCLUDED_)
#define AFX_IMGPROC_H__036984A8_6ACF_4814_8C5C_91872AE00A1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImgProcApp:
// See ImgProc.cpp for the implementation of this class
//

class CImgProcApp : public CWinApp
{
public:
	CImgProcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImgProcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROC_H__036984A8_6ACF_4814_8C5C_91872AE00A1D__INCLUDED_)
