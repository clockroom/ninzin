//
//	ヘルプクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/17
//	Last  Edition 2001/09/16
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "fileoption.h"
#include "farmhelp.h"

///////////////////////////////////////////////////////////
//	作成

void farmHelp::CreateHelp()
{
	PosX=0;
	PosY=0;
	nHelp=0;
	fShow=false;
}

void farmHelp::ReleaseHelp()
{
	BmpHelp.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	ビットマップ作成

void farmHelp::_CreateHelpBitmap(int n)
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	fileOption	fo;
	afScreen	scr;
	afDC		dc;
	char	str[1024];
	char	hand[2][8];
	bool	fturn,fmos;

	//	ビットマップ作成
	BmpHelp.CreateBitmap(384,288);

	//	ウィンドウ作成
	scr.SetWorkScreen(&BmpHelp);
	scr.SetDrawArea(0,0,384,288);
	lw.PutWindow(0,0,384,288);
	lf.PutFont(8,8,"22help");
	li.PutItem(8,40,368,240);
	scr.RestoreWorkScreen();
	scr.SetDrawArea();

	//	ボタン交換取得
	fo.LoadOption();
	fturn=fo.GetTurnLR();
	fmos =(GetSystemMetrics(SM_SWAPBUTTON)==0)?false:true;

	//	ボタン名設定
	if((!fturn && !fmos) || (fturn && fmos))
	{
		strcpy(hand[0],"左");
		strcpy(hand[1],"右");
	}
	else
	{
		strcpy(hand[0],"右");
		strcpy(hand[1],"左");
	}

	//	DC取得
	BmpHelp.GetDC(&dc);

	//	ヘルプ描画
	switch(n)
	{
	case 0:
		dc.Text(15, 48,"■ ルール",16,true,RGB(255,192,192));
		dc.Text(15, 68,"ニンジンに水をあげて色を変えつつ、右の表で要",16,true,RGB(255,255,255));
		dc.Text(15, 88,"求されている通りに収穫してください。",16,true,RGB(255,255,255));
		dc.Text(15,108,"表の見方は",16,true,RGB(255,255,255));
		dc.Text(15,128,"（収穫した数）／（要求された数）  です。",16,true,RGB(255,255,255));
		dc.Text(15,156,"■ 操作方法",16,true,RGB(255,192,192));
		sprintf(str,"%sクリックで水をあげる",hand[0]);
		dc.Text(15,176,str,16,true,RGB(255,255,255));
		sprintf(str,"%sクリックで収穫する",hand[1]);
		dc.Text(15,196,str,16,true,RGB(255,255,255));
		dc.Text(15,224,"＊ 詳しくは付属の取扱説明書をご覧ください",16,true,RGB(255,192,192));
		break;

	case 1:
		dc.Text(15, 48,"ようこそ！不思議なニンジン畑へ",16,true,RGB(255,255,255));
		dc.Text(15, 76,"このゲームは「光の三原色」の混色を原理とした",16,true,RGB(255,255,255));
		dc.Text(15, 96,"色遊びのパズルゲームです。",16,true,RGB(255,255,255));
		dc.Text(15,124,"■ 収穫の練習",16,true,RGB(255,192,192));
		sprintf(str,"ニンジンにカーソルを合わせて%sクリックすると",hand[1]);
		dc.Text(15,144,str,16,true,RGB(255,255,255));
		dc.Text(15,164,"ニンジンを収穫することができます。",16,true,RGB(255,255,255));
		dc.Text(15,184,"この面は収穫だけでクリアできるので、早速収穫",16,true,RGB(255,255,255));
		dc.Text(15,204,"してみましょう。",16,true,RGB(255,255,255));
		break;

	case 2:
		dc.Text(15, 48,"■ 水やりの練習",16,true,RGB(255,192,192));
		sprintf(str,"ニンジンにカーソルを合わせて%sクリックすると",hand[0]);
		dc.Text(15, 68,str,16,true,RGB(255,255,255));
		dc.Text(15, 88,"ニンジンに水をあげることができます。",16,true,RGB(255,255,255));
		dc.Text(15,108,"ニンジンに水をあげると、水をあげたニンジンの",16,true,RGB(255,255,255));
		dc.Text(15,128,"周り（上下左右）のニンジンの色が、水をあげた",16,true,RGB(255,255,255));
		dc.Text(15,148,"ニンジンの色と混ざって変化します。",16,true,RGB(255,255,255));
		dc.Text(15,168,"ニンジンにカーソルを合わせた時に表示される枠",16,true,RGB(255,255,255));
		dc.Text(15,188,"の色は、水をあげた後のニンジンの色です。",16,true,RGB(255,255,255));
		dc.Text(15,208,"この面は、赤いニンジンに１回だけ水をあげた後",16,true,RGB(255,255,255));
		dc.Text(15,228,"に収穫するとクリアできます。",16,true,RGB(255,255,255));
		break;

	case 3:
		dc.Text(15, 48,"■ 色の変化について",16,true,RGB(255,192,192));
		dc.Text(15, 68,"例えば、赤いニンジンに水をあげると、水をあげ",16,true,RGB(255,255,255));
		dc.Text(15, 88,"たニンジンの周りのニンジンの色が赤色と混ざっ",16,true,RGB(255,255,255));
		dc.Text(15,108,"て変化することは前の面でわかりました。",16,true,RGB(255,255,255));
		dc.Text(15,128,"逆に、すでに赤いニンジンに赤色が混ざると、赤",16,true,RGB(255,255,255));
		dc.Text(15,148,"色は抜けてしまいます。",16,true,RGB(255,255,255));
		dc.Text(15,168,"ちなみに、カーソルを畑から遠ざけるとニンジン",16,true,RGB(255,255,255));
		dc.Text(15,188,"の色素成分が表示されます。",16,true,RGB(255,255,255));
		dc.Text(15,208,"この面は、赤いニンジンに１回だけ水をあげた後",16,true,RGB(255,255,255));
		dc.Text(15,228,"に収穫するとクリアできます。",16,true,RGB(255,255,255));
		break;

	case 4:
		dc.Text(15, 48,"■ クリア方法",16,true,RGB(255,192,192));
		dc.Text(15, 68,"右の表で要求されている通りにニンジンを収穫す",16,true,RGB(255,255,255));
		dc.Text(15, 88,"るとクリアです。",16,true,RGB(255,255,255));
		dc.Text(15,108,"表の見方は",16,true,RGB(255,255,255));
		dc.Text(15,128,"（収穫した数）／（要求された数）  です。",16,true,RGB(255,255,255));
		dc.Text(15,148,"この面の場合は、黒・赤・紫色のニンジンをそれ",16,true,RGB(255,255,255));
		dc.Text(15,168,"ぞれ１本ずつ収穫するとクリアです。",16,true,RGB(255,255,255));
		dc.Text(15,188,"収穫した数が要求された数を上回ると即失敗です",16,true,RGB(255,192,192));
		dc.Text(15,208,"ので気を付けてください。",16,true,RGB(255,192,192));
		break;

	case 5:
		dc.Text(15, 48,"■ 目標手数",16,true,RGB(255,192,192));
		dc.Text(15, 68,"右下の“Ｗａｔｅｒ”と表示されている所のさら",16,true,RGB(255,255,255));
		dc.Text(15, 88,"に右にある数字は目標手数です。",16,true,RGB(255,255,255));
		dc.Text(15, 108,"手数とはニンジンに水をあげた回数のことです。",16,true,RGB(255,255,255));
		dc.Text(15, 128,"手数が目標手数を上回っても失敗にはなりません",16,true,RGB(255,255,255));
		dc.Text(15, 148,"が、できるだけ目標手数に近い手数でのクリアを",16,true,RGB(255,255,255));
		dc.Text(15, 168,"目指して頑張ってください。",16,true,RGB(255,255,255));
		dc.Text(15, 188,"なお、ニンジンに水をあげた直後にもう１度同じ",16,true,RGB(255,255,255));
		dc.Text(15, 208,"ニンジンに水をあげると１手だけ戻せます。",16,true,RGB(255,255,255));
		break;

	case 18:
		dc.Text(15, 48,"■ 収穫のタイミング",16,true,RGB(255,192,192));
		dc.Text(15, 68,"収穫は、必ずしも水をあげたあとに一気におこな",16,true,RGB(255,255,255));
		dc.Text(15, 88,"うとは限りません。",16,true,RGB(255,255,255));
		dc.Text(15, 108,"水をあげている最中に収穫しなければならない面",16,true,RGB(255,255,255));
		dc.Text(15, 128,"がこの先いくつも存在します。",16,true,RGB(255,255,255));
		dc.Text(15, 148,"この面はそういうパターンのほんの一例です。",16,true,RGB(255,255,255));
		dc.Text(15, 168,"さあ、どうやって解きますか？",16,true,RGB(255,255,255));
		break;

	case 25:
		dc.Text(15, 48,"■ タイムアタック！！",16,true,RGB(255,192,192));
		dc.Text(15, 68,"畑全体がニンジンで埋めつくされて一見難しそう",16,true,RGB(255,255,255));
		dc.Text(15, 88,"に見えるけど、実はものすごく簡単。",16,true,RGB(255,255,255));
		dc.Text(15, 108,"だって、ひたすら収穫するだけで良いんだから。",16,true,RGB(255,255,255));
		sprintf(str,"この面では疲れた頭をいったん休めてとにかく%s",hand[1]);
		dc.Text(15, 128,str,16,true,RGB(255,255,255));
		dc.Text(15, 148,"クリック、タイムアタックに挑戦だ！",16,true,RGB(255,255,255));
		break;
	}

	//	閉じる方法
	if(!fmos) strcpy(str,"▼ 左クリックでヘルプを閉じる");
	else	  strcpy(str,"▼ 右クリックでヘルプを閉じる");
	dc.Text(136,260,str,16,true,RGB(255,255,255));

	//	DC解放
	BmpHelp.ReleaseDC(&dc);
}

///////////////////////////////////////////////////////////
//	設定

void farmHelp::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool farmHelp::IsRequestAutoHelp(int no)
{
	switch(no)
	{
	case  1:
	case  2:
	case  3:
	case  4:
	case  5:
	case 18:
	case 25:
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////
//	制御

void farmHelp::Open(int n)
{
	libSound	ls;

	_CreateHelpBitmap(n);
	ls.PlaySound(6);
	nHelp=n;
	fShow=true;
}

void farmHelp::Close()
{
	libSound	ls;

	BmpHelp.ReleaseBitmap();
	ls.PlaySound(7);
	fShow=false;
}

///////////////////////////////////////////////////////////
//	表示

void farmHelp::Show()
{
	if(!fShow) return;

	if(BmpHelp.IsLost()) _CreateHelpBitmap(nHelp);
	BmpHelp.Put(PosX,PosY,0,0,384,288);
}
