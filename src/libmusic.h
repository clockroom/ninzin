//
//	���y���C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

#ifndef _LIBMUSIC_H_
#define _LIBMUSIC_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class libMusic;

///////////////////////////////////////////////////////////
//	�N���X

class libMusic
{
	public:
		static void	InitLibrary(int);
		static void	FinalLibrary();

		static void	SetOutputSystem(bool);

		void	PlayMusic(int);
		void	StopMusic();

	private:
		static afMusic	dMsc1BGM[];
		static afMusic2	dMsc2BGM[];
		static bool	fDirectMusic;
};

#endif	//	_LIBMUSIC_H_
