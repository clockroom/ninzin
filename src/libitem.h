//
//	項目ライブラリ by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/09
//	Last  Edition 2001/08/21
//

#ifndef _LIBITEM_H_
#define _LIBITEM_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class libItem;

///////////////////////////////////////////////////////////
//	クラス

class libItem
{
	public:
		static void	InitLibrary();
		static void	FinalLibrary();

		void	PutItem(int,int,int,int);

	private:
		static afBitmap		BmpMap;
		static afPattern	dPatMap[];
};

#endif	//	_LIBITEM_H_
