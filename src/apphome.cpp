//
//	ホームアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/27
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libitem.h"
#include "libmusic.h"
#include "libsound.h"
#include "libwindow.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "appfade.h"
#include "apptitle.h"
#include "apphome.h"
#include "appfarm.h"

///////////////////////////////////////////////////////////
//	定数定義

#define PROCESS_LOADHOME	 0
#define	PROCESS_WINDOWCALL	10
#define PROCESS_MAIN		20

///////////////////////////////////////////////////////////
//	グローバル変数

appHome AppHome;

///////////////////////////////////////////////////////////
//	構築

appHome::appHome():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appHome::InitApp()
{
	libMusic	lm;
	libCursor	lc;

	//	ライブラリ初期化
	libFont::InitLibrary();
	libFont::InitLibrary(17);
	libFont::InitLibrary(27);
	libFont::InitLibrary(28);
	libItem::InitLibrary();
	libMusic::InitLibrary(2);
	libSound::InitLibrary();
	libSound::InitLibrary(5,1);
	libSound::InitLibrary(15,3);
	libSound::InitLibrary(16,2);
	libWindow::InitLibrary();
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	マウス初期化
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	プレイデータ読み込み
	PlayData.LoadPlayData();

	//	背景初期化
	BackGround.CreateBackGround();

	//	セクション名初期化
	SectionName.CreateSectionName();
	SectionName.SetPos(36,28);

	//	レコード初期化
	Record.CreateRecord(&PlayData);
	Record.SetPos(16,140);

	//	ヘルプ初期化
	Help.CreateHelp();
	Help.SetPos(16,272);

	//	戻るボタン初期化
	Return.CreateReturn();
	Return.SetPos(64,400);

	//	ファームリスト初期化
	FarmList.CreateFarmList(&PlayData);
	FarmList.SetPos(300,38);

	//	変数初期化
	nProcess=PROCESS_LOADHOME;

	//	BGM再生
	lm.PlayMusic(2);
	Sleep(2000);

	//	フェードイン
	BackGround.Show();
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appHome::Main);
}

void appHome::FinalApp()
{
	//	オブジェクト解放
	BackGround.ReleaseBackGround();
	SectionName.ReleaseSectionName();
	Record.ReleaseRecord();
	Help.ReleaseHelp();
	Return.ReleaseReturn();
	FarmList.ReleaseFarmList();

	//	ライブラリ解放
	libFont::FinalLiblary();
	libItem::FinalLibrary();
	libMusic::FinalLibrary();
	libSound::FinalLibrary();
	libWindow::FinalLibrary();
	libCursor::FinalLibrary();
	libCarrot::FinalLibrary();
}

///////////////////////////////////////////////////////////
//	初期化補助

void appHome::FinalAppToFarm()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppFarm,(FPAPPFUNC)appFarm::InitApp);
}

void appHome::FinalAppToTitle()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppTitle,(FPAPPFUNC)appTitle::InitAppFromHome);
}

///////////////////////////////////////////////////////////
//	メイン

void appHome::Main()
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

void appHome::_PreEvent()
{
	//	プロセス更新
	_UpdateProcess();

	//	更新
	BackGround.Update();
	SectionName.Update();
	Record.Update();
	Help.Updata();
	Return.Update();
	FarmList.Update();

	//	（メインプロセス以外では処理しない）
	if(nProcess!=PROCESS_MAIN) return;

	//	イベント処理
	if(_FarmSelect())	return;
	if(_PageButton())	return;
	if(_ReturnButton()) return;
}

///////////////////////////////////////////////////////////
//	プロセス更新

void appHome::_UpdateProcess()
{
	bool	a,b,c,d,e;

	switch(nProcess)
	{
	case PROCESS_LOADHOME:

		SectionName.ResetSectionName();
		FarmList.ResetFarmList();
		Record.ResetRecord();
		Help.ResetHelp();
		Return.ResetReturn();

		nProcess=PROCESS_WINDOWCALL;

		break;

	case PROCESS_WINDOWCALL:

		a=FarmList.IsEndEntrance();
		b=Record.IsEndEntrance();
		c=SectionName.IsEndEntrance();
		d=Help.IsEndEntrance();
		e=Return.IsEndEntrance();
		if(!a || !b || !c || !d || !e) break;

		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	ファーム選択

bool appHome::_FarmSelect()
{
	libSound	ls;
	int	mx,my;
	int	s;

	//	カーソル位置取得
	mos.GetPos(&mx,&my);

	//	選択取得
	s=FarmList.IsFarm(mx,my);
	if(s==0) return false;

	//	マウス押下取得
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	選択
	ls.PlaySound(6);
	AppFarm.SetFarmNo(s);
	SetActiveApp(this,(FPAPPFUNC)appHome::FinalAppToFarm);

	return true;
}

///////////////////////////////////////////////////////////
//	ページめくり

bool appHome::_PageButton()
{
	libSound	ls;
	int	mx,my;
	int	p;

	//	カーソル位置取得
	mos.GetPos(&mx,&my);

	//	ボタン取得
	p=FarmList.IsButton(mx,my);
	if(p==0) return false;

	//	マウス押下取得
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	ページめくり
	ls.PlaySound(5);
	FarmList.AddPage(p);

	return true;
}

///////////////////////////////////////////////////////////
//	タイトルに戻る

bool appHome::_ReturnButton()
{
	libSound	ls;
	int	mx,my;

	//	カーソル位置取得
	mos.GetPos(&mx,&my);

	//	検索
	if(!Return.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	タイトルに戻る
	ls.PlaySound(7);
	SetActiveApp(this,(FPAPPFUNC)appHome::FinalAppToTitle);

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void appHome::_Show()
{
	int	mx,my;

	//	カーソル位置取得
	mos.GetPos(&mx,&my);

	//	背景表示
	BackGround.Show();

	//	セクション名表示
	SectionName.Show();

	//	ファームリスト表示
	if(nProcess==PROCESS_MAIN) FarmList.Show(mx,my);
	else					   FarmList.Show(-1,-1);

	//	左側表示
	Record.Show();
	Help.Show();

	//	戻るボタン表示
	if(nProcess==PROCESS_MAIN) Return.Show(mx,my);
	else					   Return.Show(-1,-1);

	//	マウスカーソル表示
	mos.Show();

	//	画面更新
	ms.Refresh();
}
