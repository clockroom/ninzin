//
//	�z�[���A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/27
//	Last  Edition 2001/09/23
//

#ifndef _APPHOME_H_
#define _APPHOME_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "fileplaydata.h"
#include "homebackground.h"
#include "homesectionname.h"
#include "homerecord.h"
#include "homehelp.h"
#include "homereturn.h"
#include "homefarmlist.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

class appHome;

///////////////////////////////////////////////////////////
//	�N���X

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
//	�O���[�o���ϐ��錾

extern appHome AppHome;

#endif	//	_APPHOME_H_
