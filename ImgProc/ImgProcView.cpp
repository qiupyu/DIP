// ImgProcView.cpp : implementation of the CImgProcView class
//

#include "stdafx.h"
#include "ImgProc.h"

#include "ImgProcDoc.h"
#include "ImgProcView.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 

/////////////////////////////////////////////////////////////////////////////
// CImgProcView

IMPLEMENT_DYNCREATE(CImgProcView, CView)

BEGIN_MESSAGE_MAP(CImgProcView, CView)
	//{{AFX_MSG_MAP(CImgProcView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_SHOW_HD, OnShowHd)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_SHOW_DBD, &CImgProcView::OnShowDbd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProcView construction/destruction

CImgProcView::CImgProcView()
{
	// TODO: add construction code here

}

CImgProcView::~CImgProcView()
{
}

BOOL CImgProcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImgProcView drawing

void CImgProcView::OnDraw(CDC* pDC)
{
	CImgProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (!pDoc) return;  
    if( EntName.Compare(_T("bmp")) == 0 )      //bmp格式  
    {
		ReadBmp();                             // 读取bmp文件信息
        ShowBitmap(pDC,BmpName);               //显示图片  
    }  
}

/////////////////////////////////////////////////////////////////////////////
// CImgProcView printing

BOOL CImgProcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgProcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgProcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImgProcView diagnostics

#ifdef _DEBUG
void CImgProcView::AssertValid() const
{
	CView::AssertValid();
}

void CImgProcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgProcDoc* CImgProcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgProcDoc)));
	return (CImgProcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgProcView message handlers


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

//显示BMP格式图片//
void CImgProcView::ShowBitmap(CDC *pDC, CString BmpName)
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
	*/
	pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,
		m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
	
	
	
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
		else
		if(level==1) //灰度图片 BmpNameLin临时图片
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

void CImgProcView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	//两种格式的文件：bmp gif
    CString filter;  
    filter="所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);            
  
    //按下确定按钮 dlg.DoModal() 函数显示对话框  
    if( dlg.DoModal() == IDOK )  
    {  
        BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp  
		BmpNameLin = BmpName+"_hd.bmp";  //临时变量名
		numPicture=1;                    //显示一张图片
        EntName = dlg.GetFileExt();      //获取文件扩展名  
        EntName.MakeLower();             //将文件扩展名转换为一个小写字符  
        Invalidate();                    //调用该函数就会调用OnDraw重绘画图  
    }  	
}


//*读取图片数据*//
bool CImgProcView::ReadBmp()
{
	//图片读出存储其中的东西
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


//保存文件//
bool CImgProcView::SaveBmp(LPCSTR lpFileName) //lpFileName为位图文件名
{
	//保存bmp格式图片 写图片过程 只处理24像素的图片 该图片无调色板
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(lpFileName,"wb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//malloc只能申请4字节的空间 （未知）
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	fwrite(m_pImage,m_nImage,1,fpw);
	free(m_pImage);
	fclose(fpo);
	fclose(fpw);
	return true;
}


//文件保存
void CImgProcView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CString filter;
	filter="所有文件(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	//重点: 1-文件打开 0-文件保存
	CFileDialog dlg(0,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);   
	//按下确定按钮
	if( dlg.DoModal() == IDOK ) {
		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //获取文件的路径
		filename = dlg.GetFileTitle();     //获取文件名
		int nFilterIndex=dlg.m_ofn.nFilterIndex;
		if( nFilterIndex == 2 )            //当用户选择文件过滤器为".BMP"时
		{
			str = str + ".bmp";	           //自动加扩展名.bmp
			SaveBmp(str);                  //保存bmp图片 就是一个写出图片的过程 
			AfxMessageBox("图片保存成功",MB_OK,0);
		}
	}
}




//
/*                  
   其中24位的图片灰度时,采用如下算法:                                                       
   1.平均值算法 R=G=B=(R+G+B)/3                                                              
   2.快速算法 R=G=B=(R+G+B+128)/4>>2                                                          
   3.加权平均值算法 根据光的亮度特性,其实正确的灰度公式应当是R=G=B=R*0.299+G*0.587+B0.144   
     为了提高速度我们做一个完全可以接受的近似，公式变形如下 R=G=B=(R*3+G*6+B)/10            
   4.精确加权平均值算法 R=G=B=R*0.299+G*0.587+B0.144                                        
*/

//灰度图像就是 R=G=B且为三者的1/3 level=1时灰度图像//
void CImgProcView::OnShowHd() 
{
	// TODO: Add your command handler code here
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能灰度图片!",MB_OK,0);
		return;
	}
	AfxMessageBox("灰度图像!",MB_OK,0);
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
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


unsigned char CImgProcView::mysaturate(int iNum)
{
	unsigned char ucTmpNum = 0;
	if (iNum >= 255)
	{
		ucTmpNum = 255;
	}
	else if (iNum < 0)
	{
		ucTmpNum = 0;
	}
	else
	{
		ucTmpNum = (unsigned char)iNum;
	}

	return ucTmpNum;
}

// 对比度alpha的最佳取值范围在[0 ~ 4]
// 亮度beta的最佳取值范围在[0~3]之间
/*
算法原理：g(x) = f(x)*alpha + 亮度均值*(beta-alpha)
  对比度算法过程：
  1.计算图像的RGB像素均值；
  2.对图像的每个像素点与均值求差值；
  3.对去掉平均值以后的像素点的RGB值，乘以对比度系数
  4.对上一步像素RGB值，加上均值乘以亮度系数的积
  5.从而得到像素点新的RGB值
*/
double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */
void CImgProcView::OnShowDbd()
{
	// TODO: 在此添加命令处理程序代码

	int sum_r = 0,sum_g = 0,sum_b = 0;
	double averg_r = 0,averg_g = 0,averg_b = 0;

	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能灰度图片!",MB_OK,0);
		return;
	}
	AfxMessageBox("对比度图像!",MB_OK,0);

    // 对比度alpha的最佳取值范围在[0 ~ 4]
    // 亮度beta的最佳取值范围在[0~3]之间
	alpha = 2.7;
	beta = 2;


	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	int color;
	unsigned char red,green,blue;
	int int_red,int_green,int_blue;
	double new_light;

	//
	/* 注意：原来下面所有操作都是for( i=0; i<m_nWidth*m_nHeight; i++ )  
	   后发现如果图片最后一行没有完整的一行数据，会出现图像变多或变少   
	   但图像的总像素为m_nImage，如果是m_nImage/3就可以保证所有像素都有 
	*/
	// 先要算出所有像素点的平均值
	for(int i=0; i < m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);
		
			
		sum_r += red;
		sum_g += green;
		sum_b += blue;
	}
	averg_r = sum_r/(m_nImage/3);
	averg_g = sum_g/(m_nImage/3);
	averg_b = sum_b/(m_nImage/3);

	// 回到图像文件的RGB值的起点
	fseek(fpo,sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),0);

	for(int i=0; i < m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);
		
		int_red = (int)(red - averg_r);
		int_green = (int)(green - averg_g);
		int_blue = (int)(blue - averg_b);

		// 乘以对比度系数
		int_red = (int)int_red * alpha;
		int_green =(int)int_green * alpha;
		int_blue = (int)int_blue * alpha;

		// 调整亮度
		int_red += (int)averg_r * beta;
		int_green += (int)averg_g * beta;
		int_blue += (int)averg_b * beta;

		// 饱和处理
		red = mysaturate(int_red);
		green = mysaturate(int_green);
		blue = mysaturate(int_blue);		

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
