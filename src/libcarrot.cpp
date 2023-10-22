//
//	ニンジンライブラリ by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/10
//	Last  Edition 2001/07/10
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libcarrot.h"

///////////////////////////////////////////////////////////
//	クラス変数

afBitmap  libCarrot::BmpCarrot;
afPattern libCarrot::dPatCarrot[12];

///////////////////////////////////////////////////////////
//	初期化

void libCarrot::InitLibrary()
{
	int	i;

	BmpCarrot.LoadBitmap("bitmap\\carrot01.bmp");
	for(i=0;i<12;i++)
	{
		dPatCarrot[i].CreatePattern(&BmpCarrot,(i%4)*32,(i/4)*32,32,32);
	}
}

void libCarrot::FinalLibrary()
{
	BmpCarrot.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	オペレータ

afPattern &libCarrot::operator[](int n)
{
	return dPatCarrot[n];
}
