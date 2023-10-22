//
//	���s�T�C���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/03
//	Last  Edition 2001/09/13
//

#ifndef _FARMFAILURESIGN_H_
#define _FARMFAILURESIGN_H_

///////////////////////////////////////////////////////////
//	�N���X�錾

class farmFailureSign;

///////////////////////////////////////////////////////////
//	�N���X

class farmFailureSign
{
	public:
		void	CreateFailureSign();
		void	ReleaseFailureSign();
		void	ResetFailureSign();
		void	ResetFailureSignNone();

		void	SetPos(int,int);

		bool	IsEndSign();

		void	Update();
		void	Show();

	private:
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_FARMFAILURESIGN_H_
