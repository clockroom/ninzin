//
//	ウィンドウライブラリ ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/28
//	Last  Edition 2001/09/02
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libwindow.h"

///////////////////////////////////////////////////////////
//	クラス変数

afBitmap  libWindow::BmpMap;
afPattern libWindow::dPatMap[2];

///////////////////////////////////////////////////////////
//	初期化

void libWindow::InitLibrary()
{
	//	パターン作成
	BmpMap.LoadBitmap("bitmap\\map03.bmp");
	dPatMap[0].CreatePattern(&BmpMap, 0,0,48,48);
	dPatMap[1].CreatePattern(&BmpMap,48,0,48,48);
}

void libWindow::FinalLibrary()
{
	BmpMap.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	描画

void libWindow::PutWindow(int x,int y,int w,int h)
{
	afScreen	scr;
	afDC		dc;
	COLORREF	c1=RGB(124,106, 87);
	COLORREF	c2=RGB(139,120,106);

	scr.GetDC(&dc);
	dc.Box(x,y,x+w,y+h,1,c1,c2);
	dc.Pixel(x	  ,y	,RGB(0,0,0));
	dc.Pixel(x+w-1,y	,RGB(0,0,0));
	dc.Pixel(x	  ,y+h-1,RGB(0,0,0));
	dc.Pixel(x+w-1,y+h-1,RGB(0,0,0));
	dc.Pixel(x+1  ,y+1	,c1);
	dc.Pixel(x+w-2,y+1	,c1);
	dc.Pixel(x+1  ,y+h-2,c1);
	dc.Pixel(x+w-2,y+h-2,c1);
	scr.ReleaseDC(&dc);

	dPatMap[1].TileOpaque(x+2,y+2,w-4,h-4);
	scr.GetDC(&dc);
	dc.Pixel(x+2  ,y+2	,c2);
	dc.Pixel(x+w-3,y+2	,c2);
	dc.Pixel(x+2  ,y+h-3,c2);
	dc.Pixel(x+w-3,y+h-3,c2);
	scr.ReleaseDC(&dc);
}

void libWindow::PutWindowWithEdge(int x,int y,int w,int h)
{
	dPatMap[0].TileOpaque(x,y,48,h);
	dPatMap[1].TileOpaque(x+48,y,w-48,h);
}
