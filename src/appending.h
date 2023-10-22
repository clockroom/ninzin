//
//	エンディングアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/16
//	Last  Edition 2001/09/23
//

#ifndef _APPENDING_H_
#define _APPENDING_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class appEnding;

///////////////////////////////////////////////////////////
//	クラス

class appEnding:public afApp
{
	public:
		appEnding();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	StaffRoll();
		void	DrawObject();

	private:
		afOscillator	OscFrmLim;

		afBitmap	BmpMsg1;
		afBitmap	BmpMsg2;
		afBitmap	BmpMsg3;
		afBitmap	BmpStaff;

		bool	fRankA;
		int		cProg;
};

///////////////////////////////////////////////////////////
//	グローバル変数宣言

extern appEnding AppEnding;

#endif	//	_APPENDING_H_
