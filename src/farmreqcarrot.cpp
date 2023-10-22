//
//	リクエストニンジンクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/08
//	Last  Edition 2001/07/22
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "farmflycarrot.h"
#include "farmreqcarrot.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDREQUEST	1000

///////////////////////////////////////////////////////////
//	作成

void farmReqCarrot::CreateReqCarrot()
{
	//	その他初期化
	PosX=0;
	PosY=0;
	cProg=ENDREQUEST;
	ClearReqCarrot();
}

void farmReqCarrot::ReleaseReqCarrot()
{
}

void farmReqCarrot::ClearReqCarrot()
{
	int	i;

	for(i=0;i<36;i++) dRequest[i]=0x08;
	Total =0;
	TotalB=0;
}

///////////////////////////////////////////////////////////
//	リセット

void farmReqCarrot::ResetReqCarrot()
{
	cProg =-1;
}

///////////////////////////////////////////////////////////
//	設定

void farmReqCarrot::SetReqCarrot(BYTE *dr)
{
	BYTE	a,b;
	int		i,j;

	//	初期化
	ClearReqCarrot();

	//	登録
	for(i=0;i<36;i++)
	{
		if(dr[i]&0x08) break;
		dRequest[i]=dr[i]&0x07;
	}
	Total=TotalB=i;

	//	並べ替え
	for(j=0;j<35;j++)for(i=0;i<35-j;i++)
	{
		a=dRequest[i];
		b=dRequest[i+1];
		if(a<=b) continue;
		dRequest[i]  =b;
		dRequest[i+1]=a;
	}
}

void farmReqCarrot::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool farmReqCarrot::IsEndRequest()
{
	if(cProg<ENDREQUEST) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	更新

void farmReqCarrot::Update()
{
	BYTE	r;

	if(cProg>=ENDREQUEST) return;
	cProg++;

	if(cProg>=60 && Total==0) cProg=ENDREQUEST;

	if(Total==0)   return;
	if(cProg<40)   return;
	if(cProg%5!=0) return;

	//	飛行ニンジン作成
	r=dRequest[--Total];
	farmFlyCarrot::CreateFlyReqCarrot(r,PosX+Total*10,PosY);

	if(cProg>=60 && Total==0) cProg=ENDREQUEST;
}

///////////////////////////////////////////////////////////
//	表示

void farmReqCarrot::Show()
{
	libCarrot	lc;
	BYTE	r;
	int		i;
	int		x;

	if(Total==0) return;
	if(cProg>=ENDREQUEST) return;
	if(cProg<0) cProg=0;

	x=0;
	if(0 FROMTO(cProg) 20) x=(1<<9)>>(cProg/2);

	for(i=0;i<Total;i++)
	{
		r=dRequest[i];
		lc[r].Put(PosX+i*10-x,PosY);
	}
}

void farmReqCarrot::ShowFont()
{
	libFont	lf;
	int		x;

	if(cProg>=60) return;
	if(cProg<0) cProg=0;

	x=0;
	if( 0 FROMTO(cProg) 20) x=(1<<9)>>(cProg/2);
	if(40 FROMTO(cProg) 60) x=1<<((cProg-40)/2);

	lf.PutFont(PosX+TotalB*10-x,PosY+16,"22request");
}
