//
//	戻るボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/06
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "optreturn.h"

///////////////////////////////////////////////////////////
//	作成

void optReturn::CreateReturn()
{
	//	初期化
	PosX=0;
	PosY=0;
}

void optReturn::ReleaseReturn()
{
}

///////////////////////////////////////////////////////////
//	設定

void optReturn::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool optReturn::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<3 || 169<=mx) return false;
	if(my<3 ||  24<=my) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void optReturn::Show(int mx,int my)
{
	libFont	lf;

	//	表示
	if(IsButton(mx,my)) lf.PutFont(PosX,PosY,"25タイトルに戻る1");
	else				lf.PutFont(PosX,PosY,"25タイトルに戻る0");
}
