//
//	ボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/12
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "farmbutton.h"

///////////////////////////////////////////////////////////
//	作成

void farmButton::CreateButton()
{
	int	i;

	//	パターン作成
	BmpButton.LoadBitmap("bitmap\\button01.bmp");
	for(i=0;i<FB_PAT_BUTTON;i++)
	{
		dPatButton[i].CreatePattern(&BmpButton,(i%2)*32,(i/2)*32,32,32);
	}

	//	その他初期化
	PosX=0;
	PosY=0;
}

void farmButton::ReleaseButton()
{
	BmpButton.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	設定

void farmButton::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

int farmButton::IsButton(int x,int y)
{
	if(y<PosY+3 || PosY+32-3<=y)	 return FB_BTN_NONE;
	if(PosX   +3<=x && x<PosX+ 32-3) return FB_BTN_HELP;
	if(PosX+40+3<=x && x<PosX+ 72-3) return FB_BTN_RETURN;
	if(PosX+80+3<=x && x<PosX+112-3) return FB_BTN_EXIT;

	return FB_BTN_NONE;
}

///////////////////////////////////////////////////////////
//	表示

void farmButton::Show(int mx,int my,bool f)
{
	int	b;

	b=IsButton(mx,my);

	if(b!=FB_BTN_EXIT) dPatButton[0].Put(PosX+80,PosY);
	else			   dPatButton[1].Put(PosX+80,PosY);

	if(f)
	{
		if(b!=FB_BTN_RETURN) dPatButton[2].Put(PosX+40,PosY);
		else				 dPatButton[3].Put(PosX+40,PosY);
		if(b!=FB_BTN_HELP)	 dPatButton[4].Put(PosX   ,PosY);
		else				 dPatButton[5].Put(PosX   ,PosY);
	}
	else
	{
		dPatButton[2].Put(PosX+40,PosY);
		dPatButton[4].Put(PosX   ,PosY);
	}
}
