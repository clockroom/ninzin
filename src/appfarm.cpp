//
//	�t�@�[���A�v���P�[�V���� by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "common.h"
#include "libfont.h"
#include "libitem.h"
#include "libmusic.h"
#include "libsound.h"
#include "libwindow.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "fileoption.h"
#include "filefarmmap.h"
#include "fileplaydata.h"
#include "appfade.h"
#include "appfarm.h"
#include "apphome.h"
#include "appending.h"
#include "farmflycarrot.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define PROCESS_LOADFARM	 0
#define PROCESS_STARTSIGN	10
#define	PROCESS_MAIN		20
#define PROCESS_CLEARSIGN	30
#define PROCESS_FAILURESIGN	40
#define PROCESS_HELP		50

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appFarm AppFarm;

///////////////////////////////////////////////////////////
//	�\�z

appFarm::appFarm():OscFrmLim(20,5)
{
}

appFarm::~appFarm()
{
	farmFlyCarrot::DestroyAll();
}

///////////////////////////////////////////////////////////
//	������

void appFarm::InitApp()
{
	libMusic		lm;
	libCursor		lc;
	fileFarmMap		ffm;
	fileOption		fo;
	filePlayData	fpd;
	int		bw,bt;
	int		mn;

	//	���C�u����������
	libFont::InitLibrary();
	libFont::InitLibrary(16);
	libItem::InitLibrary();
	libMusic::InitLibrary(3);
	libMusic::InitLibrary(4);
	libSound::InitLibrary();
	libSound::InitLibrary(8,1);
	libSound::InitLibrary(9,1);
	libSound::InitLibrary(10,2);
	libSound::InitLibrary(11,2);
	libSound::InitLibrary(12,1);
	libSound::InitLibrary(13,2);
	libSound::InitLibrary(14,1);
	libSound::InitLibrary(17,1);
	libSound::InitLibrary(18,1);
	libSound::InitLibrary(19,1);
	libWindow::InitLibrary();
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	�}�E�X������
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	�}�b�v������
	Map.CreateMap();
	Map.SetPos(48,48);
	Frame.CreateFrame();
	Frame.SetPos(0,0);

	//	�X�e�[�^�X������
	State.CreateState();
	State.SetPos(480,0);
	Count.CreateCount();
	Count.SetPos(504,72);
	Button.CreateButton();
	Button.SetPos(504,440);

	//	�T�C��������
	StartSign.CreateStartSign();
	StartSign.SetPos(132,214);
	ClearSign.CreateClearSign();
	ClearSign.SetPos(140,214);
	FailureSign.CreateFailureSign();
	FailureSign.SetPos(152,214);

	//	���N�G�X�g������
	ReqCarrot.CreateReqCarrot();
	ReqCarrot.SetPos(8,440);

	//	�w���v������
	Help.CreateHelp();
	Help.SetPos(48,96);

	//	��s�j���W��������
	farmFlyCarrot::InitFlyCarrot(&Map,&Count);

	//	�ϐ�������
	fo.LoadOption();
	fTurnLR=fo.GetTurnLR();
	nProcess=PROCESS_LOADFARM;

	//	�ȍĐ�
	ffm.LoadFarmMap(FarmNo);
	mn=ffm.GetMusic();
	if(mn==0) lm.StopMusic();
	else	  lm.PlayMusic(mn);
	Sleep(2000);

	//	�t�F�[�h�C���p�ݒ�
	fpd.LoadPlayData();
	fpd.GetFarmRecord(NULL,&bw,&bt,FarmNo);
	State.SetFarmNo(FarmNo);
	State.SetBestRecord(bw,bt);

	//	�t�F�[�h�C���p��ʍ\�z
	Map.Show(-1,-1,FM_SC_NONE);
	Frame.Show();
	State.Show();
	Count.Show();
	Button.Show(-1,-1,false);

	//	�t�F�[�h�C��
	AppFade.CallFade(AF_FADE_BLACKIN,8,this,(FPAPPFUNC)appFarm::Main);
}

