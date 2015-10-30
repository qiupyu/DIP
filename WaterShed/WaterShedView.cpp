// WaterShedView.cpp : implementation of the CWaterShedView class


#include "stdafx.h"
#include "WaterShed.h"

#include "WaterShedDoc.h"
#include "WaterShedView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView

IMPLEMENT_DYNCREATE(CWaterShedView, CScrollView)

BEGIN_MESSAGE_MAP(CWaterShedView, CScrollView)
	//{{AFX_MSG_MAP(CWaterShedView)
	ON_COMMAND(IDR_MENU_HD, OnShowHd)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView construction/destruction

/* numPicture变量显示图片数量
   0-提示错误或未打开图片 1-显示一张图片 2-显示两张图片和处理
 */
int numPicture = 0;

/*
   level变量显示具体的处理操作，每个处理函数中赋值该变量
   0-显示2张图片 1-显示灰度图片 3-显示图片采样
   2 4 8 16 32 64-不同量化等级量化图片
 */ 
int level = 0;  

CWaterShedView::CWaterShedView()
{
	// TODO: add construction code here

}

CWaterShedView::~CWaterShedView()
{
}

BOOL CWaterShedView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView drawing

void CWaterShedView::OnDraw(CDC* pDC)
{
// 	CWaterShedDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CMainFrame *pFrame;
	pFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();             
	pFrame->pImageView = this;
	
	CWaterShedDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	

	//刷新背景；
	CBrush bkBrush( RGB(58,110,165) );
	CRect clientRect ;
	GetClientRect(&clientRect);
	int w = 0;
	int h = 0;
	if( pDoc->myImageObject!=NULL)
	{
		w = pDoc->myImageObject->GetWidth();
        h = pDoc->myImageObject->GetHeight();
	}
	w = w > clientRect.Width()  ? w : clientRect.Width();
	h = h > clientRect.Height() ? h : clientRect.Height();
	clientRect.right = w;
	clientRect.bottom = h;
	pDC->FillRect( &clientRect, &bkBrush );
	
	if( !pDoc->isImageLoaded )
	{
		return;
	}
	
	CSize sizet;
   	sizet.cx = pDoc->myImageObject->GetWidth();
	sizet.cy = pDoc->myImageObject->GetHeight();
	SetScrollSizes (MM_TEXT, sizet);
	
	//OnPrepareDC (pDC);
	CRect rect;
	GetClientRect(&rect);
	int width, height;
	width = pDoc->myImageObject->GetWidth();
	height = pDoc->myImageObject->GetHeight();
	
	if(width<rect.Width())
	{
		iX = 0;//(rect.Width()-width) / 2;
	}else
	{
		iX = 0;
	}		
	if(height<rect.Height())
	{
		iY = 0;//(rect.Height()-height) / 2;
	}else
	{
		iY = 0;
	}	
	
	if(GetFocus()==this)
	{
		pDoc->myImageObject->SetPalette( pDC );
	}	    
	pDoc->myImageObject->Draw(pDC, iX, iY);

	EntName = pDoc->imageName;
	
	EntName.MakeLower(); 
	if( strstr(EntName, ".bmp") != 0 )
	{
		ReadBmp();
		if ((level == 1) && (pDoc->iHdDisplayflag))
		{
		    ShowBitmap(pDC, pDoc->ImgPathName);
		}		
	}

}

void CWaterShedView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView printing

BOOL CWaterShedView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWaterShedView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWaterShedView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView diagnostics

#ifdef _DEBUG
void CWaterShedView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWaterShedView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWaterShedDoc* CWaterShedView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaterShedDoc)));
	return (CWaterShedDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaterShedView message handlers

  

//显示BMP格式图片//
void CWaterShedView::ShowBitmap(CDC *pDC, CString BmpName)
{	
	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		
	/*
	/* 1.要装载OEM图像，则设此参数值为0  OBM_ OEM位图 OIC_OEM图标 OCR_OEM光标
	/* 2.BmpName要装载图片的文件名                  
	/* 3.装载图像类型: 
	/*   IMAGE_BITMAP-装载位图 IMAGE_CURSOR-装载光标 IMAGE_ICON-装载图标    
	/* 4.指定图标或光标的像素宽度和长度 以像素为单位    
	/* 5.加载选项:
	/*   IR_LOADFROMFILE-指明由lpszName指定文件中加载图像
	/*   IR_DEFAULTSIZE-指明使用图像默认大小
	/*   LR_CREATEDIBSECTION-当uType参数为IMAGE_BITMAP时,创建一个DIB项
	*/

	if( m_bitmap.m_hObject )
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联
	
	//边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX=0;
	int m_showY=0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度
		
	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC
		return;
	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
	CBitmap *pbmpOld = NULL;      
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境
	
	//图片显示调用函数stretchBlt
	/*
	   BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC, 
	                   int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop );
	   1.参数x、y位图目标矩形x、y的坐标值      
	   2.nWidth、nHeigth位图目标矩形的逻辑宽度和高度      
	   3.pSrcDC表示源设备CDC指针                          
	   4.xSrc、ySrc表示位图源矩形的的x、y逻辑坐标值 
	   5.dwRop表示显示位图的光栅操作方式 SRCCOPY用于直接将位图到目标环境中            
	
	pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,
		m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);*/
	
	
	
	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
	DeleteObject(&m_bitmap);               //删除内存中的位图
	dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC


	/* 
	  下面代码为后面显示第二张图片
	*/
	
	if(numPicture==2) 
	{
		//显示图片函数LoadImage
		HBITMAP m_hBitmapChange;
		

		if(level==0) //显示2张图 BmpNameLin原图
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else if(level==1) //灰度图片 BmpNameLin临时图片
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		if( m_bitmap.m_hObject ) {
			m_bitmap.Detach();            //m_bitmap为创建的位图对象
		}
		m_bitmap.Attach(m_hBitmapChange);
		//定义并创建一个内存设备环境
		CDC dcBmp;
		if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC
			return;
		BITMAP m_bmp;                          //临时bmp图片变量
		m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

		//如果图片太大显示大小为固定640*640 否则显示原图大小
		if(m_nDrawWidth<650 && m_nDrawHeight<650)
			pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,
				m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
		else
			pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
				m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY); 
		//恢复临时DC的位图
		dcBmp.SelectObject(pbmpOld);           
	}

}


