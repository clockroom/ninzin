//
//	タイトルアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libmusic.h"
#include "libsound.h"
#include "libcursor.h"
#include "fileoption.h"
#include "appfade.h"
#include "apptitle.h"
#include "apphome.h"
#include "appoption.h"

///////////////////////////////////////////////////////////
//	定数定義

#define PROCESS_LOADTITLE	 0
#define PROCESS_TITLECALL	10
#define PROCESS_MENUCALL	20
#define PROCESS_MAIN		30

///////////////////////////////////////////////////////////
//	グローバル変数

appTitle AppTitle;

///////////////////////////////////////////////////////////
//	構築

appTitle::appTitle():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appTitle::InitApp()
{
	libCursor	lc;
	fileOption	fo;

	//	オプション設定
	fo.LoadOption();
	libMusic::SetOutputSystem(fo.GetBGMOutput());
	afMusic2::SetMasterVolume(fo.GetBGMVolume());
	afSound ::SetMasterVolume(fo.GetSEVolume());

	//	ライブラリ初期化
	libFont::InitLibrary(26);
	libMusic::InitLibrary(1);
	libSound::InitLibrary();
	libSound::InitLibrary(20,2);
	libSound::InitLibrary(21,3);
	libCursor::InitLibrary();

	//	マウス初期化
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	タイトル初期化
	Title.CreateTitle();
	Title.SetPos(0,32);

	//	コピーライト初期化
	Copyright.CreateCopyright();
	Copyright.SetPos(178,376);

	//	メニュー初期化
	Menu.CreateMenu();
	Menu.SetPos(224,248);
}

void appTitle::FinalApp()
{
	//	オブジェクト解放
	Title.ReleaseTitle();
	Copyright.ReleaseCopyright();
	Menu.ReleaseMenu();

	//	ライブラリ解放
	libFont::FinalLiblary();
	libMusic::FinalLibrary();
	libSound::FinalLibrary();
	libCursor::FinalLibrary();
}

///////////////////////////////////////////////////////////
//	初期化補助

void appTitle::InitAppFromLogo()
{
	//	初期化
	InitApp();

	//	フェードイン
	nProcess=PROCESS_LOADTITLE;
	SetActiveApp(this,APP_MAIN);
}

void appTitle::InitAppFromHome()
{
	libMusic	lm;

	//	初期化
	InitApp();

	//	オブジェクトリセット
	Title.ResetTitleMain();
	Copyright.ResetCopyrightMain();
	Menu.ResetMenuMain();

	//	BGM停止
	lm.StopMusic();

	//	画面構築
	ms.ClearWhite();
	Title.Show();
	Copyright.Show();
	Menu.Show(-1,-1);

	//	フェードイン
	nProcess=PROCESS_MAIN;
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appTitle::Main);
}

void appTitle::InitAppFromOption()
{
	//	初期化
	InitApp();

	//	オブジェクトリセット
	Title.ResetTitleMain();
	Copyright.ResetCopyrightMain();
	Menu.ResetMenuMain();

	//	画面構築
	ms.ClearWhite();
	Title.Show();
	Copyright.Show();
	Menu.Show(-1,-1);

	//	フェードイン
	nProcess=PROCESS_MAIN;
	AppFade.CallFade(AF_FADE_WHITEIN,8,this,(FPAPPFUNC)appTitle::Main);
}

void appTitle::FinalAppToHome()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppHome,(FPAPPFUNC)appHome::InitApp);
}

void appTitle::FinalAppToOption()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_WHITEOUT,8,&AppOption,(FPAPPFUNC)appOption::InitApp);
}

void appTitle::FinalAppToEndProgram()
{
	FinalApp();

	cProg=-1;
	AppFade.CallFade(AF_FADE_BLACKOUT,8,this,(FPAPPFUNC)appTitle::_EndProgram);
}

///////////////////////////////////////////////////////////
//	プログラム終了

void appTitle::_EndProgram()
{
	libMusic	lm;

	if(!OscFrmLim) return;

	cProg++;
	if(cProg==25) lm.StopMusic();
	if(cProg< 50) return;

	ExitProgram();
}

///////////////////////////////////////////////////////////
//	メイン

void appTitle::Main()
{
	//	フレームリミッタ
	if(!OscFrmLim) return;

	//	キー更新
	mos.UpdateKey();

	//	前置イベント
	_PreEvent();

	//	表示
	_Show();
}

///////////////////////////////////////////////////////////
//	前置イベント

void appTitle::_PreEvent()
{
	//	プロセス更新
	_UpdateProcess();

	//	オブジェクト更新
	Title.Update();
	Copyright.Update();
	Menu.Update();

	//	イベント処理
	_MouseEvent();
}

///////////////////////////////////////////////////////////
//	プロセス更新

void appTitle::_UpdateProcess()
{
	libMusic	lm;
	bool		a,b;

	switch(nProcess)
	{
	case PROCESS_LOADTITLE:

		Title.ResetTitleTitleCall();

		cProg=0;
		nProcess=PROCESS_TITLECALL;

		break;

	case PROCESS_TITLECALL:

		if(++cProg==150) lm.PlayMusic(1);

		a=Title.IsEndEntrance();
		if(!a) break;

		Copyright.ResetCopyrightMenuCall();
		Menu.ResetMenuMenuCall();

		nProcess=PROCESS_MENUCALL;

		break;

	case PROCESS_MENUCALL:

		a=Copyright.IsEndEntrance();
		b=Menu.IsEndEntrance();
		if(!a || !b) break;

		Title.ResetTitleMain();
		Copyright.ResetCopyrightMain();
		Menu.ResetMenuMain();

		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	マウスイベント

bool appTitle::_MouseEvent()
{
	libMusic	lm;
	libSound	ls;
	int	mx,my;

	//	マウス押下以外
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	メニュー表示前
	if(nProcess!=PROCESS_MAIN)
	{
		Title.ResetTitleMain();
		Copyright.ResetCopyrightMain();
		Menu.ResetMenuMain();
		lm.PlayMusic(1);
		nProcess=PROCESS_MAIN;
		return true;
	}

	//	メニュー選択
	mos.GetPos(&mx,&my);
	switch(Menu.IsMenu(mx,my))
	{
	case TM_MENU_START:
		ls.PlaySound(6);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToHome);
		break;

	case TM_MENU_OPTION:
		ls.PlaySound(6);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToOption);
		break;

	case TM_MENU_END:
		ls.PlaySound(7);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToEndProgram);
		break;

	default:
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void appTitle::_Show()
{
	int	mx,my;

	//	画面消去
	ms.ClearWhite();

	//	タイトル表示
	Title.Show();

	//	コピーライト表示
	Copyright.Show();

	//	メニュー表示
	mos.GetPos(&mx,&my);
	Menu.Show(mx,my);

	//	マウス表示
	if(nProcess==PROCESS_MAIN) mos.Show();

	//	画面更新
	ms.Refresh();
}
