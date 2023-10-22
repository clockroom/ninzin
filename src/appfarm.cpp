//
//	ファームアプリケーション by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "common.h"
#include "libfont.h"
#include "libitem.h"
#include "libmusic.h"
#include "libsound.h"
#include "libwindow.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "fileoption.h"
#include "filefarmmap.h"
#include "fileplaydata.h"
#include "appfade.h"
#include "appfarm.h"
#include "apphome.h"
#include "appending.h"
#include "farmflycarrot.h"

///////////////////////////////////////////////////////////
//	定数定義

#define PROCESS_LOADFARM	 0
#define PROCESS_STARTSIGN	10
#define	PROCESS_MAIN		20
#define PROCESS_CLEARSIGN	30
#define PROCESS_FAILURESIGN	40
#define PROCESS_HELP		50

///////////////////////////////////////////////////////////
//	グローバル変数

appFarm AppFarm;

///////////////////////////////////////////////////////////
//	構築

appFarm::appFarm():OscFrmLim(20,5)
{
}

appFarm::~appFarm()
{
	farmFlyCarrot::DestroyAll();
}

///////////////////////////////////////////////////////////
//	初期化

void appFarm::InitApp()
{
	libMusic		lm;
	libCursor		lc;
	fileFarmMap		ffm;
	fileOption		fo;
	filePlayData	fpd;
	int		bw,bt;
	int		mn;

	//	ライブラリ初期化
	libFont::InitLibrary();
	libFont::InitLibrary(16);
	libItem::InitLibrary();
	libMusic::InitLibrary(3);
	libMusic::InitLibrary(4);
	libSound::InitLibrary();
	libSound::InitLibrary(8,1);
	libSound::InitLibrary(9,1);
	libSound::InitLibrary(10,2);
	libSound::InitLibrary(11,2);
	libSound::InitLibrary(12,1);
	libSound::InitLibrary(13,2);
	libSound::InitLibrary(14,1);
	libSound::InitLibrary(17,1);
	libSound::InitLibrary(18,1);
	libSound::InitLibrary(19,1);
	libWindow::InitLibrary();
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	マウス初期化
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	マップ初期化
	Map.CreateMap();
	Map.SetPos(48,48);
	Frame.CreateFrame();
	Frame.SetPos(0,0);

	//	ステータス初期化
	State.CreateState();
	State.SetPos(480,0);
	Count.CreateCount();
	Count.SetPos(504,72);
	Button.CreateButton();
	Button.SetPos(504,440);

	//	サイン初期化
	StartSign.CreateStartSign();
	StartSign.SetPos(132,214);
	ClearSign.CreateClearSign();
	ClearSign.SetPos(140,214);
	FailureSign.CreateFailureSign();
	FailureSign.SetPos(152,214);

	//	リクエスト初期化
	ReqCarrot.CreateReqCarrot();
	ReqCarrot.SetPos(8,440);

	//	ヘルプ初期化
	Help.CreateHelp();
	Help.SetPos(48,96);

	//	飛行ニンジン初期化
	farmFlyCarrot::InitFlyCarrot(&Map,&Count);

	//	変数初期化
	fo.LoadOption();
	fTurnLR=fo.GetTurnLR();
	nProcess=PROCESS_LOADFARM;

	//	曲再生
	ffm.LoadFarmMap(FarmNo);
	mn=ffm.GetMusic();
	if(mn==0) lm.StopMusic();
	else	  lm.PlayMusic(mn);
	Sleep(2000);

	//	フェードイン用設定
	fpd.LoadPlayData();
	fpd.GetFarmRecord(NULL,&bw,&bt,FarmNo);
	State.SetFarmNo(FarmNo);
	State.SetBestRecord(bw,bt);

	//	フェードイン用画面構築
	Map.Show(-1,-1,FM_SC_NONE);
	Frame.Show();
	State.Show();
	Count.Show();
	Button.Show(-1,-1,false);

	//	フェードイン
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appFarm::Main);
}

