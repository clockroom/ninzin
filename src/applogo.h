//
//	���[�J���S�A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

#ifndef _APPLOGO_H_
#define _APPLOGO_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class appLogo;

///////////////////////////////////////////////////////////
//	�N���X

class appLogo:public afApp
{
	public:
		appLogo();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	_Show();

	private:
		afOscillator	OscFrmLim;
		afBitmap		BmpLogo;
		int				cProg;
};

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ��錾

extern appLogo AppLogo;

#endif	//	_APPLOGO_H_