void appFarm::FinalApp()
{
	//	�I�u�W�F�N�g���
	Map.ReleaseMap();
	Frame.ReleaseFrame();
	State.ReleaseState();
	Count.ReleaseCount();
	Button.ReleaseButton();
	StartSign.ReleaseStartSign();
	ClearSign.ReleaseClearSign();
	FailureSign.ReleaseFailureSign();
	ReqCarrot.ReleaseReqCarrot();
	Help.ReleaseHelp();

	//	��s�j���W�����
	farmFlyCarrot::FinalFlyCarrot();

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

void appFarm::FinalAppToHome()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppHome,(FPAPPFUNC)appHome::InitApp);
}

void appFarm::FinalAppToEnding()
{
	FinalApp();
	AppFade.CallFade(AF_FADE_BLACKOUT,8,&AppEnding,(FPAPPFUNC)appEnding::InitApp);
}

///////////////////////////////////////////////////////////
//	���C��

void appFarm::Main()
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

void appFarm::_PreEvent()
{
	libCursor	lc;

	//	�v���Z�X�X�V
	_UpdateProcess();

	//	�I�u�W�F�N�g�X�V
	State.Update();
	Map.Update();
	StartSign.Update();
	ClearSign.Update();
	FailureSign.Update();
	ReqCarrot.Update();
	farmFlyCarrot::UpdateAll();

	//	�}�E�X�J�[�\���ݒ�
	lc.ProvideMouseCursor(&mos,0);

	//	�{�^��
	if(_Button()) return;

	//	(���C���v���Z�X�ȊO�ł͏������Ȃ�)
	if(nProcess!=PROCESS_MAIN) return;

	//	�s��
	if(_WaterCarrot()) return;
	if(_PullCarrot())  return;
}

///////////////////////////////////////////////////////////
//	�v���Z�X�X�V

void appFarm::_UpdateProcess()
{
	libSound		ls;
	filePlayData	fpd;
	bool	a,b,c,d,e;

	switch(nProcess)
	{
	case PROCESS_LOADFARM:

		_LoadFarm();
		LastPosX=-1;
		LastPosY=-1;
		nProcess=PROCESS_STARTSIGN;

		break;

	case PROCESS_STARTSIGN:

		a=Map.IsEndPlant();
		b=StartSign.IsEndSign();
		c=ReqCarrot.IsEndRequest();
		d=farmFlyCarrot::IsEndFlyReqCarrot();
		e=State.IsEndCount();
		if(!a || !b || !c || !d || !e) break;

		State.ResetStateMain();
		nProcess=PROCESS_MAIN;

		break;

	case PROCESS_MAIN:

		//	����ǂݍ���
		if(fFirstLoad)
		{
			fFirstLoad=false;

			//	�ǂݍ��݌`�ՋL�^
			fpd.LoadPlayData();
			fpd.SetFarmRecord(FarmNo,FP_NOCLEAR,FP_NOCLEAR);
			fpd.SavePlayData();

			//	�����w���v�N��
			if(!Help.IsRequestAutoHelp(FarmNo)) break;
			Help.Open(FarmNo);
			State.PauseState();
			mos.InvalidateKeyL();

			nProcess=PROCESS_HELP;

			break;
		}

		//	�N���A
		if(Count.IsClear() && !MODE_EDIT)
		{
			ls.PlaySound(14);
			ClearSign.ResetClearSign();
			State.ResetStateNone();
			nProcess=PROCESS_CLEARSIGN;
			break;
		}

		//	���s
		if(Count.IsFailure() && !MODE_EDIT)
		{
			ls.PlaySound(12);
			FailureSign.ResetFailureSign();
			State.ResetStateNone();
			farmFlyCarrot::DestroyAll();
			mos.InvalidateKeyL();
			nProcess=PROCESS_FAILURESIGN;
			break;
		}

		break;

	case PROCESS_CLEARSIGN:

		a=ClearSign.IsEndSign();
		if(!a) break;

		_SaveFarm();

		//	�G���f�B���O��
		if(FarmNo==MAX_FARM && !fRetry)
		{
			SetActiveApp(this,(FPAPPFUNC)appFarm::FinalAppToEnding);
			break;
		}

		if(!fRetry) FarmNo++;
		nProcess=PROCESS_LOADFARM;

		break;

	case PROCESS_FAILURESIGN:

		if(mos.GetKeyL()!=KEY_PULL)
		{
			a=FailureSign.IsEndSign();
			if(!a) break;
		}
		else
		{
			mos.InvalidateKeyL();
			FailureSign.ResetFailureSignNone();
		}

		nProcess=PROCESS_LOADFARM;

		break;

	case PROCESS_HELP:

		if(mos.GetKeyL()!=KEY_PULL) break;
		mos.InvalidateKeyL();

		Help.Close();
		State.RestartState();
		nProcess=PROCESS_MAIN;

		break;
	}
}