void appFarm::FinalApp()
{
	//	オブジェクト解放
	Map.ReleaseMap();
	Frame.ReleaseFrame();
	State.ReleaseState();
	Count.ReleaseCount();
	Button.ReleaseButton();
	StartSign.ReleaseStartSign();
	ClearSign.ReleaseClearSign();
	FailureSign.ReleaseFailureSign();
	ReqCarrot.ReleaseReqCarrot();
	Help.ReleaseHelp();

	//	飛行ニンジン解放
	farmFlyCarrot::FinalFlyCarrot();

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

void appFarm::FinalAppToHome()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppHome,(FPAPPFUNC)appHome::InitApp);
}

void appFarm::FinalAppToEnding()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppEnding,(FPAPPFUNC)appEnding::InitApp);
}

///////////////////////////////////////////////////////////
//	メイン

void appFarm::Main()
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

void appFarm::_PreEvent()
{
	libCursor	lc;

	//	プロセス更新
	_UpdateProcess();

	//	オブジェクト更新
	State.Update();
	Map.Update();
	StartSign.Update();
	ClearSign.Update();
	FailureSign.Update();
	ReqCarrot.Update();
	farmFlyCarrot::UpdateAll();

	//	マウスカーソル設定
	lc.ProvideMouseCursor(&mos,0);

	//	ボタン
	if(_Button()) return;

	//	(メインプロセス以外では処理しない)
	if(nProcess!=PROCESS_MAIN) return;

	//	行動
	if(_WaterCarrot()) return;
	if(_PullCarrot())  return;
}

///////////////////////////////////////////////////////////
//	プロセス更新

