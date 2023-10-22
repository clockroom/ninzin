//
//	操作ボタンボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/13
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "optmouse.h"

///////////////////////////////////////////////////////////
//	作成

void optMouse::CreateMouse()
{
	//	ビットマップ読み込み
	BmpMouse.LoadBitmap("bitmap\\object02.bmp");

	//	初期化
	PosX=0;
	PosY=0;
	fTurnLR=false;
}

void optMouse::ReleaseMouse()
{
	BmpMouse.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	設定

void optMouse::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optMouse::SetTurnLR(bool f)
{
	fTurnLR=f;
}

void optMouse::SetTurnLR()
{
	fTurnLR=!fTurnLR;
}

///////////////////////////////////////////////////////////
//	取得

bool optMouse::GetTureLR()
{
	return fTurnLR;
}

bool optMouse::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<4 || 124<=mx) return false;
	if(my<6 ||  27<=my) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void optMouse::Show(int mx,int my)
{
	libFont	lf;
	bool	fmos;

	//	ボタン表示
	if(IsButton(mx,my)) lf.PutFont(PosX,PosY+2,"25操作ボタン1");
	else				lf.PutFont(PosX,PosY+2,"25操作ボタン0");

	//	状況表示
	fmos=(GetSystemMetrics(SM_SWAPBUTTON)==0)?false:true;
	if((!fmos && !fTurnLR) || (fmos && fTurnLR))
	{
		lf.PutFont(PosX+208,PosY+2,"23水やり");
		BmpMouse.Opaque(PosX+288,PosY,0,0,32,32);
		lf.PutFont(PosX+323,PosY+2,"23収穫");
	}
	else
	{
		lf.PutFont(PosX+208,PosY+2,"23収穫");
		BmpMouse.Opaque(PosX+288,PosY,0,0,32,32);
		lf.PutFont(PosX+323,PosY+2,"23水やり");
	}
}
