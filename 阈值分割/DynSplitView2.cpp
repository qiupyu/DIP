// DynSplitView2.cpp : implementation file
//

#include "stdafx.h"
#include "DSplit.h"
#include "DynSplitView2.h"
#include "DlgYuZhiFenGe.h"
#include "DlgZhiFangTu.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2

IMPLEMENT_DYNCREATE(CDynSplitView2, CView)

CDynSplitView2::CDynSplitView2()
{
	state2=0;
	state=0;
}

/*初始化图像数据*/
void CDynSplitView2::clearmem()
{
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc ->statedoc=0;
    state2=1;
	CDibNew1=&pDoc->CDibNew;
    CDib1=&pDoc->CDib;
    long int  size=CDib1->GetHeight()*CDib1->GetDibWidthBytes();
	memcpy(CDibNew1->m_pData,CDib1->m_pData,size);//复制原图像到处理区
}

CPalette * CDynSplitView2::CreateBitmapPalette(BingXingBianJieDib * pBitmap)
{
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} palette = { 0x300, 256 };
	
	LPRGBQUAD pRGBTable = pBitmap->GetRGB();
	UINT numberOfColors = pBitmap->GetNumberOfColors();
	
	for(UINT x=0; x<numberOfColors; ++x)
	{
		palette.aEntries[x].peRed =
			pRGBTable[x].rgbRed;
		palette.aEntries[x].peGreen =
			pRGBTable[x].rgbGreen;
		palette.aEntries[x].peBlue =
			pRGBTable[x].rgbBlue;
		palette.aEntries[x].peFlags = 0;
	}
	
	hPalette.CreatePalette((LPLOGPALETTE)&palette);
	//CPalette hPale=&hPalette;
	return &hPalette;
}

CDynSplitView2::~CDynSplitView2()
{
}

CDSplitDoc* CDynSplitView2::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSplitDoc)));
	return (CDSplitDoc*)m_pDocument;
}


BEGIN_MESSAGE_MAP(CDynSplitView2, CView)
	//{{AFX_MSG_MAP(CDynSplitView2)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILESAVE, OnFilesave)
	ON_COMMAND(ID_Yuzhifenge, OnYuzhifenge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 drawing

void CDynSplitView2::OnDraw(CDC* pDC)
{	
	CDSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc ->statedoc&&state2==1)
	{
        int m_scale=1;
		BYTE* pBitmapData = CDibNew1->GetData();
        LPBITMAPINFO pBitmapInfo = CDibNew1->GetInfo();
        int bitmapHeight = CDibNew1->GetHeight();
        int bitmapWidth = CDibNew1->GetWidth();
		int scaledWidth = (int)(bitmapWidth * m_scale);
		int scaledHeight = (int)(bitmapHeight * m_scale);
		if (CDibNew1->GetRGB()) // Has a color table
		{
			CPalette * hPalette=CreateBitmapPalette(CDibNew1);
            CPalette * hOldPalette =
                pDC->SelectPalette(hPalette, true);
            pDC->RealizePalette();
			::StretchDIBits(pDC->GetSafeHdc(),0, 0, bitmapWidth, bitmapHeight,
				0, 0, bitmapWidth, bitmapHeight,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
            pDC->SelectPalette(hOldPalette, true);
            ::DeleteObject(hPalette);
		}
		else
		{
            StretchDIBits(pDC->GetSafeHdc(),
                0, 0, scaledWidth, scaledHeight,
                0, 0, bitmapWidth, bitmapHeight,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 diagnostics

#ifdef _DEBUG
void CDynSplitView2::AssertValid() const
{
	CView::AssertValid();
}

void CDynSplitView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynSplitView2 message handlers

BOOL CDynSplitView2::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,::GetSysColor(COLOR_WINDOW));
	return TRUE;
}

void CDynSplitView2::OnFilesave() 
{
	CFileDialog dlg(FALSE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())
	CString  filename;
    filename.Format ("%s",dlg.GetPathName() );    
    CDibNew1->SaveFile(filename);
	state2=1;
	Invalidate();
}



/*阈值分割消息映射*/ 
void CDynSplitView2::OnYuzhifenge() 
{
	int i;
	int Yuzhi;   //阈值变量
	// 各颜色分量的灰度分布密度
    float midu[256];
	
	// 计算灰度分布密度	 	  
	clearmem();
	CDibNew1->Zhifangtu(midu);             //调用灰度统计处理函数
	
	// 创建灰度直方图对话框
	CDlgZhiFangTu*    dlg;
	dlg=new CDlgZhiFangTu(this);
	dlg->Create(IDD_DIALOG_ZhiFangTu);
	// 传递灰度分布密度数据给面板类
	for (i = 0; i <256; i++)
		dlg->m_fIntensity[i] = midu[i];
	
	// 显示对话框，由用户进行灰度折线变换
	dlg->ShowWindow(SW_RESTORE);
	
    //创建阈值选择对话框
	CDlgYuZhiFenGe  dlg1;
	dlg1.m_Yuzhi=0;
	
	// 显示对话框，提示用户输入阈值
	if (dlg1.DoModal() != IDOK)
	{
		// 返回
		return;
	}
    Yuzhi=dlg1.m_Yuzhi;
	
	// 删除对话框
	delete dlg1;
	delete dlg;
	
	clearmem();
	CDibNew1->Yuzhifenge(Yuzhi);             //调用阈值分割处理函数
	Invalidate();
}




