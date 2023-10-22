//
//	ボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/12
//	Last  Edition 2001/09/13
//

#ifndef _FARMBUTTON_H_
#define _FARMBUTTON_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	定数定義

#define FB_BTN_NONE		0
#define FB_BTN_EXIT		1
#define FB_BTN_RETURN	2
#define FB_BTN_HELP		3

#define	FB_PAT_BUTTON	6

///////////////////////////////////////////////////////////
//	クラス宣言

class farmButton;

///////////////////////////////////////////////////////////
//	クラス

class farmButton
{
	public:
		void	CreateButton();
		void	ReleaseButton();

		void	SetPos(int,int);

		int		IsButton(int,int);

		void	Show(int,int,bool);

	private:
		afBitmap	BmpButton;
		afPattern	dPatButton[FB_PAT_BUTTON];
		int	PosX,PosY;
};

#endif	//	_FARMBUTTON_H_
