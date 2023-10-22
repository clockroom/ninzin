//
//	タイトルクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/09
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libsound.h"
#include "titletitle.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void titleTitle::CreateTitle()
{
	//	パターン作成
	BmpTitle.LoadBitmap("bitmap\\logo02.bmp",true);
	PatTitle.CreatePattern(&BmpTitle,0,0,640,178);

	//	その他初期化
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void titleTitle::ReleaseTitle()
{
	BmpTitle.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	リセット

void titleTitle::ResetTitleTitleCall()
{
	cProg=-1;
}

void titleTitle::ResetTitleMain()
{
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	設定

void titleTitle::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool titleTitle::IsEndEntrance()
{
	if(cProg<ENDENTRANCE) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	更新

void titleTitle::Update()
{
	if(cProg>=ENDENTRANCE) return;
	if(++cProg<250)		   return;
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void titleTitle::Show()
{
	libSound	ls;
	int	dst1[]={22,62,86,106,122};
	int	dst2[]={134,142,146};
	int	a,y;
	int	i;

	if(cProg<0) cProg=0;

	y=-120;
	if(  0 FROMTO(cProg)  22) {a=cProg;    y+=363-a*a*3/4;}
	if( 22 FROMTO(cProg)  42) {a=42-cProg; y+=300-a*a*3/4;}
	if( 42 FROMTO(cProg)  62) {a=cProg-42; y+=300-a*a*3/4;}
	if( 62 FROMTO(cProg)  74) {a=74-cProg; y+=108-a*a*3/4;}
	if( 74 FROMTO(cProg)  86) {a=cProg-74; y+=108-a*a*3/4;}
	if( 86 FROMTO(cProg)  96) {a=96-cProg; y+= 75-a*a*3/4;}
	if( 96 FROMTO(cProg) 106) {a=cProg-96; y+= 75-a*a*3/4;}
	if(106 FROMTO(cProg) 114) {a=114-cProg;y+= 48-a*a*3/4;}
	if(114 FROMTO(cProg) 122) {a=cProg-114;y+= 48-a*a*3/4;}
	if(122 FROMTO(cProg) 128) {a=128-cProg;y+= 27-a*a*3/4;}
	if(128 FROMTO(cProg) 134) {a=cProg-128;y+= 27-a*a*3/4;}
	if(134 FROMTO(cProg) 138) {a=138-cProg;y+= 12-a*a*3/4;}
	if(138 FROMTO(cProg) 142) {a=cProg-138;y+= 12-a*a*3/4;}
	if(142 FROMTO(cProg) 144) {a=144-cProg;y+=  3-a*a*3/4;}
	if(144 FROMTO(cProg) 146) {a=cProg-144;y+=  3-a*a*3/4;}
	if(160 FROMTO(cProg) 200) y=-(200-cProg)*3;
	if(200 FROMTO(cProg) 250) y=0;
	if(cProg>=ENDENTRANCE) y=0;

	PatTitle.Opaque(PosX,PosY-y);

	//	音声再生
	if(0 FROMTO(cProg) 123)
	{
		for(i=0;i<5;i++)
		{
			if(cProg==dst1[i]) ls.PlaySound(20);
		}
	}
	if(134 FROMTO(cProg) 147)
	{
		for(i=0;i<3;i++)
		{
			if(cProg==dst2[i]) ls.PlaySound(21);
		}
	}
}
