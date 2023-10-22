//
//	ステータスクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/09
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libitem.h"
#include "libwindow.h"
#include "farmstate.h"

///////////////////////////////////////////////////////////
//	定数定義

#define PROC_NONE		0
#define PROC_STARTSIGN	1
#define PROC_MAIN		2
#define PROC_PAUSE		3

#define ENDCOUNT	1000

///////////////////////////////////////////////////////////
//	作成

void farmState::CreateState()
{
	//	ステータス用ビットマップ作成
	_CreateStateBitmap();

	//	その他初期化
	PosX=0;
	PosY=0;
	FarmNo=0;
	GoodWater=0;
	cGoodWater=0;
	BestWater=0;
	BestTime=0;
	cWater=0;
	cTime=0;
	nProc=PROC_NONE;
	cProg=ENDCOUNT;
}

void farmState::ReleaseState()
{
	BmpState.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	ビットマップ作成

void farmState::_CreateStateBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	afScreen	scr;

	//	ビットマップ作成
	BmpState.CreateBitmap(160,480,true);

	scr.SetWorkScreen(&BmpState);
	scr.SetDrawArea(0,0,160,480);

	//	ベース表示
	lw.PutWindowWithEdge(0,0,160,480);

	//	ファーム番号
	lf.PutFont(16,8,"22farm");
	li.PutItem(80,8,64,24);

	//	ニンジン
	lf.PutFont(16,40,"22carrot");
	li.PutItem(16,64,128,288);

	//	水
	lf.PutFont(16,360,"22water");
	li.PutItem(96,358,48,24);
	li.PutItem(16,384,128,24);
	li.PutItem(16,410,128,24);

	scr.RestoreWorkScreen();
	scr.SetDrawArea();
}

///////////////////////////////////////////////////////////
//	リセット

void farmState::ResetStateNone()
{
	nProc=PROC_NONE;
	cProg=-1;
}

void farmState::ResetStateStartSign()
{
	nProc=PROC_STARTSIGN;
	cProg=-1;
	cGoodWater=-1;
	cWater=0;
	cTime=0;
}

void farmState::ResetStateMain()
{
	nProc=PROC_MAIN;
	cProg=-1;
}

void farmState::PauseState()
{
	nProc=PROC_PAUSE;
}

void farmState::RestartState()
{
	nProc=PROC_MAIN;
}

///////////////////////////////////////////////////////////
//	設定

void farmState::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void farmState::SetFarmNo(int n)
{
	FarmNo=n;
}

void farmState::SetGoodWater(int n)
{
	GoodWater=n;
}

void farmState::SetBestRecord(int w,int t)
{
	BestWater=w;
	BestTime=t;
}

void farmState::AddWater(int add)
{
	cWater+=add;
	if(cWater<0)   cWater=0;
	if(cWater>100) cWater=100;
}

///////////////////////////////////////////////////////////
//	取得

void farmState::GetRecord(int *pw,int *pt)
{
	if(pw!=NULL) *pw=cWater;
	if(pt!=NULL) *pt=cTime;
}

void farmState::GetBestRecord(int *pw,int *pt)
{
	if(pw!=NULL) *pw=BestWater;
	if(pt!=NULL) *pt=BestTime;
}

bool farmState::IsEndCount()
{
	if(nProc!=PROC_STARTSIGN) return true;
	if(cProg>=ENDCOUNT)		  return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void farmState::Update()
{
	switch(nProc)
	{
	case PROC_STARTSIGN:

		if(cProg>=ENDCOUNT) break;
		if((++cProg)%2!=0) break;
		if((++cGoodWater)<GoodWater) break;
		cProg=ENDCOUNT;
		cGoodWater=GoodWater;

		break;

	case PROC_MAIN:

		if(cTime<50000) cTime++;

		break;
	}
}

///////////////////////////////////////////////////////////
//	表示

void farmState::Show()
{
	libFont	lf;
	char	str1[256];
	char	str2[256];

	if(cProg<0) cProg=0;
	if(cGoodWater<0) cGoodWater=0;

	//	ベース表示
	if(BmpState.IsLost()) _CreateStateBitmap();
	BmpState.Opaque(PosX,PosY,0,0,160,480);

	//	ファーム番号
	sprintf(str1,"11%02d",FarmNo);
	lf.PutFont(PosX+96,PosY+12,str1);

	//	目標値
	sprintf(str1,"11%02d",cGoodWater);
	lf.PutFont(PosX+104,PosY+362,str1);

	//	現在値
	if(cWater<100)	sprintf(str1,"12%02d",cWater);
	else			sprintf(str1,"12--");
	if(cTime<50000)	sprintf(str2,"###t#%03d",cTime/50);
	else			sprintf(str2,"###t#---");
	strcat(str1,str2);
	lf.PutFont(PosX+24,PosY+388,str1);
	lf.PutFont(PosX+68,PosY+388,"12t");

	//	ベスト値
	if(BestWater<100) sprintf(str1,"11%02d",BestWater);
	else			  sprintf(str1,"11--");
	if(BestTime<50000) sprintf(str2,"###t#%03d",BestTime/50);
	else			   sprintf(str2,"###t#---");
	strcat(str1,str2);
	lf.PutFont(PosX+24,PosY+414,str1);
	lf.PutFont(PosX+68,PosY+414,"11t");
}
