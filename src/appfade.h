//
//	フェードアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/23
//

#ifndef _APPFADE_H_
#define _APPFADE_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	定数定義

#define	AF_FADE_NONE		0
#define AF_FADE_BLACKOUT	1
#define AF_FADE_BLACKIN		2
#define AF_FADE_WHITEOUT	3
#define AF_FADE_WHITEIN		4

///////////////////////////////////////////////////////////
//	クラス宣言

class appFade;

///////////////////////////////////////////////////////////
//	クラス

class appFade:public afApp
{
	public:
		appFade();

		void	InitApp();
		void	FinalApp();
		void	Main();

		void	CallFade(int,int,afApp*,FPAPPFUNC);

	private:
		void	_FadeNone();
		void	_FadeBlackOut();
		void	_FadeBlackIn();
		void	_FadeWhiteOut();
		void	_FadeWhiteIn();

	private:
		afOscillator	OscFrmLim;
		afBitmap		BmpScreen;

		afApp		*pApp;
		FPAPPFUNC	fpFunc;

		int	nFade;
		int	Frame;
		int	cProg;
};

///////////////////////////////////////////////////////////
//	グローバル変数宣言

extern appFade AppFade;

#endif	//	_APPFADE_H_
