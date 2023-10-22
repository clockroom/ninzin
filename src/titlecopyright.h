//
//	�R�s�[���C�g�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/08/30
//

#ifndef _TITLECOPYRIGHT_H_
#define _TITLECOPYRIGHT_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class titleCopyright;

///////////////////////////////////////////////////////////
//	�N���X

class titleCopyright
{
	public:
		void	CreateCopyright();
		void	ReleaseCopyright();
		void	ResetCopyrightMenuCall();
		void	ResetCopyrightMain();

		void	SetPos(int,int);

		bool	IsEndEntrance();

		void	Update();
		void	Show();

	private:
		afBitmap	BmpCopyright;
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_TITLECOPYRIGHT_H_