void appFarm::_UpdateProcess()
{
	libSound		ls;
	filePlayData	fpd;
	bool	a,b,c,d,e;

	switch(nProcess)
	{
	case PROCESS_LOADFARM:

		_LoadFarm();
		LastPosX=-1;
		LastPosY=-1;
		nProcess=PROCESS_STARTSIGN;

		break;

	case PROCESS_STARTSIGN:

		a=Map.IsEndPlant();
		b=StartSign.IsEndSign();
		c=ReqCarrot.IsEndRequest();
		d=farmFlyCarrot::IsEndFlyReqCarrot();
		e=State.IsEndCount();
		if(!a || !b || !c || !d || !e) break;

		State.ResetStateMain();
		nProcess=PROCESS_MAIN;

		break;

	case PROCESS_MAIN:

		//	初回読み込み
		if(fFirstLoad)
		{
			fFirstLoad=false;

			//	読み込み形跡記録
			fpd.LoadPlayData();
			fpd.SetFarmRecord(FarmNo,FP_NOCLEAR,FP_NOCLEAR);
			fpd.SavePlayData();

			//	自動ヘルプ起動
			if(!Help.IsRequestAutoHelp(FarmNo)) break;
			Help.Open(FarmNo);
			State.PauseState();
			mos.InvalidateKeyL();

			nProcess=PROCESS_HELP;

			break;
		}

		//	クリア
		if(Count.IsClear() && !MODE_EDIT)
		{
			ls.PlaySound(14);
			ClearSign.ResetClearSign();
			State.ResetStateNone();
			nProcess=PROCESS_CLEARSIGN;
			break;
		}

		//	失敗
		if(Count.IsFailure() && !MODE_EDIT)
		{
			ls.PlaySound(12);
			FailureSign.ResetFailureSign();
			State.ResetStateNone();
			farmFlyCarrot::DestroyAll();
			mos.InvalidateKeyL();
			nProcess=PROCESS_FAILURESIGN;
			break;
		}

		break;

	case PROCESS_CLEARSIGN:

		a=ClearSign.IsEndSign();
		if(!a) break;

		_SaveFarm();

		//	エンディングへ
		if(FarmNo==MAX_FARM && !fRetry)
		{
			SetActiveApp(this,(FPAPPFUNC)appFarm::FinalAppToEnding);
			break;
		}

		if(!fRetry) FarmNo++;
		nProcess=PROCESS_LOADFARM;

		break;

	case PROCESS_FAILURESIGN:

		if(mos.GetKeyL()!=KEY_PULL)
		{
			a=FailureSign.IsEndSign();
			if(!a) break;
		}
		else
		{
			mos.InvalidateKeyL();
			FailureSign.ResetFailureSignNone();
		}

		nProcess=PROCESS_LOADFARM;

		break;

	case PROCESS_HELP:

		if(mos.GetKeyL()!=KEY_PULL) break;
		mos.InvalidateKeyL();

		Help.Close();
		State.RestartState();
		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	ステージロード

void appFarm::_LoadFarm()
{
	libMusic		lm;
	fileFarmMap		ffm;
	filePlayData	fpd;
	BYTE	(*pm)[8];
	BYTE	*pr;
	int		gw,bw,bt;
	int		mn;

	//	マップ読み込み
	ffm.LoadFarmMap(FarmNo);
	pm=ffm.GetMap();
	pr=ffm.GetRequest();

	//	レコード読み込み
	fpd.LoadPlayData();
	fpd.GetFarmRecord(&gw,&bw,&bt,FarmNo);

	//	初回読み込み
	if(bw==FP_FIRSTLOAD) fFirstLoad=true;
	else				 fFirstLoad=false;
	if(bw==FP_FIRSTLOAD || bw==FP_NOCLEAR) fRetry=false;
	else fRetry=true;

	//	曲再生
	mn=ffm.GetMusic();
	if(mn==0) lm.StopMusic();
	else	  lm.PlayMusic(mn);

	//	カウントクリア
	Count.ClearCount();

	//	ステータス設定
	State.SetFarmNo(FarmNo);
	State.SetGoodWater(gw);
	State.SetBestRecord(bw,bt);
	State.ResetStateStartSign();

	//	マップ設定
	Map.SetMap(pm);
	Map.ResetMap();

	//	リクエスト設定
	ReqCarrot.SetReqCarrot(pr);
	ReqCarrot.ResetReqCarrot();

	//	開始サイン設定
	StartSign.SetFarmNo(FarmNo);
	StartSign.ResetStartSign();
}

///////////////////////////////////////////////////////////
//	ステージセーブ

void appFarm::_SaveFarm()
{
	filePlayData	fpd;
	int	nw,nt,bw,bt;

	//	レコード取得
	State.GetRecord(&nw,&nt);
	State.GetBestRecord(&bw,&bt);

	//	レコード設定
	if(nw<bw)
	{
		bw=nw;
		bt=nt;
	}
	else if(nw==bw && nt<bt)
	{
		bw=nw;
		bt=nt;
	}

	//	レコード書き込み
	fpd.LoadPlayData();
	fpd.SetFarmRecord(FarmNo,bw,bt);
	fpd.SavePlayData();
}

///////////////////////////////////////////////////////////
//	水やり

bool appFarm::_WaterCarrot()
{
	libSound	ls;
	libCursor	lc;
	int	mx,my;
	int	fx,fy;

	mos.GetPos(&mx,&my);
	if(!Map.IsFarm(mx,my)) return false;

	if(!fTurnLR)
	{
		if(mos.GetKeyR()!=KEY_FREE) return false;
		if(mos.GetKeyL()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,1);
		}
		if(mos.GetKeyL()!=KEY_PULL) return false;
		mos.InvalidateKeyL();
	}
	else
	{
		if(mos.GetKeyL()!=KEY_FREE) return false;
		if(mos.GetKeyR()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,1);
		}
		if(mos.GetKeyR()!=KEY_PULL) return false;
		mos.InvalidateKeyR();
	}

	if(!Map.WaterCarrot(mx,my)) return false;
	ls.PlaySound(8);

	Map.GetFarmPos(&fx,&fy,mx,my);
	if(LastPosX!=fx || LastPosY!=fy)
	{
		State.AddWater(1);
		LastPosX=fx;
		LastPosY=fy;
	}
	else
	{
		State.AddWater(-1);
		LastPosX=-1;
		LastPosY=-1;
	}

	return true;
}

