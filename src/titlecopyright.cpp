//
//	コピーライトクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/08/30
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "titlecopyright.h"

///////////////////////////////////////////////////////////
//	定数定義

#define USELESSCOPYRIGHT	2000
#define	ENDENTRANCE			1000

///////////////////////////////////////////////////////////
//	作成

void titleCopyright::CreateCopyright()
{
	//	ビットマップ読み込み
	BmpCopyright.LoadBitmap("bitmap\\logo03.bmp");

	//	その他初期化
	PosX=0;
	PosY=0;
	cProg=USELESSCOPYRIGHT;
}

void titleCopyright::ReleaseCopyright()
{
	BmpCopyright.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	リセット

void titleCopyright::ResetCopyrightMenuCall()
{
	cProg=-1;
}

void titleCopyright::ResetCopyrightMain()
{
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	設定

void titleCopyright::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool titleCopyright::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void titleCopyright::Update()
{
	if(cProg==USELESSCOPYRIGHT) return;
	if(cProg==ENDENTRANCE)		return;
	if(++cProg<8) return;
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void titleCopyright::Show()
{
	int	b;

	if(cProg==USELESSCOPYRIGHT) return;
	if(cProg<0) cProg=0;

	b=32;
	if(0 FROMTO(cProg) 8) b=64-cProg*4;

	BmpCopyright.Bright(PosX,PosY,b,0,0,284,104);
}
