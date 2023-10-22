//
//	ホームアプリケーション ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/27
//	Last  Edition 2001/09/23
//

#ifndef _APPHOME_H_
#define _APPHOME_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "fileplaydata.h"
#include "homebackground.h"
#include "homesectionname.h"
#include "homerecord.h"
#include "homehelp.h"
#include "homereturn.h"
#include "homefarmlist.h"

///////////////////////////////////////////////////////////
//	クラス宣言

class appHome;

///////////////////////////////////////////////////////////
//	クラス

class appHome:public afApp
{
	public:
		appHome();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	FinalAppToFarm();
		void	FinalAppToTitle();

		void	_PreEvent();
		void	_UpdateProcess();
		bool	_FarmSelect();
		bool	_PageButton();
		bool	_ReturnButton();

		void	_Show();

	private:
		afOscillator	OscFrmLim;

		filePlayData	PlayData;

		homeBackGround	BackGround;
		homeSectionName	SectionName;
		homeRecord		Record;
		homeHelp		Help;
		homeReturn		Return;
		homeFarmList	FarmList;

		int	nProcess;
};

///////////////////////////////////////////////////////////
//	グローバル変数宣言

extern appHome AppHome;

#endif	//	_APPHOME_H_
