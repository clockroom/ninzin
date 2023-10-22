//
//	戻るボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "homereturn.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void homeReturn::CreateReturn()
{
	//	初期化
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeReturn::ReleaseReturn()
{
}

///////////////////////////////////////////////////////////
//	リセット

void homeReturn::ResetReturn()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	設定

void homeReturn::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool homeReturn::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<3 || 172<=mx) return false;
	if(my<4 ||  24<=my) return false;

	return true;;
}

bool homeReturn::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void homeReturn::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==76) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void homeReturn::Show(int mx,int my)
{
	libFont		lf;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<56) return;

	//	表示位置設定
	py=PosY;
	if(56 FROMTO(cProg) 76) py+=(1<<9)>>((cProg-56)/2);

	//	表示
	if(IsButton(mx,my)) lf.BlendFont(PosX,py,24,"27タイトルに戻る1");
	else				lf.BlendFont(PosX,py,24,"27タイトルに戻る0");
}
