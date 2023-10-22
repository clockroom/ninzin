//
//	ＢＧＭ方式ボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/21
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "optbgmoutput.h"

///////////////////////////////////////////////////////////
//	作成

void optBGMOutput::CreateBGMOutput()
{
	//	初期化
	PosX=0;
	PosY=0;
	fDirectMusic=false;
}

void optBGMOutput::ReleaseBGMOutput()
{
}

///////////////////////////////////////////////////////////
//	設定

void optBGMOutput::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optBGMOutput::SetBGMOutput(bool f)
{
	fDirectMusic=f;
}

void optBGMOutput::SetBGMOutput()
{
	fDirectMusic=!fDirectMusic;
}

///////////////////////////////////////////////////////////
//	取得

bool optBGMOutput::GetBGMOutput()
{
	return fDirectMusic;
}

bool optBGMOutput::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<4 || 113<=mx) return false;
	if(my<6 ||  27<=my) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void optBGMOutput::Show(int mx,int my)
{
	libFont	lf;

	//	ボタン表示
	if(IsButton(mx,my)) lf.PutFont(PosX,PosY+2,"25ＢＧＭ方式1");
	else				lf.PutFont(PosX,PosY+2,"25ＢＧＭ方式0");

	//	状況表示
	if(fDirectMusic) lf.PutFont(PosX+208,PosY+2,"23DirectMusic");
	else			 lf.PutFont(PosX+208,PosY+2,"23MCI");
}
