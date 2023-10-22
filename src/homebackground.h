//
//	�w�i�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/28
//	Last  Edition 2001/09/02
//

#ifndef _HOMEBACKGROUND_H_
#define _HOMEBACKGROUND_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class homeBackGround;

///////////////////////////////////////////////////////////
//	�N���X

class homeBackGround
{
	public:
		void	CreateBackGround();
		void	ReleaseBackGround();

		void	Update();
		void	Show();

	private:
		afBitmap	BmpBackGround;
		afPattern	PatBackGround;

	private:
		int	cProg;
};

#endif	//	_HOMEBACKGROUND_H_
