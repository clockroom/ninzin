//
//	ステータスクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/09
//	Last  Edition 2001/09/13
//

#ifndef _FARMSTATE_H_
#define _FARMSTATE_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class farmState;

///////////////////////////////////////////////////////////
//	クラス

class farmState
{
	public:
		void	CreateState();
		void	ReleaseState();
		void	ResetStateNone();
		void	ResetStateStartSign();
		void	ResetStateMain();
		void	PauseState();
		void	RestartState();

		void	SetPos(int,int);
		void	SetFarmNo(int);
		void	SetGoodWater(int);
		void	SetBestRecord(int,int);
		void	AddWater(int);

		void	GetRecord(int*,int*);
		void	GetBestRecord(int*,int*);
		bool	IsEndCount();

		void	Update();
		void	Show();

	private:
		void	_CreateStateBitmap();

	private:
		afBitmap	BmpState;
		int	PosX,PosY;
		int	FarmNo;
		int	GoodWater;
		int	cGoodWater;
		int	BestWater;
		int	BestTime;
		int	cWater;
		int	cTime;
		int	nProc,cProg;
};

#endif	//	_FARMSTATE_H_
