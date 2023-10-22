//
//	�I�v�V�����A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "libfont.h"
#include "libsound.h"
#include "libcursor.h"
#include "libcarrot.h"
#include "appfade.h"
#include "apptitle.h"
#include "appoption.h"

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appOption AppOption;

///////////////////////////////////////////////////////////
//	�\�z

appOption::appOption():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	������

void appOption::InitApp()
{
	libCursor	lc;

	//	���C�u����������
	libFont::InitLibrary(16);
	libFont::InitLibrary(23);
	libFont::InitLibrary(24);
	libFont::InitLibrary(25);
	libSound::InitLibrary();
	libSound::InitLibrary(1,3);
	libSound::InitLibrary(2,1);
	libSound::InitLibrary(3,1);
	libSound::InitLibrary(4,1);
	libSound::InitLibrary(11,1);
	libCursor::InitLibrary();
	libCarrot::InitLibrary();

	//	�}�E�X������
	mos.ResetKey();
	lc.ProvideMouseCursor(&mos,0);

	//	�I�v�V�����ǂݍ���
	Option.LoadOption();

	//	�Z�N�V������������
	SectionName.CreateSectionName();
	SectionName.SetPos(32,0+40);

	//	�a�f�l����������
	BGMOutput.CreateBGMOutput();
	BGMOutput.SetPos(64,80+40);
	BGMOutput.SetBGMOutput(Option.GetBGMOutput());

	//	�a�f�l���ʏ�����
	BGMVolume.CreateBGMVolume();
	BGMVolume.SetPos(64,128+40);
	BGMVolume.SetVolume(Option.GetBGMVolume());
	BGMVolume.SetEnable(BGMOutput.GetBGMOutput());

	//	���ʉ����ʏ�����
	SEVolume.CreateSEVolume();
	SEVolume.SetPos(64,184+40);
	SEVolume.SetVolume(Option.GetSEVolume());

	//	����{�^��������
	Mouse.CreateMouse();
	Mouse.SetPos(64,248+40);
	Mouse.SetTurnLR(Option.GetTurnLR());

	//	�L�^�폜�{�^��������
	DelRecord.CreateDelRecord();
	DelRecord.SetPos(64,288+40);
	DelRecord.SetDelCount(3);

	//	�߂�{�^��������
	Return.CreateReturn();
	Return.SetPos(64,364+40);

	//	��ʍ\�z
	ms.ClearWhite();
	SectionName.Show();
	BGMOutput.Show(-1,-1);
	BGMVolume.Show();
	SEVolume.Show();
	Mouse.Show(-1,-1);
	DelRecord.Show(-1,-1);
	Return.Show(-1,-1);

	//	�t�F�[�h�C��
	AppFade.CallFade(AF_FADE_WHITEIN,8,this,(FPAPPFUNC)appOption::Main);
}

void appOption::FinalApp()
{
	//	�I�v�V������������
	Option.SetBGMOutput(BGMOutput.GetBGMOutput());
	Option.SetBGMVolume(BGMVolume.GetVolume());
	Option.SetSEVolume(SEVolume.GetVolume());
	Option.SetTurnLR(Mouse.GetTureLR());
	Option.SaveOption();

	//	���C�u�������
	libFont::FinalLiblary();
	libSound::FinalLibrary();
	libCursor::FinalLibrary();
	libCarrot::FinalLibrary();

	//	�I�u�W�F�N�g���
	SectionName.ReleaseSectionName();
	BGMOutput.ReleaseBGMOutput();
	BGMVolume.ReleaseBGMVolume();
	SEVolume.ReleaseSEVolume();
	Mouse.ReleaseMouse();
	DelRecord.ReleaseDelRecord();
	Return.ReleaseReturn();

	//	�t�F�[�h�A�E�g
	AppFade.CallFade(AF_FADE_WHITEOUT,8,&AppTitle,(FPAPPFUNC)appTitle::InitAppFromOption);
}

///////////////////////////////////////////////////////////
//	���C��

void appOption::Main()
{
	//	�t���[�����~�b�^
	if(!OscFrmLim) return;

	//	�}�E�X�X�V
	mos.UpdateKey();

	//	�O�u�C�x���g
	_PreEvent();

	//	�\��
	_Show();
}

///////////////////////////////////////////////////////////
//	�O�u�C�x���g

