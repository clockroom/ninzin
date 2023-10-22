//
//	レコードクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/16
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "common.h"
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "fileplaydata.h"
#include "homerecord.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void homeRecord::CreateRecord(filePlayData *ppd)
{
	//	初期化
	pPlayData=ppd;
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;

	//	ビットマップ作成
	_CreateRecordBitmap();
}

void homeRecord::ReleaseRecord()
{
	BmpRecord.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	リセット

void homeRecord::ResetRecord()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	ビットマップ作成

void homeRecord::_CreateRecordBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	afScreen	scr;
	char	str[256];
	char	r;
	int		a;
	int		c,gw,bw,bt;

	//	ビットマップ作成
	BmpRecord.CreateBitmap(272,120);

	scr.SetWorkScreen(&BmpRecord);
	scr.SetDrawArea(0,0,272,120);

	//	ベース描画
	lw.PutWindow(0,0,272,120);

	//	文字描画
	lf.PutFont(8, 8,"22rank");
	lf.PutFont(8,64,"22record");

	//	項目描画
	li.PutItem(  8,32, 48,24);
	li.PutItem( 64,32,200,24);
	li.PutItem(  8,88, 48,24);
	li.PutItem( 64,88, 64,24);
	li.PutItem(136,88,128,24);

	//	データ取得
	c=pPlayData->GetClearCount();
	pPlayData->GetTotalRecord(&gw,&bw,&bt);

	//	ランク決定
	r='F';
	if(c>=26) r='E';
	if(c==MAX_FARM)
	{
		a=bw-gw;
		r='D';
		if(a<=30) r='C';
		if(a<=10) r='B';
		if(a<= 0) r='A';
	}

	//	ランク描画
	sprintf(str,"17%c",r);
	lf.PutFont(23,36,str);
	sprintf(str,"28%c",r);
	lf.PutFont(84,36,str);

	//	レコード描画
	sprintf(str,"11%02d",c);
	lf.PutFont(16,92,str);

	if(bw<1000) sprintf(str,"11%03d",bw);
	else	   sprintf(str,"11---");
	lf.PutFont(72,92,str);

	if(bt<500000) sprintf(str,"11t#%06.1f",bt/50.0);
	else		 sprintf(str,"11t#----.-");
	lf.PutFont(146,92,str);

	scr.RestoreWorkScreen();
	scr.SetDrawArea();
}

///////////////////////////////////////////////////////////
//	設定

void homeRecord::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool homeRecord::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void homeRecord::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==60) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void homeRecord::Show()
{
	libSound	ls;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<40) return;

	//	表示位置設定
	py=PosY;
	if(40 FROMTO(cProg) 60) py+=(1<<9)>>((cProg-40)/2);

	//	ウィンドウ表示
	if(BmpRecord.IsLost()) _CreateRecordBitmap();
	BmpRecord.Put(PosX,py,0,0,272,120);

	//	音声再生
	if(cProg==42) ls.PlaySound(16);
}
