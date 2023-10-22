//
//	戻るボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/05
//

#ifndef _HOMERETURN_H_
#define _HOMERETURN_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class homeReturn;

///////////////////////////////////////////////////////////
//	クラス

class homeReturn
{
	public:
		void	CreateReturn();
		void	ReleaseReturn();
		void	ResetReturn();

		void	SetPos(int,int);

		bool	IsButton(int,int);
		bool	IsEndEntrance();

		void	Update();
		void	Show(int,int);

	private:
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_HOMERETURN_H_
