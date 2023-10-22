//
//	�z�[���A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/27
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libitem.h"
#include "libmusic.h"
#include "libsound.h"
#include "libwindow.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "appfade.h"
#include "apptitle.h"
#include "apphome.h"
#include "appfarm.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define PROCESS_LOADHOME	 0
#define	PROCESS_WINDOWCALL	10
#define PROCESS_MAIN		20

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appHome AppHome;

///////////////////////////////////////////////////////////
//	�\�z

appHome::appHome():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	������

void appHome::InitApp()
{
	libMusic	lm;
	libCursor	lc;

	//	���C�u����������
	libFont::InitLibrary();
	libFont::InitLibrary(17);
	libFont::InitLibrary(27);
	libFont::InitLibrary(28);
	libItem::InitLibrary();
	libMusic::InitLibrary(2);
	libSound::InitLibrary();
	libSound::InitLibrary(5,1);
	libSound::InitLibrary(15,3);
	libSound::InitLibrary(16,2);
	libWindow::InitLibrary();
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	�}�E�X������
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	�v���C�f�[�^�ǂݍ���
	PlayData.LoadPlayData();

	//	�w�i������
	BackGround.CreateBackGround();

	//	�Z�N�V������������
	SectionName.CreateSectionName();
	SectionName.SetPos(36,28);

	//	���R�[�h������
	Record.CreateRecord(&PlayData);
	Record.SetPos(16,140);

	//	�w���v������
	Help.CreateHelp();
	Help.SetPos(16,272);

	//	�߂�{�^��������
	Return.CreateReturn();
	Return.SetPos(64,400);

	//	�t�@�[�����X�g������
	FarmList.CreateFarmList(&PlayData);
	FarmList.SetPos(300,38);

	//	�ϐ�������
	nProcess=PROCESS_LOADHOME;

	//	BGM�Đ�
	lm.PlayMusic(2);
	Sleep(2000);

	//	�t�F�[�h�C��
	BackGround.Show();
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appHome::Main);
}

void appHome::FinalApp()
{
	//	�I�u�W�F�N�g���
	BackGround.ReleaseBackGround();
	SectionName.ReleaseSectionName();
	Record.ReleaseRecord();
	Help.ReleaseHelp();
	Return.ReleaseReturn();
	FarmList.ReleaseFarmList();

	//	���C�u�������
	libFont::FinalLiblary();
	libItem::FinalLibrary();
	libMusic::FinalLibrary();
	libSound::FinalLibrary();
	libWindow::FinalLibrary();
	libCursor::FinalLibrary();
	libCarrot::FinalLibrary();
}

///////////////////////////////////////////////////////////
//	�������⏕

void appHome::FinalAppToFarm()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppFarm,(FPAPPFUNC)appFarm::InitApp);
}

void appHome::FinalAppToTitle()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppTitle,(FPAPPFUNC)appTitle::InitAppFromHome);
}

///////////////////////////////////////////////////////////
//	���C��

void appHome::Main()
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

void appHome::_PreEvent()
{
	//	�v���Z�X�X�V
	_UpdateProcess();

	//	�X�V
	BackGround.Update();
	SectionName.Update();
	Record.Update();
	Help.Updata();
	Return.Update();
	FarmList.Update();

	//	�i���C���v���Z�X�ȊO�ł͏������Ȃ��j
	if(nProcess!=PROCESS_MAIN) return;

	//	�C�x���g����
	if(_FarmSelect())	return;
	if(_PageButton())	return;
	if(_ReturnButton()) return;
}

///////////////////////////////////////////////////////////
//	�v���Z�X�X�V

void appHome::_UpdateProcess()
{
	bool	a,b,c,d,e;

	switch(nProcess)
	{
	case PROCESS_LOADHOME:

		SectionName.ResetSectionName();
		FarmList.ResetFarmList();
		Record.ResetRecord();
		Help.ResetHelp();
		Return.ResetReturn();

		nProcess=PROCESS_WINDOWCALL;

		break;

	case PROCESS_WINDOWCALL:

		a=FarmList.IsEndEntrance();
		b=Record.IsEndEntrance();
		c=SectionName.IsEndEntrance();
		d=Help.IsEndEntrance();
		e=Return.IsEndEntrance();
		if(!a || !b || !c || !d || !e) break;

		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	�t�@�[���I��

bool appHome::_FarmSelect()
{
	libSound	ls;
	int	mx,my;
	int	s;

	//	�J�[�\���ʒu�擾
	mos.GetPos(&mx,&my);

	//	�I���擾
	s=FarmList.IsFarm(mx,my);
	if(s==0) return false;

	//	�}�E�X�����擾
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	�I��
	ls.PlaySound(6);
	AppFarm.SetFarmNo(s);
	SetActiveApp(this,(FPAPPFUNC)appHome::FinalAppToFarm);

	return true;
}

///////////////////////////////////////////////////////////
//	�y�[�W�߂���

bool appHome::_PageButton()
{
	libSound	ls;
	int	mx,my;
	int	p;

	//	�J�[�\���ʒu�擾
	mos.GetPos(&mx,&my);

	//	�{�^���擾
	p=FarmList.IsButton(mx,my);
	if(p==0) return false;

	//	�}�E�X�����擾
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	�y�[�W�߂���
	ls.PlaySound(5);
	FarmList.AddPage(p);

	return true;
}

///////////////////////////////////////////////////////////
//	�^�C�g���ɖ߂�

bool appHome::_ReturnButton()
{
	libSound	ls;
	int	mx,my;

	//	�J�[�\���ʒu�擾
	mos.GetPos(&mx,&my);

	//	����
	if(!Return.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	�^�C�g���ɖ߂�
	ls.PlaySound(7);
	SetActiveApp(this,(FPAPPFUNC)appHome::FinalAppToTitle);

	return true;
}

///////////////////////////////////////////////////////////
//	�\��

void appHome::_Show()
{
	int	mx,my;

	//	�J�[�\���ʒu�擾
	mos.GetPos(&mx,&my);

	//	�w�i�\��
	BackGround.Show();

	//	�Z�N�V�������\��
	SectionName.Show();

	//	�t�@�[�����X�g�\��
	if(nProcess==PROCESS_MAIN) FarmList.Show(mx,my);
	else					   FarmList.Show(-1,-1);

	//	�����\��
	Record.Show();
	Help.Show();

	//	�߂�{�^���\��
	if(nProcess==PROCESS_MAIN) Return.Show(mx,my);
	else					   Return.Show(-1,-1);

	//	�}�E�X�J�[�\���\��
	mos.Show();

	//	��ʍX�V
	ms.Refresh();
}
