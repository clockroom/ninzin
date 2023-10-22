//
//	�^�C�g���A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libmusic.h"
#include "libsound.h"
#include "libcursor.h"
#include "fileoption.h"
#include "appfade.h"
#include "apptitle.h"
#include "apphome.h"
#include "appoption.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define PROCESS_LOADTITLE	 0
#define PROCESS_TITLECALL	10
#define PROCESS_MENUCALL	20
#define PROCESS_MAIN		30

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appTitle AppTitle;

///////////////////////////////////////////////////////////
//	�\�z

appTitle::appTitle():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	������

void appTitle::InitApp()
{
	libCursor	lc;
	fileOption	fo;

	//	�I�v�V�����ݒ�
	fo.LoadOption();
	libMusic::SetOutputSystem(fo.GetBGMOutput());
	afMusic2::SetMasterVolume(fo.GetBGMVolume());
	afSound ::SetMasterVolume(fo.GetSEVolume());

	//	���C�u����������
	libFont::InitLibrary(26);
	libMusic::InitLibrary(1);
	libSound::InitLibrary();
	libSound::InitLibrary(20,2);
	libSound::InitLibrary(21,3);
	libCursor::InitLibrary();

	//	�}�E�X������
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	�^�C�g��������
	Title.CreateTitle();
	Title.SetPos(0,32);

	//	�R�s�[���C�g������
	Copyright.CreateCopyright();
	Copyright.SetPos(178,376);

	//	���j���[������
	Menu.CreateMenu();
	Menu.SetPos(224,248);
}

void appTitle::FinalApp()
{
	//	�I�u�W�F�N�g���
	Title.ReleaseTitle();
	Copyright.ReleaseCopyright();
	Menu.ReleaseMenu();

	//	���C�u�������
	libFont::FinalLiblary();
	libMusic::FinalLibrary();
	libSound::FinalLibrary();
	libCursor::FinalLibrary();
}

///////////////////////////////////////////////////////////
//	�������⏕

void appTitle::InitAppFromLogo()
{
	//	������
	InitApp();

	//	�t�F�[�h�C��
	nProcess=PROCESS_LOADTITLE;
	SetActiveApp(this,APP_MAIN);
}

void appTitle::InitAppFromHome()
{
	libMusic	lm;

	//	������
	InitApp();

	//	�I�u�W�F�N�g���Z�b�g
	Title.ResetTitleMain();
	Copyright.ResetCopyrightMain();
	Menu.ResetMenuMain();

	//	BGM��~
	lm.StopMusic();

	//	��ʍ\�z
	ms.ClearWhite();
	Title.Show();
	Copyright.Show();
	Menu.Show(-1,-1);

	//	�t�F�[�h�C��
	nProcess=PROCESS_MAIN;
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appTitle::Main);
}

void appTitle::InitAppFromOption()
{
	//	������
	InitApp();

	//	�I�u�W�F�N�g���Z�b�g
	Title.ResetTitleMain();
	Copyright.ResetCopyrightMain();
	Menu.ResetMenuMain();

	//	��ʍ\�z
	ms.ClearWhite();
	Title.Show();
	Copyright.Show();
	Menu.Show(-1,-1);

	//	�t�F�[�h�C��
	nProcess=PROCESS_MAIN;
	AppFade.CallFade(AF_FADE_WHITEIN,8,this,(FPAPPFUNC)appTitle::Main);
}

void appTitle::FinalAppToHome()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppHome,(FPAPPFUNC)appHome::InitApp);
}

void appTitle::FinalAppToOption()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_WHITEOUT,8,&AppOption,(FPAPPFUNC)appOption::InitApp);
}

void appTitle::FinalAppToEndProgram()
{
	FinalApp();

	cProg=-1;
	AppFade.CallFade(AF_FADE_BLACKOUT,8,this,(FPAPPFUNC)appTitle::_EndProgram);
}

///////////////////////////////////////////////////////////
//	�v���O�����I��

void appTitle::_EndProgram()
{
	libMusic	lm;

	if(!OscFrmLim) return;

	cProg++;
	if(cProg==25) lm.StopMusic();
	if(cProg< 50) return;

	ExitProgram();
}

///////////////////////////////////////////////////////////
//	���C��

void appTitle::Main()
{
	//	�t���[�����~�b�^
	if(!OscFrmLim) return;

	//	�L�[�X�V
	mos.UpdateKey();

	//	�O�u�C�x���g
	_PreEvent();

	//	�\��
	_Show();
}

///////////////////////////////////////////////////////////
//	�O�u�C�x���g

void appTitle::_PreEvent()
{
	//	�v���Z�X�X�V
	_UpdateProcess();

	//	�I�u�W�F�N�g�X�V
	Title.Update();
	Copyright.Update();
	Menu.Update();

	//	�C�x���g����
	_MouseEvent();
}

///////////////////////////////////////////////////////////
//	�v���Z�X�X�V

void appTitle::_UpdateProcess()
{
	libMusic	lm;
	bool		a,b;

	switch(nProcess)
	{
	case PROCESS_LOADTITLE:

		Title.ResetTitleTitleCall();

		cProg=0;
		nProcess=PROCESS_TITLECALL;

		break;

	case PROCESS_TITLECALL:

		if(++cProg==150) lm.PlayMusic(1);

		a=Title.IsEndEntrance();
		if(!a) break;

		Copyright.ResetCopyrightMenuCall();
		Menu.ResetMenuMenuCall();

		nProcess=PROCESS_MENUCALL;

		break;

	case PROCESS_MENUCALL:

		a=Copyright.IsEndEntrance();
		b=Menu.IsEndEntrance();
		if(!a || !b) break;

		Title.ResetTitleMain();
		Copyright.ResetCopyrightMain();
		Menu.ResetMenuMain();

		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	�}�E�X�C�x���g

bool appTitle::_MouseEvent()
{
	libMusic	lm;
	libSound	ls;
	int	mx,my;

	//	�}�E�X�����ȊO
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	���j���[�\���O
	if(nProcess!=PROCESS_MAIN)
	{
		Title.ResetTitleMain();
		Copyright.ResetCopyrightMain();
		Menu.ResetMenuMain();
		lm.PlayMusic(1);
		nProcess=PROCESS_MAIN;
		return true;
	}

	//	���j���[�I��
	mos.GetPos(&mx,&my);
	switch(Menu.IsMenu(mx,my))
	{
	case TM_MENU_START:
		ls.PlaySound(6);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToHome);
		break;

	case TM_MENU_OPTION:
		ls.PlaySound(6);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToOption);
		break;

	case TM_MENU_END:
		ls.PlaySound(7);
		SetActiveApp(this,(FPAPPFUNC)appTitle::FinalAppToEndProgram);
		break;

	default:
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////
//	�\��

void appTitle::_Show()
{
	int	mx,my;

	//	��ʏ���
	ms.ClearWhite();

	//	�^�C�g���\��
	Title.Show();

	//	�R�s�[���C�g�\��
	Copyright.Show();

	//	���j���[�\��
	mos.GetPos(&mx,&my);
	Menu.Show(mx,my);

	//	�}�E�X�\��
	if(nProcess==PROCESS_MAIN) mos.Show();

	//	��ʍX�V
	ms.Refresh();
}
