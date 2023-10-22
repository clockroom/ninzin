//
//	�^�C�g���A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

#ifndef _APPTITLE_H_
#define _APPTITLE_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "titletitle.h"
#include "titlecopyright.h"
#include "titlemenu.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

class appTitle;

///////////////////////////////////////////////////////////
//	�N���X

class appTitle:public afApp
{
	public:
		appTitle();

		void	InitApp();
		void	FinalApp();
		void	Main();

		void	InitAppFromLogo();
		void	InitAppFromHome();
		void	InitAppFromOption();

	private:
		void	FinalAppToHome();
		void	FinalAppToOption();
		void	FinalAppToEndProgram();

		void	_EndProgram();

		void	_PreEvent();
		void	_UpdateProcess();
		bool	_MouseEvent();

		void	_Show();

	private:
		afOscillator OscFrmLim;

		titleTitle		Title;
		titleCopyright	Copyright;
		titleMenu		Menu;

		int		nProcess;
		int		cProg;
};

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ��錾

extern appTitle AppTitle;

#endif	//	_APPTITLE_H_
