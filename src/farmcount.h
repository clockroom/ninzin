//
//	�J�E���g�N���X by ClockRoom 2001
//	Program by Y.Kumagai 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/07/22
//

#ifndef _FARMCOUNT_H_
#define _FARMCOUNT_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class farmCount;

///////////////////////////////////////////////////////////
//	�N���X

class farmCount
{
	private:
		struct dataCarrotCount
		{
			int	cCarrot;
			int	ReqCarrot;
		};

	public:
		void	CreateCount();
		void	ReleaseCount();
		void	ClearCount();

		void	SetPos(int,int);
		void	AddCount(BYTE);
		void	AddRequest(BYTE);

		void	GetPos(int*,int*);
		bool	IsClear();
		bool	IsFailure();

		void	Show();

	private:
		dataCarrotCount	dCount[8];
		int	PosX,PosY;
};

#endif	//	_FARMCOUNT_H_
