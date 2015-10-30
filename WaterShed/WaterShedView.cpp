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

/* numPicture������ʾͼƬ����
   0-��ʾ�����δ��ͼƬ 1-��ʾһ��ͼƬ 2-��ʾ����ͼƬ�ʹ���
 */
int numPicture = 0;

/*
   level������ʾ����Ĵ��������ÿ���������и�ֵ�ñ���
   0-��ʾ2��ͼƬ 1-��ʾ�Ҷ�ͼƬ 3-��ʾͼƬ����
   2 4 8 16 32 64-��ͬ�����ȼ�����ͼƬ
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
	

	//ˢ�±�����
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

  

//��ʾBMP��ʽͼƬ//
void CWaterShedView::ShowBitmap(CDC *pDC, CString BmpName)
{	
	//����bitmapָ�� ���ú���LoadImageװ��λͼ
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		
	/*
	/* 1.Ҫװ��OEMͼ������˲���ֵΪ0  OBM_ OEMλͼ OIC_OEMͼ�� OCR_OEM���
	/* 2.BmpNameҪװ��ͼƬ���ļ���                  
	/* 3.װ��ͼ������: 
	/*   IMAGE_BITMAP-װ��λͼ IMAGE_CURSOR-װ�ع�� IMAGE_ICON-װ��ͼ��    
	/* 4.ָ��ͼ���������ؿ�Ⱥͳ��� ������Ϊ��λ    
	/* 5.����ѡ��:
	/*   IR_LOADFROMFILE-ָ����lpszNameָ���ļ��м���ͼ��
	/*   IR_DEFAULTSIZE-ָ��ʹ��ͼ��Ĭ�ϴ�С
	/*   LR_CREATEDIBSECTION-��uType����ΪIMAGE_BITMAPʱ,����һ��DIB��
	*/

	if( m_bitmap.m_hObject )
	{
		m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ
	}
	m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����
	
	//�߽�
	CRect rect;
	GetClientRect(&rect);

	//ͼƬ��ʾ(x,y)��ʼ����
	int m_showX=0;
	int m_showY=0;
	int m_nWindowWidth = rect.right - rect.left;   //����ͻ������
	int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�
		
	//���岢����һ���ڴ��豸����DC
	CDC dcBmp;
	if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC
		return;
	BITMAP m_bmp;                          //��ʱbmpͼƬ����
	m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��
	CBitmap *pbmpOld = NULL;      
	dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����
	
	//ͼƬ��ʾ���ú���stretchBlt
	/*
	   BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC, 
	                   int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop );
	   1.����x��yλͼĿ�����x��y������ֵ      
	   2.nWidth��nHeigthλͼĿ����ε��߼���Ⱥ͸߶�      
	   3.pSrcDC��ʾԴ�豸CDCָ��                          
	   4.xSrc��ySrc��ʾλͼԴ���εĵ�x��y�߼�����ֵ 
	   5.dwRop��ʾ��ʾλͼ�Ĺ�դ������ʽ SRCCOPY����ֱ�ӽ�λͼ��Ŀ�껷����            
	
	pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,
		m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);*/
	
	
	
	dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ
	DeleteObject(&m_bitmap);               //ɾ���ڴ��е�λͼ
	dcBmp.DeleteDC();                      //ɾ��CreateCompatibleDC�õ���ͼƬDC


	/* 
	  �������Ϊ������ʾ�ڶ���ͼƬ
	*/
	
	if(numPicture==2) 
	{
		//��ʾͼƬ����LoadImage
		HBITMAP m_hBitmapChange;
		

		if(level==0) //��ʾ2��ͼ BmpNameLinԭͼ
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else if(level==1) //�Ҷ�ͼƬ BmpNameLin��ʱͼƬ
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		if( m_bitmap.m_hObject ) {
			m_bitmap.Detach();            //m_bitmapΪ������λͼ����
		}
		m_bitmap.Attach(m_hBitmapChange);
		//���岢����һ���ڴ��豸����
		CDC dcBmp;
		if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC
			return;
		BITMAP m_bmp;                          //��ʱbmpͼƬ����
		m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

		//���ͼƬ̫����ʾ��СΪ�̶�640*640 ������ʾԭͼ��С
		if(m_nDrawWidth<650 && m_nDrawHeight<650)
			pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,
				m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
		else
			pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
				m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY); 
		//�ָ���ʱDC��λͼ
		dcBmp.SelectObject(pbmpOld);           
	}

}


//*��ȡͼƬ����*//
bool CWaterShedView::ReadBmp()
{
	CWaterShedDoc* pDoc = GetDocument();

	//ͼƬ�����洢���еĶ���
    BmpName = pDoc->ImgPathName;
	FILE *fp = fopen(BmpName,"rb");
	if(fp==0)
	{		
		AfxMessageBox("�޷����ļ�!",MB_OK,0);
		return 0; 
	}
	//��ȡ�ļ�ͷ ���BMP��ʽ���õķ���
	fread(&bfh.bfType,sizeof(WORD),1,fp);
	fread(&bfh.bfSize,sizeof(DWORD),1,fp);
	fread(&bfh.bfReserved1,sizeof(WORD),1,fp);
	fread(&bfh.bfReserved2,sizeof(WORD),1,fp);
	fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);
	//ͼ���ļ������ֽ���
	m_nSize = bfh.bfSize;
	//�ж��Ƿ���bmp��ʽͼƬ
	if(bfh.bfType!=0x4d42)   //'BM'
	{
		AfxMessageBox("����BMP��ʽͼƬ!",MB_OK,0);
		return 0;
	}
	//��ȡ��Ϣͷ
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
		AfxMessageBox("���ṹ��ռ���ֽ������ִ���");
		return 0;
	}
	//λͼѹ�����ͣ������� 0����ѹ���� 1��BI_RLE8ѹ�����ͣ���2��BI_RLEѹ�����ͣ�֮һ
	if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("λͼ��ѹ��!");
		return 0;
	}
	//��ȡͼ��߿��ÿ��������ռλ��
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //ÿ��������ռλ��
	//����ͼ��ÿ��������ռ���ֽ�����������32�ı�����
	m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;
	//ͼƬ��С ����ϵͳ�Դ����ļ�ͷ BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//������ BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;Ҫ m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//λͼʵ��ʹ�õ���ɫ���е���ɫ�� biClrUsed
	m_nPalette = 0;                       //��ʼ��
	if(bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//����λͼ�ռ� ��СΪλͼ��С m_nImage
	//mallocֻ������4�ֽڵĿռ� ��δ֪��
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

	//ͼƬ�����洢���еĶ���
    BmpName = pDoc->ImgPathName;
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ����ܻҶ�ͼƬ!",MB_OK,0);
		return;
	}
	AfxMessageBox("�Ҷ�ͼ��!",MB_OK,0);
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	BmpNameLin = BmpName+"_hd.bmp"; 

	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;

	//
	/* ע�⣺ԭ���������в�������for( i=0; i<m_nWidth*m_nHeight; i++ )  
	   �������ͼƬ���һ��û��������һ�����ݣ������ͼ��������   
	   ��ͼ���������Ϊm_nImage�������m_nImage/3�Ϳ��Ա�֤�������ض��� 
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

