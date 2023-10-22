//
//	オプションアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libsound.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "appfade.h"
#include "apptitle.h"
#include "appoption.h"

///////////////////////////////////////////////////////////
//	グローバル変数

appOption AppOption;

///////////////////////////////////////////////////////////
//	構築

appOption::appOption():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	初期化

void appOption::InitApp()
{
	libCursor	lc;

	//	ライブラリ初期化
	libFont::InitLibrary(16);
	libFont::InitLibrary(23);
	libFont::InitLibrary(24);
	libFont::InitLibrary(25);
	libSound::InitLibrary();
	libSound::InitLibrary(1,3);
	libSound::InitLibrary(2,1);
	libSound::InitLibrary(3,1);
	libSound::InitLibrary(4,1);
	libSound::InitLibrary(11,1);
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	マウス初期化
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	オプション読み込み
	Option.LoadOption();

	//	セクション名初期化
	SectionName.CreateSectionName();
	SectionName.SetPos(32,0+40);

	//	ＢＧＭ方式初期化
	BGMOutput.CreateBGMOutput();
	BGMOutput.SetPos(64,80+40);
	BGMOutput.SetBGMOutput(Option.GetBGMOutput());

	//	ＢＧＭ音量初期化
	BGMVolume.CreateBGMVolume();
	BGMVolume.SetPos(64,128+40);
	BGMVolume.SetVolume(Option.GetBGMVolume());
	BGMVolume.SetEnable(BGMOutput.GetBGMOutput());

	//	効果音音量初期化
	SEVolume.CreateSEVolume();
	SEVolume.SetPos(64,184+40);
	SEVolume.SetVolume(Option.GetSEVolume());

	//	操作ボタン初期化
	Mouse.CreateMouse();
	Mouse.SetPos(64,248+40);
	Mouse.SetTurnLR(Option.GetTurnLR());

	//	記録削除ボタン初期化
	DelRecord.CreateDelRecord();
	DelRecord.SetPos(64,288+40);
	DelRecord.SetDelCount(3);

	//	戻るボタン初期化
	Return.CreateReturn();
	Return.SetPos(64,364+40);

	//	画面構築
	ms.ClearWhite();
	SectionName.Show();
	BGMOutput.Show(-1,-1);
	BGMVolume.Show();
	SEVolume.Show();
	Mouse.Show(-1,-1);
	DelRecord.Show(-1,-1);
	Return.Show(-1,-1);

	//	フェードイン
	AppFade.CallFade(AF_FADE_WHITEIN,8,this,(FPAPPFUNC)appOption::Main);
}

void appOption::FinalApp()
{
	//	オプション書き込み
	Option.SetBGMOutput(BGMOutput.GetBGMOutput());
	Option.SetBGMVolume(BGMVolume.GetVolume());
	Option.SetSEVolume(SEVolume.GetVolume());
	Option.SetTurnLR(Mouse.GetTureLR());
	Option.SaveOption();

	//	ライブラリ解放
	libFont::FinalLiblary();
	libSound::FinalLibrary();
	libCursor::FinalLibrary();
	libCarrot::FinalLibrary();

	//	オブジェクト解放
	SectionName.ReleaseSectionName();
	BGMOutput.ReleaseBGMOutput();
	BGMVolume.ReleaseBGMVolume();
	SEVolume.ReleaseSEVolume();
	Mouse.ReleaseMouse();
	DelRecord.ReleaseDelRecord();
	Return.ReleaseReturn();

	//	フェードアウト
	AppFade.CallFade(AF_FADE_WHITEOUT,8,&AppTitle,(FPAPPFUNC)appTitle::InitAppFromOption);
}

///////////////////////////////////////////////////////////
//	メイン

void appOption::Main()
{
	//	フレームリミッタ
	if(!OscFrmLim) return;

	//	マウス更新
	mos.UpdateKey();

	//	前置イベント
	_PreEvent();

	//	表示
	_Show();
}

///////////////////////////////////////////////////////////
//	前置イベント

