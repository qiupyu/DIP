#include "stdafx.h"
#include "windowsx.h"
#include "math.h"
#include "BingXingBianJieDib.h"
#include "MainFrm.h"
#include "DynSplitView2.h"
 
BingXingBianJieDib::BingXingBianJieDib()
{
}
BingXingBianJieDib::~BingXingBianJieDib()
{
}



///***************************************************************/           
/*函数名称：Fenbutongji(int *tongji)                                      
/*函数类型：void
/*参数说明：tonji     ---直方图灰度值统计                                      
/*功能：对图像进行灰度值统计。            
/***************************************************************/ 
void BingXingBianJieDib::Fenbutongji(int *tongji)
{
	// 循环变量
	LONG i;
	LONG j;
	//变量初始化
	memset(tongji,0,sizeof(int) * 256);
	// 指向DIB象素指针
	LPBYTE p_data;
	// 找到DIB图像象素起始位置
	p_data = this->GetData();
	// DIB的宽度
	LONG wide = GetDibWidthBytes();
	// DIB的高度
	LONG height = GetHeight();
	// 对各像素进行灰度转换
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i++)
		{
			// 对各像素进行灰度统计
			unsigned char temp = *((unsigned char *)p_data + wide * j + i);
			tongji[temp]++; 
		}
	}
}

///***************************************************************/           
/*函数名称：Yuzhifenge(int Yuzhi)                                      
/*函数类型：void
/*参数说明：Yuzhi  ---阈值选取                                     
/*功能：对图像进行阈值分割。            
/***************************************************************/
void BingXingBianJieDib::Yuzhifenge(int Yuzhi)
{
	// 指向源图像的指针
	LPBYTE  p_data;
	LPBYTE	lpSrc;
	// 指向缓存图像的指针
	LPBYTE	lpDst;
	// 指向缓存DIB图像的指针
	LPBYTE	temp;
	//循环变量
	long i;
	long j;
	//图像的高和宽
	long wide;
	long height;
	p_data=GetData();
	if(m_pBitmapInfoHeader->biBitCount<9)	//灰度图像
		wide=GetWidth();
	else	//24位彩色
		wide=GetDibWidthBytes();
	height=GetHeight();
	temp=new BYTE[wide*height];
	memset(temp,255,wide*height);
	for (j=0;j<height;j++)
	{
		for(i=0;i<wide;i++)
		{
			lpSrc=p_data+wide*j+i;
			lpDst=temp+wide*j+i;
			if(abs(*lpSrc-Yuzhi)<30)
				*lpDst=Yuzhi;			
		}
	}
    memcpy(p_data,temp,wide*height);
	delete temp;	
}


 
///***************************************************************/           
/*函数名称：Zhifangtu(float *fPs_Y)                              */
/*函数类型：void                                                 */
/*变量说明：tongji  灰度分布密度统计                             */                           
/*功能：对图像进行灰度直方图统计。								 */
/*****************************************************************/
void BingXingBianJieDib::Zhifangtu(float *tongji)
{
	// 循环变量
	int i;
	int j;
	// 灰度计数
	int huidu[256];
	int wide,height;    //原图长、宽
	// 变量初始化
	memset(huidu,0,sizeof(huidu));
	if(m_pBitmapInfoHeader->biBitCount<9)	//灰度图像
	{
        wide=this->GetWidth ();
        height=this->GetHeight ();
		int width= (((wide*24) + 31) / 32 * 4) ;
		LPBYTE temp1=new BYTE[wide*height+1024];    //新图像缓冲区
		//拷贝原图像到缓存图像
		memcpy( temp1,m_pData,wide*height );
		// 对各像素进行灰度统计
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j <wide; j ++)
			{
				unsigned char  temp =  temp1[wide* i + j] ;			  			 
				// 灰度统计计数
				huidu[temp]++;		
			}
		}
		// 计算灰度分布密度
		for(i=0;i<256;i++)
			tongji[i] = huidu[i] / (height * wide *1.0f);
	}
	else	//24位彩色
	{
       	wide=this->GetDibWidthBytes();
        height=this->GetHeight ();
		LPBYTE  temp1=new BYTE[wide*height];    //新图像缓冲区
		//拷贝原图像到缓存图像
		memcpy(temp1,m_pData,wide*height );
		// 对各像素进行灰度统计
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j <wide; j ++)
			{
				unsigned char  temp = temp1[wide* i + j] ;
				// 灰度统计计数
				huidu[temp]++;		
			}
		} 
		// 计算灰度分布密度
		for(i=0;i<256;i++)
			tongji[i] = huidu[i] / (height * wide *1.0f);
	} 
}


