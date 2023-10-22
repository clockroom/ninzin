//
//	���N�G�X�g�j���W���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/08
//	Last  Edition 2001/07/22
//

#ifndef _FARMREQCARROT_H_
#define _FARMREQCARROT_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class farmReqCarrot;

///////////////////////////////////////////////////////////
//	�N���X

class farmReqCarrot
{
	public:
		void	CreateReqCarrot();
		void	ReleaseReqCarrot();
		void	ClearReqCarrot();
		void	ResetReqCarrot();

		void	SetReqCarrot(BYTE*);
		void	SetPos(int,int);

		bool	IsEndRequest();

		void	Update();
		void	Show();
		void	ShowFont();

	private:
		BYTE	dRequest[36];
		int		Total,TotalB;
		int		PosX,PosY;
		int		cProg;
};

#endif	//	_FARMREQCARROT_H_