///////////////////////////////////////////////////////////
//	収穫

bool appFarm::_PullCarrot()
{
	libSound	ls;
	libCursor	lc;
	BYTE	c;
	int		x,y;

	mos.GetPos(&x,&y);
	if(!Map.IsFarm(x,y)) return false;

	if(!fTurnLR)
	{
		if(mos.GetKeyL()!=KEY_FREE) return false;
		if(mos.GetKeyR()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,2);
		}
		if(mos.GetKeyR()!=KEY_PULL) return false;
		mos.InvalidateKeyR();
	}
	else
	{
		if(mos.GetKeyR()!=KEY_FREE) return false;
		if(mos.GetKeyL()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,2);
		}
		if(mos.GetKeyL()!=KEY_PULL) return false;
		mos.InvalidateKeyL();
	}

	c=Map.PullCarrot(x,y);
	if(c&0x08) return false;
	ls.PlaySound(9);

	LastPosX=-1;
	LastPosY=-1;

	//	飛行ニンジン作成
	farmFlyCarrot::CreateFlyPullCarrot(c,x,y);

	return true;
}

///////////////////////////////////////////////////////////
//	ボタン

bool appFarm::_Button()
{
	libSound	ls;
	int	mx,my;
	int	b;

	mos.GetPos(&mx,&my);
	b=Button.IsButton(mx,my);

	if(b==FB_BTN_NONE) return false;
	if(nProcess!=PROCESS_MAIN)
	{
		if(nProcess!=PROCESS_STARTSIGN) return false;
		if(b!=FB_BTN_EXIT)				return false;
	}
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	ボタンごとの処理
	switch(b)
	{
	case FB_BTN_HELP:
		Help.Open(0);
		State.PauseState();
		nProcess=PROCESS_HELP;
		return true;

	case FB_BTN_RETURN:
		nProcess=PROCESS_LOADFARM;
		return true;

	case FB_BTN_EXIT:
		ls.PlaySound(7);
		SetActiveApp(this,(FPAPPFUNC)appFarm::FinalAppToHome);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////
//	表示

void appFarm::_Show()
{
	int	mx,my;
	int	f;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	マップ表示
	f=(mos.GetKeyR()==KEY_FREE)?FM_SC_WATER:FM_SC_PULL;
	f=(mos.GetKeyL()!=KEY_FREE)?FM_SC_WATER:f;
	f=(nProcess!=PROCESS_MAIN )?FM_SC_NONE :f;
	Map.Show(mx,my,f);
	Frame.Show();

	//	ステータス表示
	State.Show();
	Count.Show();
	switch(nProcess)
	{
	case PROCESS_MAIN:	   Button.Show(mx,my,true); break;
	case PROCESS_STARTSIGN:Button.Show(mx,my,false);break;
	default:			   Button.Show(-1,-1,false);break;
	}

	//	リクエスト表示
	ReqCarrot.Show();

	//	飛行ニンジン表示
	farmFlyCarrot::ShowAll();

	//	ヘルプ表示
	Help.Show();

	//	マウスカーソル表示
	if(nProcess==PROCESS_MAIN ||
	   nProcess==PROCESS_STARTSIGN ||
	   nProcess==PROCESS_HELP) mos.Show();

	//	リクエスト表示
	ReqCarrot.ShowFont();

	//	サイン表示
	StartSign.Show();
	ClearSign.Show();
	FailureSign.Show();

	//	画面更新
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	設定

void appFarm::SetFarmNo(int n)
{
	FarmNo=n;
}
