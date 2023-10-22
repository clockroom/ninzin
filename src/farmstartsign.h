//
//	開始サインクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/07
//	Last  Edition 2001/07/07
//

#ifndef _FARMSTARTSIGN_H_
#define _FARMSTARTSIGN_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class farmStartSign;

///////////////////////////////////////////////////////////
//	クラス

class farmStartSign
{
	public:
		void	CreateStartSign();
		void	ReleaseStartSign();
		void	ResetStartSign();

		void	SetPos(int,int);
		void	SetFarmNo(int);

		bool	IsEndSign();

		void	Update();
		void	Show();

	private:
		int	PosX,PosY;
		int	cProg;
		int	FarmNo;
};

#endif	//	_FARMSTARTSIGN_H_
