//
//	クリアサインクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/07/22
//

#ifndef _FARMCLEARSIGN_H_
#define _FARMCLEARSIGN_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class farmClearSign;

///////////////////////////////////////////////////////////
//	クラス

class farmClearSign
{
	public:
		void	CreateClearSign();
		void	ReleaseClearSign();
		void	ResetClearSign();

		void	SetPos(int,int);

		bool	IsEndSign();

		void	Update();
		void	Show();

	private:
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_FARMCLEARSIGN_H_
