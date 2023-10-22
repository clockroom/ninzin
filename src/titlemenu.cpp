//
//	メニュークラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/05
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "titlemenu.h"

///////////////////////////////////////////////////////////
//	定数定義

#define USELESSMENU	2000
#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	作成

void titleMenu::CreateMenu()
{
	//	その他初期化
	PosX=0;
	PosY=0;
	cProg=USELESSMENU;
}

void titleMenu::ReleaseMenu()
{
}

///////////////////////////////////////////////////////////
//	リセット

void titleMenu::ResetMenuMenuCall()
{
	cProg=-1;
}

void titleMenu::ResetMenuMain()
{
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	設定

void titleMenu::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

bool titleMenu::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

int titleMenu::IsMenu(int mx,int my)
{
	if(PosX+12<=mx && mx<PosX+180 &&
	   PosY+ 6<=my && my<PosY+28)	return TM_MENU_START;
	if(PosX+38<=mx && mx<PosX+156 &&
	   PosY+42<=my && my<PosY+64)	return TM_MENU_OPTION;
	if(PosX+12<=mx && mx<PosX+181 &&
	   PosY+78<=my && my<PosY+101)	return TM_MENU_END;

	return TM_MENU_NONE;
}

///////////////////////////////////////////////////////////
//	更新

void titleMenu::Update()
{
	if(cProg==USELESSMENU) return;
	if(cProg==ENDENTRANCE) return;
	if(++cProg<18) return;
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void titleMenu::Show(int mx,int my)
{
	libFont	lf;
	int		x,n;

	if(cProg==USELESSMENU) return;
	if(cProg<0) cProg=0;

	//	過渡表示
	if(0 FROMTO(cProg) 18)
	{
		x=1024>>cProg;
		lf.PutFont(PosX+x,PosY,"26ゲームスタート0");
		x=8192>>cProg;
		lf.PutFont(PosX+x,PosY+36,"26オプション0");
		x=65536>>cProg;
		lf.PutFont(PosX+x,PosY+72,"26ゲームをやめる0");
		return;
	}

	//	定常表示
	n=IsMenu(mx,my);
	if(n!=TM_MENU_START)  lf.PutFont(PosX,PosY,"26ゲームスタート0");
	else				  lf.PutFont(PosX,PosY,"26ゲームスタート1");
	if(n!=TM_MENU_OPTION) lf.PutFont(PosX,PosY+36,"26オプション0");
	else				  lf.PutFont(PosX,PosY+36,"26オプション1");
	if(n!=TM_MENU_END)	  lf.PutFont(PosX,PosY+72,"26ゲームをやめる0");
	else				  lf.PutFont(PosX,PosY+72,"26ゲームをやめる1");
}
