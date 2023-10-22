//
//	フェードアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "appfade.h"

///////////////////////////////////////////////////////////
//	グローバル変数

appFade AppFade;

///////////////////////////////////////////////////////////
//	構築

appFade::appFade():OscFrmLim(40,10)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appFade::InitApp()
{
	//	初期化
	cProg=-1;

	//	処理設定
	SetActiveApp(this,APP_MAIN);
}

void appFade::FinalApp()
{
	//	ビットマップ解放
	BmpScreen.ReleaseBitmap();

	//	処理設定
	SetActiveApp(pApp,fpFunc);
}

///////////////////////////////////////////////////////////
//	メイン

void appFade::Main()
{
	//	フレームリミッタ
	if(!OscFrmLim) return;

	//	カウント
	cProg++;
	if(cProg<0) return;
	if(cProg>Frame)
	{
		SetActiveApp(this,APP_FINAL);
		return;
	}

	//	フェード
	switch(nFade)
	{
	case AF_FADE_NONE:	  _FadeNone();	  break;
	case AF_FADE_BLACKOUT:_FadeBlackOut();break;
	case AF_FADE_BLACKIN: _FadeBlackIn(); break;
	case AF_FADE_WHITEOUT:_FadeWhiteOut();break;
	case AF_FADE_WHITEIN: _FadeWhiteIn() ;break;
	}
}

///////////////////////////////////////////////////////////
//	フェード無し

void appFade::_FadeNone()
{
	BmpScreen.Opaque(0,0,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	ブラックアウト

void appFade::_FadeBlackOut()
{
	BmpScreen.BrightOpaque(0,0,32-cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	ブラックイン

void appFade::_FadeBlackIn()
{
	BmpScreen.BrightOpaque(0,0,cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	ホワイトアウト

void appFade::_FadeWhiteOut()
{
	BmpScreen.BrightOpaque(0,0,32+cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	ホワイトイン

void appFade::_FadeWhiteIn()
{
	BmpScreen.BrightOpaque(0,0,64-cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	フェード呼び出し

void appFade::CallFade(int n,int f,afApp *p,FPAPPFUNC fp)
{
	//	ビットマップ作成
	BmpScreen.CreateBitmap(640,480);
	BmpScreen.ClipScreen(0,0,640,480);

	//	フェード情報設定
	pApp=p;
	fpFunc=fp;
	nFade=n;
	Frame=f;

	//	処理設定
	SetActiveApp(this,APP_INIT);
}