///////////////////////////////////////////////////////////
//	�X�e�[�W���[�h

void appFarm::_LoadFarm()
{
	libMusic		lm;
	fileFarmMap		ffm;
	filePlayData	fpd;
	BYTE	(*pm)[8];
	BYTE	*pr;
	int		gw,bw,bt;
	int		mn;

	//	�}�b�v�ǂݍ���
	ffm.LoadFarmMap(FarmNo);
	pm=ffm.GetMap();
	pr=ffm.GetRequest();

	//	���R�[�h�ǂݍ���
	fpd.LoadPlayData();
	fpd.GetFarmRecord(&gw,&bw,&bt,FarmNo);

	//	����ǂݍ���
	if(bw==FP_FIRSTLOAD) fFirstLoad=true;
	else				 fFirstLoad=false;
	if(bw==FP_FIRSTLOAD || bw==FP_NOCLEAR) fRetry=false;
	else fRetry=true;

	//	�ȍĐ�
	mn=ffm.GetMusic();
	if(mn==0) lm.StopMusic();
	else	  lm.PlayMusic(mn);

	//	�J�E���g�N���A
	Count.ClearCount();

	//	�X�e�[�^�X�ݒ�
	State.SetFarmNo(FarmNo);
	State.SetGoodWater(gw);
	State.SetBestRecord(bw,bt);
	State.ResetStateStartSign();

	//	�}�b�v�ݒ�
	Map.SetMap(pm);
	Map.ResetMap();

	//	���N�G�X�g�ݒ�
	ReqCarrot.SetReqCarrot(pr);
	ReqCarrot.ResetReqCarrot();

	//	�J�n�T�C���ݒ�
	StartSign.SetFarmNo(FarmNo);
	StartSign.ResetStartSign();
}

///////////////////////////////////////////////////////////
//	�X�e�[�W�Z�[�u

void appFarm::_SaveFarm()
{
	filePlayData	fpd;
	int	nw,nt,bw,bt;

	//	���R�[�h�擾
	State.GetRecord(&nw,&nt);
	State.GetBestRecord(&bw,&bt);

	//	���R�[�h�ݒ�
	if(nw<bw)
	{
		bw=nw;
		bt=nt;
	}
	else if(nw==bw && nt<bt)
	{
		bw=nw;
		bt=nt;
	}

	//	���R�[�h��������
	fpd.LoadPlayData();
	fpd.SetFarmRecord(FarmNo,bw,bt);
	fpd.SavePlayData();
}

///////////////////////////////////////////////////////////
//	�����

bool appFarm::_WaterCarrot()
{
	libSound	ls;
	libCursor	lc;
	int	mx,my;
	int	fx,fy;

	mos.GetPos(&mx,&my);
	if(!Map.IsFarm(mx,my)) return false;

	if(!fTurnLR)
	{
		if(mos.GetKeyR()!=KEY_FREE) return false;
		if(mos.GetKeyL()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,1);
		}
		if(mos.GetKeyL()!=KEY_PULL) return false;
		mos.InvalidateKeyL();
	}
	else
	{
		if(mos.GetKeyL()!=KEY_FREE) return false;
		if(mos.GetKeyR()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,1);
		}
		if(mos.GetKeyR()!=KEY_PULL) return false;
		mos.InvalidateKeyR();
	}

	if(!Map.WaterCarrot(mx,my)) return false;
	ls.PlaySound(8);

	Map.GetFarmPos(&fx,&fy,mx,my);
	if(LastPosX!=fx || LastPosY!=fy)
	{
		State.AddWater(1);
		LastPosX=fx;
		LastPosY=fy;
	}
	else
	{
		State.AddWater(-1);
		LastPosX=-1;
		LastPosY=-1;
	}

	return true;
}

