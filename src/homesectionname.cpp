//
//	セクション名クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/01
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "homesectionname.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void homeSectionName::CreateSectionName()
{
	//	初期化
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeSectionName::ReleaseSectionName()
{
}

///////////////////////////////////////////////////////////
//	リセット

void homeSectionName::ResetSectionName()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	設定

void homeSectionName::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool homeSectionName::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void homeSectionName::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==30) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void homeSectionName::Show()
{
	libFont		lf;
	int	px;

	if(cProg<0) cProg=0;

	//	文字表示１
	px=PosX;
	if(0 FROMTO(cProg) 22) px+=(1<<10)>>(cProg/2);
	lf.PutFont(px,PosY,"21farm");

	//	文字表示２
	if(cProg<8) return;
	px=PosX;
	if(8 FROMTO(cProg) 30) px+=(1<<10)>>((cProg-8)/2);
	lf.PutFont(px+64,PosY+52,"21select");
}
