//
//	飛行ニンジンクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/26
//	Last  Edition 2001/07/10
//

#ifndef _FARMFLYCARROT_H_
#define _FARMFLYCARROT_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class farmFlyCarrot;
class farmMap;
class farmCount;

///////////////////////////////////////////////////////////
//	クラス

class farmFlyCarrot
{
	public:
		static void	InitFlyCarrot(farmMap*,farmCount*);
		static void	FinalFlyCarrot();

		static void	CreateFlyPullCarrot(BYTE,int,int);
		static void CreateFlyReqCarrot(BYTE,int,int);

		static void	DestroyAll();
		static void	UpdateAll();
		static void	ShowAll();

		static bool IsEndFlyReqCarrot();

	private:
		farmFlyCarrot(int,BYTE,int,int,int,int);
		~farmFlyCarrot();

		void	_Destroy();
		void	_Update();
		void	_Show();

		bool	_IsEndFlyReqCarrot();

	private:
		static farmFlyCarrot	*pChainTop;

		static farmMap		*pMap;
		static farmCount	*pCount;

		farmFlyCarrot	*pChainNext;
		BYTE	nCarrot;
		int		nType;
		int		SX,SY,EX,EY;
		int		cProg;
};

#endif	//	_FARMFLYCARROT_H_
