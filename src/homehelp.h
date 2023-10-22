//
//	ヘルプクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/02
//

#ifndef _HOMEHELP_H_
#define _HOMEHELP_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class homeHelp;

///////////////////////////////////////////////////////////
//	クラス

class homeHelp
{
	public:
		void	CreateHelp();
		void	ReleaseHelp();
		void	ResetHelp();

		void	SetPos(int,int);

		bool	IsEndEntrance();

		void	Updata();
		void	Show();

	private:
		void	_CreateHelpBitmap();

	private:
		afBitmap	BmpHelp;
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_HOMEHELP_H_
