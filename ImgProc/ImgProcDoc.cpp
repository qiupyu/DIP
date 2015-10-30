// ImgProcDoc.cpp : implementation of the CImgProcDoc class
//

#include "stdafx.h"
#include "ImgProc.h"

#include "ImgProcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc

IMPLEMENT_DYNCREATE(CImgProcDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgProcDoc, CDocument)
	//{{AFX_MSG_MAP(CImgProcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc construction/destruction

CImgProcDoc::CImgProcDoc()
{
	// TODO: add one-time construction code here

}

CImgProcDoc::~CImgProcDoc()
{
}

BOOL CImgProcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc serialization

void CImgProcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc diagnostics

#ifdef _DEBUG
void CImgProcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgProcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc commands
