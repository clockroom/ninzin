//
//	ウィンドウライブラリ ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/28
//	Last  Edition 2001/08/28
//

#ifndef _LIBWINDOW_H_
#define _LIBWINDOW_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class libWindow;

///////////////////////////////////////////////////////////
//	クラス

class libWindow
{
	public:
		static void	InitLibrary();
		static void	FinalLibrary();

		void	PutWindow(int,int,int,int);
		void	PutWindowWithEdge(int,int,int,int);

	private:
		static afBitmap		BmpMap;
		static afPattern	dPatMap[];
};

#endif	//	_LIBWINDOW_H_
