//
//	失敗サインクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/03
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include "libfont.h"
#include "libsound.h"
#include "farmfailuresign.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDSIGN	1000

///////////////////////////////////////////////////////////
//	作成

void farmFailureSign::CreateFailureSign()
{
	PosX=0;
	PosY=0;
	cProg=ENDSIGN;
}

void farmFailureSign::ReleaseFailureSign()
{
}

///////////////////////////////////////////////////////////
//	リセット

void farmFailureSign::ResetFailureSign()
{
	cProg=-1;
}

void farmFailureSign::ResetFailureSignNone()
{
	cProg=ENDSIGN;
}

///////////////////////////////////////////////////////////
//	設定

void farmFailureSign::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool farmFailureSign::IsEndSign()
{
	if(cProg==ENDSIGN) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void farmFailureSign::Update()
{
	if(cProg==ENDSIGN) return;
	if(++cProg==220) cProg=ENDSIGN;
}

///////////////////////////////////////////////////////////
//	表示

void farmFailureSign::Show()
{
	libFont		lf;
	libSound	ls;
	int	dst[]={23,57,83,103,115,123,129,133};
	int	i;
	int	y,a,b;

	if(cProg>=ENDSIGN) return;
	if(cProg<0) cProg=0;

	//	共通設定
	y=0;
	b=32;

	//	変更
	if(  0 FROMTO(cProg)  23) {a=cProg	  ;y=(396-a*a*3/4);}
	if( 23 FROMTO(cProg)  40) {a=40-cProg ;y=(216-a*a*3/4);}
	if( 40 FROMTO(cProg)  57) {a=cProg-40 ;y=(216-a*a*3/4);}
	if( 57 FROMTO(cProg)  70) {a= 70-cProg;y=(126-a*a*3/4);}
	if( 70 FROMTO(cProg)  83) {a=cProg- 70;y=(126-a*a*3/4);}
	if( 83 FROMTO(cProg)  93) {a= 93-cProg;y=( 75-a*a*3/4);}
	if( 93 FROMTO(cProg) 103) {a=cProg- 93;y=( 75-a*a*3/4);}
	if(103 FROMTO(cProg) 109) {a=109-cProg;y=( 27-a*a*3/4);}
	if(109 FROMTO(cProg) 115) {a=cProg-109;y=( 27-a*a*3/4);}
	if(115 FROMTO(cProg) 119) {a=119-cProg;y=( 12-a*a*3/4);}
	if(119 FROMTO(cProg) 123) {a=cProg-119;y=( 12-a*a*3/4);}
	if(123 FROMTO(cProg) 126) {a=126-cProg;y=(  6-a*a*3/4);}
	if(126 FROMTO(cProg) 129) {a=cProg-126;y=(  6-a*a*3/4);}
	if(129 FROMTO(cProg) 131) {a=131-cProg;y=(  3-a*a*3/4);}
	if(131 FROMTO(cProg) 133) {a=cProg-131;y=(  3-a*a*3/4);}

	if(160 FROMTO(cProg) 192) b=192-cProg;
	if(cProg>=192) b=0;

	//	表示
	lf.BlendFont(PosX,PosY-y,b,"21failure");

	//	音声再生
	if(cProg>133) return;
	for(i=0;i<8;i++)
	{
		if(cProg==dst[i]) ls.PlaySound(13);
	}
}
