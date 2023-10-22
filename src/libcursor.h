//
//	�J�[�\�����C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/08/21
//

#ifndef _LIBCURSOR_H_
#define _LIBCURSOR_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class libCursor;

///////////////////////////////////////////////////////////
//	�N���X

class libCursor
{
	public:
		static void	InitLibrary();
		static void	FinalLibrary();

		void	ProvideMouseCursor(afMouse*,int);

		afPattern	&operator[](int);

	private:
		static afBitmap 	BmpCursor;
		static afPattern	dPatCursor[];
};

#endif	//	_LIBCURSOR_H_
