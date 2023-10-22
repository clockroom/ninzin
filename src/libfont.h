//
//	フォントライブラリ by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/09/20
//

#ifndef _LIBFONT_H_
#define _LIBFONT_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class libFont;

///////////////////////////////////////////////////////////
//	クラス

class libFont
{
	public:
		static void	InitLibrary();
		static void	InitLibrary(int);
		static void FinalLiblary();

		void	PutFont(int,int,const char*);
		void	BlendFont(int,int,int,const char*);
		void	BrightFont(int,int,int,const char*);

	private:
		void	_PutFont11(afPattern*,int,int,int,const char*);
		void	_PutFont16(int,int,int,const char*);
		void	_PutFont17(int,int,int,const char*);
		void	_PutFont21(int,int,int,const char*);
		void	_PutFont22(int,int,int,const char*);
		void	_PutFont23(int,int,int,const char*);
		void	_PutFont24(int,int,int,const char*);
		void	_PutFont25(int,int,int,const char*);
		void	_PutFont26(int,int,int,const char*);
		void	_PutFont27(int,int,int,const char*);
		void	_PutFont28(int,int,int,const char*);

	private:
		static afBitmap		BmpFont11;
		static afBitmap		BmpFont16;
		static afBitmap		BmpFont17;
		static afBitmap		BmpFont21;
		static afBitmap		BmpFont22;
		static afBitmap		BmpFont23;
		static afBitmap		BmpFont24;
		static afBitmap		BmpFont25;
		static afBitmap		BmpFont26;
		static afBitmap		BmpFont27;
		static afBitmap		BmpFont28;

		static afPattern	dPatFont11[];
		static afPattern	dPatFont12[];
		static afPattern	dPatFont13[];
		static afPattern	dPatFont16[];
		static afPattern	dPatFont17[];
		static afPattern	dPatFont21[];
		static afPattern	dPatFont22[];
		static afPattern	dPatFont23[];
		static afPattern	dPatFont24[];
		static afPattern	dPatFont25[];
		static afPattern	dPatFont26[];
		static afPattern	dPatFont27[];
		static afPattern	dPatFont28[];
};

#endif	//	_LIBFONT_H_
