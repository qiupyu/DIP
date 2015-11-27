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
/*�������ƣ�Fenbutongji(int *tongji)                                      
/*�������ͣ�void
/*����˵����tonji     ---ֱ��ͼ�Ҷ�ֵͳ��                                      
/*���ܣ���ͼ����лҶ�ֵͳ�ơ�            
/***************************************************************/ 
void BingXingBianJieDib::Fenbutongji(int *tongji)
{
	// ѭ������
	LONG i;
	LONG j;
	//������ʼ��
	memset(tongji,0,sizeof(int) * 256);
	// ָ��DIB����ָ��
	LPBYTE p_data;
	// �ҵ�DIBͼ��������ʼλ��
	p_data = this->GetData();
	// DIB�Ŀ��
	LONG wide = GetDibWidthBytes();
	// DIB�ĸ߶�
	LONG height = GetHeight();
	// �Ը����ؽ��лҶ�ת��
	for (j = 0; j < height; j ++)
	{
		for (i = 0; i <wide; i++)
		{
			// �Ը����ؽ��лҶ�ͳ��
			unsigned char temp = *((unsigned char *)p_data + wide * j + i);
			tongji[temp]++; 
		}
	}
}

///***************************************************************/           
/*�������ƣ�Yuzhifenge(int Yuzhi)                                      
/*�������ͣ�void
/*����˵����Yuzhi  ---��ֵѡȡ                                     
/*���ܣ���ͼ�������ֵ�ָ            
/***************************************************************/
void BingXingBianJieDib::Yuzhifenge(int Yuzhi)
{
	// ָ��Դͼ���ָ��
	LPBYTE  p_data;
	LPBYTE	lpSrc;
	// ָ�򻺴�ͼ���ָ��
	LPBYTE	lpDst;
	// ָ�򻺴�DIBͼ���ָ��
	LPBYTE	temp;
	//ѭ������
	long i;
	long j;
	//ͼ��ĸߺͿ�
	long wide;
	long height;
	p_data=GetData();
	if(m_pBitmapInfoHeader->biBitCount<9)	//�Ҷ�ͼ��
		wide=GetWidth();
	else	//24λ��ɫ
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
/*�������ƣ�Zhifangtu(float *fPs_Y)                              */
/*�������ͣ�void                                                 */
/*����˵����tongji  �Ҷȷֲ��ܶ�ͳ��                             */                           
/*���ܣ���ͼ����лҶ�ֱ��ͼͳ�ơ�								 */
/*****************************************************************/
void BingXingBianJieDib::Zhifangtu(float *tongji)
{
	// ѭ������
	int i;
	int j;
	// �Ҷȼ���
	int huidu[256];
	int wide,height;    //ԭͼ������
	// ������ʼ��
	memset(huidu,0,sizeof(huidu));
	if(m_pBitmapInfoHeader->biBitCount<9)	//�Ҷ�ͼ��
	{
        wide=this->GetWidth ();
        height=this->GetHeight ();
		int width= (((wide*24) + 31) / 32 * 4) ;
		LPBYTE temp1=new BYTE[wide*height+1024];    //��ͼ�񻺳���
		//����ԭͼ�񵽻���ͼ��
		memcpy( temp1,m_pData,wide*height );
		// �Ը����ؽ��лҶ�ͳ��
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j <wide; j ++)
			{
				unsigned char  temp =  temp1[wide* i + j] ;			  			 
				// �Ҷ�ͳ�Ƽ���
				huidu[temp]++;		
			}
		}
		// ����Ҷȷֲ��ܶ�
		for(i=0;i<256;i++)
			tongji[i] = huidu[i] / (height * wide *1.0f);
	}
	else	//24λ��ɫ
	{
       	wide=this->GetDibWidthBytes();
        height=this->GetHeight ();
		LPBYTE  temp1=new BYTE[wide*height];    //��ͼ�񻺳���
		//����ԭͼ�񵽻���ͼ��
		memcpy(temp1,m_pData,wide*height );
		// �Ը����ؽ��лҶ�ͳ��
		for (i = 0; i < height; i ++)
		{
			for (j = 0; j <wide; j ++)
			{
				unsigned char  temp = temp1[wide* i + j] ;
				// �Ҷ�ͳ�Ƽ���
				huidu[temp]++;		
			}
		} 
		// ����Ҷȷֲ��ܶ�
		for(i=0;i<256;i++)
			tongji[i] = huidu[i] / (height * wide *1.0f);
	} 
}