void appOption::_PreEvent()
{
	if(_SelectBGMOutput()) return;
	if(_SelectBGMVolume()) return;
	if(_SelectSEVolume())  return;
	if(_SelectMouse())	   return;
	if(_DelRecordButton()) return;
	if(_ReturnButton())	   return;
}

///////////////////////////////////////////////////////////
//	ＢＧＭ方式設定

bool appOption::_SelectBGMOutput()
{
	libSound	ls;
	int	mx,my;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	検索
	if(!BGMOutput.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL)	   return false;

	//	操作ボタン設定
	BGMOutput.SetBGMOutput();
	BGMVolume.SetEnable(BGMOutput.GetBGMOutput());
	ls.PlaySound(11);

	return true;
}

///////////////////////////////////////////////////////////
//	ＢＧＭ音量設定

bool appOption::_SelectBGMVolume()
{
	libSound	ls;
	int	mx,my;
	int	ov,nv;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	ボリューム取得
	ov=BGMVolume.GetVolume();
	nv=BGMVolume.IsVolume(mx,my);

	if(nv==OB_VOLUME_NONE) return false;
	if(nv==ov && mos.GetKeyL()!=KEY_PUSH) return false;
	if(mos.GetKeyL()==KEY_FREE) return false;

	//	ボリューム設定
	BGMVolume.SetVolume(nv);
	afMusic2::SetMasterVolume(nv);
	ls.PlaySound(1);

	return true;
}

///////////////////////////////////////////////////////////
//	効果音音量設定

bool appOption::_SelectSEVolume()
{
	libSound	ls;
	int	mx,my;
	int	ov,nv;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	ボリューム取得
	ov=SEVolume.GetVolume();
	nv=SEVolume.IsVolume(mx,my);

	if(nv==OS_VOLUME_NONE) return false;
	if(nv==ov && mos.GetKeyL()!=KEY_PUSH) return false;
	if(mos.GetKeyL()==KEY_FREE) return false;

	//	ボリューム設定
	SEVolume.SetVolume(nv);
	afSound::SetMasterVolume(nv);
	ls.PlaySound(1);

	return true;
}

///////////////////////////////////////////////////////////
//	操作ボタン設定

bool appOption::_SelectMouse()
{
	libSound	ls;
	int	mx,my;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	検索
	if(!Mouse.IsButton(mx,my))	return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;

	//	操作ボタン設定
	Mouse.SetTurnLR();
	ls.PlaySound(11);

	return true;
}

///////////////////////////////////////////////////////////
//	記録削除

bool appOption::_DelRecordButton()
{
	libSound	ls;
	int		mx,my;
	char	str[1024];

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	検索
	if(!DelRecord.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL)	   return false;
	mos.InvalidateKeyL();

	//	音声再生
	switch(DelRecord.GetDelCount())
	{
	case 3:ls.PlaySound(2);break;
	case 2:ls.PlaySound(3);break;
	case 1:ls.PlaySound(4);break;
	}

	//	削除
	DelRecord.AddDelCount(-1);
	if(!DelRecord.IsDelete()) return true;

	GetFullPathFileName(str,"record.bin");
	remove(str);

	return true;
}

///////////////////////////////////////////////////////////
//	タイトルに戻る

bool appOption::_ReturnButton()
{
	libSound	ls;
	int	mx,my;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	検索
	if(!Return.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	タイトルに戻る
	ls.PlaySound(7);
	SetActiveApp(this,APP_FINAL);

	return true;
}

///////////////////////////////////////////////////////////
//	表示

void appOption::_Show()
{
	int	mx,my;

	//	マウス位置取得
	mos.GetPos(&mx,&my);

	//	画面消去
	ms.ClearWhite();

	//	セクション名表示
	SectionName.Show();

	//	設定表示
	BGMOutput.Show(mx,my);
	BGMVolume.Show();
	SEVolume.Show();
	Mouse.Show(mx,my);
	DelRecord.Show(mx,my);
	Return.Show(mx,my);

	//	マウスカーソル表示
	mos.Show();

	//	画面更新
	ms.Refresh();
}
