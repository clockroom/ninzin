//
//	ヘルプクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/07
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "homehelp.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void homeHelp::CreateHelp()
{
	//	ビットマップ作成
	_CreateHelpBitmap();

	//	初期化
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeHelp::ReleaseHelp()
{
	BmpHelp.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	ビットマップ作成

void homeHelp::_CreateHelpBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	afScreen	scr;
	afDC		dc;

	//	ビットマップ作成
	BmpHelp.CreateBitmap(272,100);

	//	ウィンドウ描画
	scr.SetWorkScreen(&BmpHelp);
	scr.SetDrawArea(0,0,272,100);
	lw.PutWindow(0,0,272,100);
	lf.PutFont(8,8,"22help");
	li.PutItem(8,36,256,56);
	scr.RestoreWorkScreen();
	scr.SetDrawArea();

	//	文字描画
	BmpHelp.GetDC(&dc);
	dc.Text(16,47,"右のファーム一覧表からプレイし",16,true,RGB(255,255,255));
	dc.Text(16,67,"たい面を選択してください。",16,true,RGB(255,255,255));
	BmpHelp.ReleaseDC(&dc);
}

///////////////////////////////////////////////////////////
//	リセット

void homeHelp::ResetHelp()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	設定

void homeHelp::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool homeHelp::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void homeHelp::Updata()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==68) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void homeHelp::Show()
{
	libSound	ls;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<48) return;

	//	表示位置設定
	py=PosY;
	if(48 FROMTO(cProg) 68) py+=(1<<9)>>((cProg-48)/2);

	//	ヘルプ表示
	if(BmpHelp.IsLost()) _CreateHelpBitmap();
	BmpHelp.Put(PosX,py,0,0,272,100);

	//	音声再生
	if(cProg==50) ls.PlaySound(16);
}
