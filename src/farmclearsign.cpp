//
//	クリアサインクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/07/22
//

///////////////////////////////////////////////////////////
//	インクルード

#include "libfont.h"
#include "libsound.h"
#include "farmclearsign.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDSIGN	60

///////////////////////////////////////////////////////////
//	作成

void farmClearSign::CreateClearSign()
{
	PosX=0;
	PosY=0;
	cProg=ENDSIGN;
}

void farmClearSign::ReleaseClearSign()
{
}

///////////////////////////////////////////////////////////
//	リセット

void farmClearSign::ResetClearSign()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	設定

void farmClearSign::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool farmClearSign::IsEndSign()
{
	if(cProg<ENDSIGN) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	更新

void farmClearSign::Update()
{
	if(cProg>=ENDSIGN) return;
	cProg++;
}

///////////////////////////////////////////////////////////
//	表示

void farmClearSign::Show()
{
	afScreen	scr;
	libFont		lf;
	libSound	ls;
	int	x,b;

	if(cProg>=ENDSIGN) return;
	if(cProg<0) cProg=0;

	//	共通設定
	x=0;
	b=64;

	//	変更
	if(0 FROMTO(cProg) 20)
	{
		x=-(1<<9)>>(cProg/2);
		b=cProg*32/20;
	}
	if(40 FROMTO(cProg) 60)
	{
		x=1<<((cProg-40)/2);
		b=(59-cProg)*32/20;
	}

	//	表示
	scr.SetDrawArea(0,0,480,480);
	lf.BlendFont(PosX+x,PosY,b,"21clear");
	scr.SetDrawArea();

	//	音声再生
	if(cProg== 0) ls.PlaySound(17);
	if(cProg==40) ls.PlaySound(18);
}
