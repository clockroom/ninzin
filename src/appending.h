//
//	�G���f�B���O�A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/16
//	Last  Edition 2001/09/23
//

#ifndef _APPENDING_H_
#define _APPENDING_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class appEnding;

///////////////////////////////////////////////////////////
//	�N���X

class appEnding:public afApp
{
	public:
		appEnding();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	StaffRoll();
		void	DrawObject();

	private:
		afOscillator	OscFrmLim;

		afBitmap	BmpMsg1;
		afBitmap	BmpMsg2;
		afBitmap	BmpMsg3;
		afBitmap	BmpStaff;

		bool	fRankA;
		int		cProg;
};

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ��錾

extern appEnding AppEnding;

#endif	//	_APPENDING_H_