///////////////////////////////////////////////////////////
//	���n

bool appFarm::_PullCarrot()
{
	libSound	ls;
	libCursor	lc;
	BYTE	c;
	int		x,y;

	mos.GetPos(&x,&y);
	if(!Map.IsFarm(x,y)) return false;

	if(!fTurnLR)
	{
		if(mos.GetKeyL()!=KEY_FREE) return false;
		if(mos.GetKeyR()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,2);
		}
		if(mos.GetKeyR()!=KEY_PULL) return false;
		mos.InvalidateKeyR();
	}
	else
	{
		if(mos.GetKeyR()!=KEY_FREE) return false;
		if(mos.GetKeyL()!=KEY_FREE)
		{
			lc.ProvideMouseCursor(&mos,2);
		}
		if(mos.GetKeyL()!=KEY_PULL) return false;
		mos.InvalidateKeyL();
	}

	c=Map.PullCarrot(x,y);
	if(c&0x08) return false;
	ls.PlaySound(9);

	LastPosX=-1;
	LastPosY=-1;

	//	��s�j���W���쐬
	farmFlyCarrot::CreateFlyPullCarrot(c,x,y);

	return true;
}

///////////////////////////////////////////////////////////
//	�{�^��

bool appFarm::_Button()
{
	libSound	ls;
	int	mx,my;
	int	b;

	mos.GetPos(&mx,&my);
	b=Button.IsButton(mx,my);

	if(b==FB_BTN_NONE) return false;
	if(nProcess!=PROCESS_MAIN)
	{
		if(nProcess!=PROCESS_STARTSIGN) return false;
		if(b!=FB_BTN_EXIT)				return false;
	}
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	�{�^�����Ƃ̏���
	switch(b)
	{
	case FB_BTN_HELP:
		Help.Open(0);
		State.PauseState();
		nProcess=PROCESS_HELP;
		return true;

	case FB_BTN_RETURN:
		nProcess=PROCESS_LOADFARM;
		return true;

	case FB_BTN_EXIT:
		ls.PlaySound(7);
		SetActiveApp(this,(FPAPPFUNC)appFarm::FinalAppToHome);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////
//	�\��

void appFarm::_Show()
{
	int	mx,my;
	int	f;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	�}�b�v�\��
	f=(mos.GetKeyR()==KEY_FREE)?FM_SC_WATER:FM_SC_PULL;
	f=(mos.GetKeyL()!=KEY_FREE)?FM_SC_WATER:f;
	f=(nProcess!=PROCESS_MAIN )?FM_SC_NONE :f;
	Map.Show(mx,my,f);
	Frame.Show();

	//	�X�e�[�^�X�\��
	State.Show();
	Count.Show();
	switch(nProcess)
	{
	case PROCESS_MAIN:	   Button.Show(mx,my,true); break;
	case PROCESS_STARTSIGN:Button.Show(mx,my,false);break;
	default:			   Button.Show(-1,-1,false);break;
	}

	//	���N�G�X�g�\��
	ReqCarrot.Show();

	//	��s�j���W���\��
	farmFlyCarrot::ShowAll();

	//	�w���v�\��
	Help.Show();

	//	�}�E�X�J�[�\���\��
	if(nProcess==PROCESS_MAIN ||
	   nProcess==PROCESS_STARTSIGN ||
	   nProcess==PROCESS_HELP) mos.Show();

	//	���N�G�X�g�\��
	ReqCarrot.ShowFont();

	//	�T�C���\��
	StartSign.Show();
	ClearSign.Show();
	FailureSign.Show();

	//	��ʍX�V
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�ݒ�

void appFarm::SetFarmNo(int n)
{
	FarmNo=n;
}
