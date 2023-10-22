//
//	�I�v�V�����A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/23
//

#ifndef _APPOPTION_H_
#define _APPOPTION_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "fileoption.h"
#include "optsectionname.h"
#include "optbgmoutput.h"
#include "optbgmvolume.h"
#include "optsevolume.h"
#include "optmouse.h"
#include "optdelrecord.h"
#include "optreturn.h"

///////////////////////////////////////////////////////////
//	�N���X�錾

class appOption;

///////////////////////////////////////////////////////////
//	�N���X

class appOption:public afApp
{
	public:
		appOption();

		void	InitApp();
		void	FinalApp();
		void	Main();

	private:
		void	_PreEvent();
		bool	_SelectBGMOutput();
		bool	_SelectBGMVolume();
		bool	_SelectSEVolume();
		bool	_SelectMouse();
		bool	_DelRecordButton();
		bool	_ReturnButton();

		void	_Show();

	private:
		afOscillator	OscFrmLim;

		fileOption		Option;

		optSectionName	SectionName;
		optBGMOutput	BGMOutput;
		optBGMVolume	BGMVolume;
		optSEVolume		SEVolume;
		optMouse		Mouse;
		optDelRecord	DelRecord;
		optReturn		Return;
};

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ��錾

extern appOption AppOption;

#endif	//	_APPOPTION_H_
