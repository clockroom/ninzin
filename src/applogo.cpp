//
//	メーカロゴアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "applogo.h"
#include "apptitle.h"

///////////////////////////////////////////////////////////
//	グローバル変数

appLogo AppLogo;

///////////////////////////////////////////////////////////
//	構築

appLogo::appLogo():OscFrmLim(40,10)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appLogo::InitApp()
{
	//	ビットマップ読み込み
	BmpLogo.LoadBitmap("bitmap\\logo01.bmp");

	//	初期化
	cProg=-1;

	//	処理設定
	SetActiveApp(this,APP_MAIN);
}

void appLogo::FinalApp()
{
	//	ビットマップ解放
	BmpLogo.ReleaseBitmap();

	//	処理設定
	SetActiveApp(&AppTitle,(FPAPPFUNC)appTitle::InitAppFromLogo);
}

void appLogo::Main()
{
	//	フレームリミッタ
	if(!OscFrmLim) return;

	//	カウント
	if(++cProg<0) cProg=0;
	if(cProg>=128)
	{
		SetActiveApp(this,APP_FINAL);
		return;
	}

	//	表示
	_Show();
}

///////////////////////////////////////////////////////////
//	表示

void appLogo::_Show()
{
	//	画面消去
	ms.ClearWhite();

	//	フェードイン
	if(32 FROMTO(cProg) 48)
	{
		BmpLogo.BrightOpaque(184,208,(64-cProg)*2,0,0,272,64);
	}

	//	停止
	if(48 FROMTO(cProg) 96)
	{
		BmpLogo.Opaque(184,208,0,0,272,64);
	}

	//	フェードアウト
	if(96 FROMTO(cProg) 112)
	{
		BmpLogo.BrightOpaque(184,208,(cProg-80)*2,0,0,272,64);
	}

	//	画面更新
	ms.Refresh();
}
