//
//	ニンジンライブラリ by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/10
//	Last  Edition 2001/07/10
//

#ifndef _LIBCARROT_H_
#define _LIBCARROT_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class libCarrot;

///////////////////////////////////////////////////////////
//	クラス

class libCarrot
{
	public:
		static void	InitLibrary();
		static void	FinalLibrary();

		afPattern	&operator[](int);

	private:
		static afBitmap		BmpCarrot;
		static afPattern	dPatCarrot[];
};

#endif	//	_LIBCARROT_H_
