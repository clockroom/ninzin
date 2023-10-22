//
//	メーカロゴアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

#ifndef _APPLOGO_H_
#define _APPLOGO_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class appLogo;

///////////////////////////////////////////////////////////
//	クラス

class appLogo:public afApp
{
	public:
		appLogo();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	_Show();

	private:
		afOscillator	OscFrmLim;
		afBitmap		BmpLogo;
		int				cProg;
};

///////////////////////////////////////////////////////////
//	グローバル変数宣言

extern appLogo AppLogo;

#endif	//	_APPLOGO_H_
