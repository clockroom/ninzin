//
//	不思議なニンジン畑 by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/21
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "main.h"
#include "common.h"
#include "fileoption.h"
#include "workprotect.h"
#include "applogo.h"

///////////////////////////////////////////////////////////
//	アプリケーション設定

static bool fAppName=SetAppName("不思議なニンジン畑");

///////////////////////////////////////////////////////////
//	ファイル関数宣言

static bool _ExitProc();

///////////////////////////////////////////////////////////
//	グローバル変数

afScreen ms;
afMouse  mos;

///////////////////////////////////////////////////////////
//	初期化

bool afInit()
{
	fileOption	fo;
	workProtect	wp;
	afErrorBox	eb;

	//	プロテクト
	if(!wp.Protect() && !MODE_EDIT)
	{
		eb.SetTitle("プロテクト エラー - 不思議なニンジン畑");
		eb.SetMessage("\nデータファイルの構成が不正であるためプロテクトが異常を通知しました。\n\n"
			"次のいずれかの原因が考えられます。\n"
			"１） 何らかの理由により構成ファイルが破損した。\n"
			"２） 実はマップデータの改造を試みたが上手くいかなかった。");
		eb.SetRepair("\n原因１の場合は本ソフトウェアを上書きインストールしてください。\n"
			"原因２の場合は元に戻すか、または頑張ってプロテクトを突破してください。");
		eb.OpenBox();
		return false;
	}

	//	画面作成
	if(!ms.CreateScreen(640,480))
	{
		eb.SetTitle("システム エラー - 不思議なニンジン畑");
		eb.SetMessage("初期化に失敗しました。\n起動できません。");
		eb.OpenBox();
		return false;
	}

	//	サウンドシステム初期化
	fo.LoadOption();
	if(fo.GetDMInit()) afMusic2::InitMusic2();
	afSound::SetSoundQuality(16);

	//	システム設定
	SetExitProc(_ExitProc);

	//	システム起動
	SetActiveApp(&AppLogo,APP_INIT);

	return true;
}

///////////////////////////////////////////////////////////
//	終了プロシージャ

bool _ExitProc()
{
	ClipCursor(NULL);
	return true;
}

///////////////////////////////////////////////////////////
//	メイン

void afMain()
{
	RECT	rc;

	//	カーソル移動範囲設定
	GetClipCursor(&rc);
	if(rc.left !=  2 || rc.top	 !=  2 ||
	   rc.right!=638 || rc.bottom!=478)
	{
		rc.left =  2;	rc.top	 =  2;
		rc.right=638;	rc.bottom=478;
		ClipCursor(&rc);
	}

	//	メイン処理
	CallActiveApp();
}
