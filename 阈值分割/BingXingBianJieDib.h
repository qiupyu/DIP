#ifndef __BingXingBianJieDib_H
#define __BingXingBianJieDib_H
#include "Cdib.h"
 
typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;

typedef struct{
	int Height;
	int Width;
}	Seed;

typedef struct{
	int Height;
	int Width;
}	Point;

class BingXingBianJieDib :public CDib
{

public:
	BingXingBianJieDib();
	~BingXingBianJieDib();

public:
	void Zhifangtu(float *tongji);
	void Yuzhifenge(int Yuzhi);
	void BingXingBianJieDib::Fenbutongji(int *tongji);


protected:
};
#endif