//
//	操作ボタンボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/13
//	Last  Edition 2001/09/13
//

#ifndef _OPTMOUSE_H_
#define _OPTMOUSE_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class optMouse;

///////////////////////////////////////////////////////////
//	クラス

class optMouse
{
	public:
		void	CreateMouse();
		void	ReleaseMouse();

		void	SetPos(int,int);
		void	SetTurnLR(bool);
		void	SetTurnLR();

		bool	GetTureLR();
		bool	IsButton(int,int);

		void	Show(int,int);

	private:
		afBitmap	BmpMouse;
		int		PosX,PosY;
		bool	fTurnLR;
};

#endif	//	_OPTMOUSE_H_
