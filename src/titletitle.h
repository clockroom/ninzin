//
//	�^�C�g���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/08/30
//

#ifndef _TITLETITLE_H_
#define _TITLETITLE_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class titleTitle;

///////////////////////////////////////////////////////////
//	�N���X

class titleTitle
{
	public:
		void	CreateTitle();
		void	ReleaseTitle();
		void	ResetTitleTitleCall();
		void	ResetTitleMain();

		void	SetPos(int,int);

		bool	IsEndEntrance();

		void	Update();
		void	Show();

	private:
		afBitmap	BmpTitle;
		afPattern	PatTitle;
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_TITLETITLE_H_
