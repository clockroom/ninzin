//
//	エンディングアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/16
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "libmusic.h"
#include "fileplaydata.h"
#include "appfade.h"
#include "apphome.h"
#include "appending.h"

///////////////////////////////////////////////////////////
//	グローバル変数

appEnding AppEnding;

///////////////////////////////////////////////////////////
//	構築

appEnding::appEnding():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appEnding::InitApp()
{
	libMusic		lm;
	filePlayData	fpd;
	int	gw,bw;

	//	マウス初期化
	mos.ResetKey();

	//	ビットマップ読み込み
	BmpMsg1.LoadBitmap("bitmap\\object03.bmp");
	BmpMsg2.LoadBitmap("bitmap\\object04.bmp");
	BmpMsg3.LoadBitmap("bitmap\\object05.bmp");
	BmpStaff.LoadBitmap("bitmap\\object06.bmp");

	//	ランク取得
	fpd.LoadPlayData();
	fpd.GetTotalRecord(&gw,&bw,NULL);
	if(bw<=gw) fRankA=true;
	else	   fRankA=false;

	//	BGM停止
	lm.StopMusic();

	//	フェードイン
	ms.Clear();
	DrawObject();
	AppFade.CallFade(AF_FADE_BLACKIN,16,this,(FPAPPFUNC)appEnding::Main);
}

void appEnding::FinalApp()
{
	BmpMsg1.ReleaseBitmap();
	BmpMsg2.ReleaseBitmap();
	BmpMsg3.ReleaseBitmap();
	BmpStaff.ReleaseBitmap();

	//	ホームへ移動
	SetActiveApp(&AppHome,(FPAPPFUNC)appHome::InitApp);
}

///////////////////////////////////////////////////////////
//	メイン

void appEnding::Main()
{
	//	マウス更新
	mos.UpdateKey();

	//	表示
	ms.Clear();
	DrawObject();
	ms.Refresh();

	//	スタッフロールへ
	if(mos.GetKeyL()==KEY_PULL)
	{
		cProg=0;
		AppFade.CallFade(AF_FADE_BLACKOUT,16,this,(FPAPPFUNC)appEnding::StaffRoll);
	}
}

///////////////////////////////////////////////////////////
//	スタッフロール

void appEnding::StaffRoll()
{
	//	フレームリミッタ
	if(!OscFrmLim) return;

	//	表示
	ms.Clear();
	BmpStaff.Opaque(120,520-cProg,0,0,402,162);
	ms.Refresh();

	//	カウント
	if(++cProg>840) SetActiveApp(this,APP_FINAL);
}

///////////////////////////////////////////////////////////
//	オブジェクト描画

void appEnding::DrawObject()
{
	if(!fRankA)
	{
		BmpMsg1.Opaque(110,112,0,0,406,60);
		BmpMsg2.Opaque(134,208,0,0,374,70);
		BmpMsg3.Opaque(60,304,0,0,522,68);
	}
	else
	{
		BmpMsg1.Opaque(110,160,0,0,406,60);
		BmpMsg2.Opaque(134,256,0,0,374,70);
	}
}
