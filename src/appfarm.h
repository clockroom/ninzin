//
//	ファームアプリケーション by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/23
//

#ifndef _APPFARM_H_
#define _APPFARM_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "farmmap.h"
#include "farmframe.h"
#include "farmstate.h"
#include "farmcount.h"
#include "farmbutton.h"
#include "farmstartsign.h"
#include "farmclearsign.h"
#include "farmfailuresign.h"
#include "farmreqcarrot.h"
#include "farmhelp.h"

///////////////////////////////////////////////////////////
//	クラス宣言

class appFarm;

///////////////////////////////////////////////////////////
//	クラス

class appFarm:public afApp
{
	public:
		appFarm();
		~appFarm();

		void	InitApp();
		void	FinalApp();
		void	Main();

		void	SetFarmNo(int);

	private:
		void	FinalAppToHome();
		void	FinalAppToEnding();

		void	_PreEvent();
		void	_UpdateProcess();
		void	_LoadFarm();
		void	_SaveFarm();
		bool	_WaterCarrot();
		bool	_PullCarrot();
		bool	_Button();

		void	_Show();

	private:
		afOscillator	OscFrmLim;

		farmMap		Map;
		farmFrame	Frame;
		farmState	State;
		farmCount	Count;
		farmButton	Button;
		farmStartSign	StartSign;
		farmClearSign	ClearSign;
		farmFailureSign	FailureSign;
		farmReqCarrot	ReqCarrot;
		farmHelp	Help;

		int		nProcess;
		int		FarmNo;
		int		LastPosX,LastPosY;
		bool	fFirstLoad;
		bool	fRetry;
		bool	fTurnLR;
};

///////////////////////////////////////////////////////////
//	グローバル変数宣言

extern appFarm AppFarm;

#endif	//	_APPFARM_H_
