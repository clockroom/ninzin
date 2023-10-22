//
//	�������C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/06
//	Last  Edition 2001/09/18
//

#ifndef _LIBSOUND_H_
#define _LIBSOUND_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class libSound;

///////////////////////////////////////////////////////////
//	�N���X

class libSound
{
	public:
		static void	InitLibrary();
		static void	InitLibrary(int,int);
		static void	FinalLibrary();

		void	PlaySound(int);

	private:
		static afSound	dSndSE[];
};

#endif	//	_LIBSOUND_H_