void appOption::_PreEvent()
{
	if(_SelectBGMOutput()) return;
	if(_SelectBGMVolume()) return;
	if(_SelectSEVolume())  return;
	if(_SelectMouse())	   return;
	if(_DelRecordButton()) return;
	if(_ReturnButton())	   return;
}

///////////////////////////////////////////////////////////
//	�a�f�l�����ݒ�

bool appOption::_SelectBGMOutput()
{
	libSound	ls;
	int	mx,my;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	����
	if(!BGMOutput.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL)	   return false;

	//	����{�^���ݒ�
	BGMOutput.SetBGMOutput();
	BGMVolume.SetEnable(BGMOutput.GetBGMOutput());
	ls.PlaySound(11);

	return true;
}

///////////////////////////////////////////////////////////
//	�a�f�l���ʐݒ�

bool appOption::_SelectBGMVolume()
{
	libSound	ls;
	int	mx,my;
	int	ov,nv;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	�{�����[���擾
	ov=BGMVolume.GetVolume();
	nv=BGMVolume.IsVolume(mx,my);

	if(nv==OB_VOLUME_NONE) return false;
	if(nv==ov && mos.GetKeyL()!=KEY_PUSH) return false;
	if(mos.GetKeyL()==KEY_FREE) return false;

	//	�{�����[���ݒ�
	BGMVolume.SetVolume(nv);
	afMusic2::SetMasterVolume(nv);
	ls.PlaySound(1);

	return true;
}

///////////////////////////////////////////////////////////
//	���ʉ����ʐݒ�

bool appOption::_SelectSEVolume()
{
	libSound	ls;
	int	mx,my;
	int	ov,nv;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	�{�����[���擾
	ov=SEVolume.GetVolume();
	nv=SEVolume.IsVolume(mx,my);

	if(nv==OS_VOLUME_NONE) return false;
	if(nv==ov && mos.GetKeyL()!=KEY_PUSH) return false;
	if(mos.GetKeyL()==KEY_FREE) return false;

	//	�{�����[���ݒ�
	SEVolume.SetVolume(nv);
	afSound::SetMasterVolume(nv);
	ls.PlaySound(1);

	return true;
}

///////////////////////////////////////////////////////////
//	����{�^���ݒ�

bool appOption::_SelectMouse()
{
	libSound	ls;
	int	mx,my;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	����
	if(!Mouse.IsButton(mx,my))	return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;

	//	����{�^���ݒ�
	Mouse.SetTurnLR();
	ls.PlaySound(11);

	return true;
}

///////////////////////////////////////////////////////////
//	�L�^�폜

bool appOption::_DelRecordButton()
{
	libSound	ls;
	int		mx,my;
	char	str[1024];

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	����
	if(!DelRecord.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL)	   return false;
	mos.InvalidateKeyL();

	//	�����Đ�
	switch(DelRecord.GetDelCount())
	{
	case 3:ls.PlaySound(2);break;
	case 2:ls.PlaySound(3);break;
	case 1:ls.PlaySound(4);break;
	}

	//	�폜
	DelRecord.AddDelCount(-1);
	if(!DelRecord.IsDelete()) return true;

	GetFullPathFileName(str,"record.bin");
	remove(str);

	return true;
}

///////////////////////////////////////////////////////////
//	�^�C�g���ɖ߂�

bool appOption::_ReturnButton()
{
	libSound	ls;
	int	mx,my;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	����
	if(!Return.IsButton(mx,my)) return false;
	if(mos.GetKeyL()!=KEY_PULL) return false;
	mos.InvalidateKeyL();

	//	�^�C�g���ɖ߂�
	ls.PlaySound(7);
	SetActiveApp(this,APP_FINAL);

	return true;
}

///////////////////////////////////////////////////////////
//	�\��

void appOption::_Show()
{
	int	mx,my;

	//	�}�E�X�ʒu�擾
	mos.GetPos(&mx,&my);

	//	��ʏ���
	ms.ClearWhite();

	//	�Z�N�V�������\��
	SectionName.Show();

	//	�ݒ�\��
	BGMOutput.Show(mx,my);
	BGMVolume.Show();
	SEVolume.Show();
	Mouse.Show(mx,my);
	DelRecord.Show(mx,my);
	Return.Show(mx,my);

	//	�}�E�X�J�[�\���\��
	mos.Show();

	//	��ʍX�V
	ms.Refresh();
}
