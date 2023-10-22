//
//	ヘルプクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/17
//	Last  Edition 2001/09/12
//

#ifndef _FARMHELP_H_
#define _FARMHELP_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class farmHelp;

///////////////////////////////////////////////////////////
//	クラス

class farmHelp
{
	public:
		void	CreateHelp();
		void	ReleaseHelp();

		void	SetPos(int,int);

		bool	IsRequestAutoHelp(int);

		void	Open(int);
		void	Close();
		void	Show();

	private:
		void	_CreateHelpBitmap(int);

		afBitmap	BmpHelp;
		int		PosX,PosY;
		int		nHelp;
		bool	fShow;
};

#endif	//	_FARMHELP_H_