//*读取图片数据*//
bool CWaterShedView::ReadBmp()
{
	CWaterShedDoc* pDoc = GetDocument();

	//图片读出存储其中的东西
    BmpName = pDoc->ImgPathName;
	FILE *fp = fopen(BmpName,"rb");
	if(fp==0)
	{		
		AfxMessageBox("无法打开文件!",MB_OK,0);
		return 0; 
	}
	//读取文件头 解决BMP格式倒置的方法
	fread(&bfh.bfType,sizeof(WORD),1,fp);
	fread(&bfh.bfSize,sizeof(DWORD),1,fp);
	fread(&bfh.bfReserved1,sizeof(WORD),1,fp);
	fread(&bfh.bfReserved2,sizeof(WORD),1,fp);
	fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);
	//图像文件的总字节数
	m_nSize = bfh.bfSize;
	//判断是否是bmp格式图片
	if(bfh.bfType!=0x4d42)   //'BM'
	{
		AfxMessageBox("不是BMP格式图片!",MB_OK,0);
		return 0;
	}
	//读取信息头
	fread(&bih.biSize,sizeof(DWORD),1,fp);
	fread(&bih.biWidth,sizeof(LONG),1,fp);
	fread(&bih.biHeight,sizeof(LONG),1,fp);
	fread(&bih.biPlanes,sizeof(WORD),1,fp);
	fread(&bih.biBitCount,sizeof(WORD),1,fp);
	fread(&bih.biCompression,sizeof(DWORD),1,fp);
	fread(&bih.biSizeImage,sizeof(DWORD),1,fp);
	fread(&bih.biXPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biYPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biClrUsed,sizeof(DWORD),1,fp);
	fread(&bih.biClrImportant,sizeof(DWORD),1,fp);
	if(bih.biSize!=sizeof(bih))
	{
		AfxMessageBox("本结构所占用字节数出现错误");
		return 0;
	}
	//位图压缩类型，必须是 0（不压缩） 1（BI_RLE8压缩类型）或2（BI_RLE压缩类型）之一
	if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("位图被压缩!");
		return 0;
	}
	//获取图像高宽和每个像素所占位数
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //每个像素所占位数
	//计算图像每行像素所占的字节数（必须是32的倍数）
	m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;
	//图片大小 调用系统自带的文件头 BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//否则用 BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;要 m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//位图实际使用的颜色表中的颜色数 biClrUsed
	m_nPalette = 0;                       //初始化
	if(bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//申请位图空间 大小为位图大小 m_nImage
	//malloc只能申请4字节的空间 （未知）
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fp);
	fclose(fp);
	return true;
}

void CWaterShedView::OnShowHd() 
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here

	CWaterShedDoc* pDoc = GetDocument();

	numPicture = pDoc->isImageLoaded;
	pDoc->iHdDisplayflag++;

	//图片读出存储其中的东西
    BmpName = pDoc->ImgPathName;
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能灰度图片!",MB_OK,0);
		return;
	}
	AfxMessageBox("灰度图像!",MB_OK,0);
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	BmpNameLin = BmpName+"_hd.bmp"; 

	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;

	//
	/* 注意：原来下面所有操作都是for( i=0; i<m_nWidth*m_nHeight; i++ )  
	   后发现如果图片最后一行没有完整的一行数据，会出现图像变多或变少   
	   但图像的总像素为m_nImage，如果是m_nImage/3就可以保证所有像素都有 
	*/

	for(int i=0; i < m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		color=(red+green+blue)/3;
		red=color;
		green=color;  
		blue=color;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=1;
	Invalidate();
}

