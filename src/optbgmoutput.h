//
//	�a�f�l�����{�^���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

#ifndef _OPTBGMOUTPUT_H_
#define _OPTBGMOUTPUT_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class optBGMOutput;

///////////////////////////////////////////////////////////
//	�N���X

class optBGMOutput
{
	public:
		void	CreateBGMOutput();
		void	ReleaseBGMOutput();

		void	SetPos(int,int);
		void	SetBGMOutput(bool);
		void	SetBGMOutput();

		bool	GetBGMOutput();
		bool	IsButton(int,int);

		void	Show(int,int);

	private:
		int		PosX,PosY;
		bool	fDirectMusic;
};

#endif	//	_OPTBGMOUTPUT_H_
