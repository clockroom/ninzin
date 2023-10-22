//
//	�s�v�c�ȃj���W���� by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/21
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "common.h"
#include "fileoption.h"
#include "workprotect.h"
#include "applogo.h"

///////////////////////////////////////////////////////////
//	�A�v���P�[�V�����ݒ�

static bool fAppName=SetAppName("�s�v�c�ȃj���W����");

///////////////////////////////////////////////////////////
//	�t�@�C���֐��錾

static bool _ExitProc();

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

afScreen ms;
afMouse  mos;

///////////////////////////////////////////////////////////
//	������

bool afInit()
{
	fileOption	fo;
	workProtect	wp;
	afErrorBox	eb;

	//	�v���e�N�g
	if(!wp.Protect() && !MODE_EDIT)
	{
		eb.SetTitle("�v���e�N�g �G���[ - �s�v�c�ȃj���W����");
		eb.SetMessage("\n�f�[�^�t�@�C���̍\�����s���ł��邽�߃v���e�N�g���ُ��ʒm���܂����B\n\n"
			"���̂����ꂩ�̌������l�����܂��B\n"
			"�P�j ���炩�̗��R�ɂ��\���t�@�C�����j�������B\n"
			"�Q�j ���̓}�b�v�f�[�^�̉��������݂�����肭�����Ȃ������B");
		eb.SetRepair("\n�����P�̏ꍇ�͖{�\�t�g�E�F�A���㏑���C���X�g�[�����Ă��������B\n"
			"�����Q�̏ꍇ�͌��ɖ߂����A�܂��͊撣���ăv���e�N�g��˔j���Ă��������B");
		eb.OpenBox();
		return false;
	}

	//	��ʍ쐬
	if(!ms.CreateScreen(640,480))
	{
		eb.SetTitle("�V�X�e�� �G���[ - �s�v�c�ȃj���W����");
		eb.SetMessage("�������Ɏ��s���܂����B\n�N���ł��܂���B");
		eb.OpenBox();
		return false;
	}

	//	�T�E���h�V�X�e��������
	fo.LoadOption();
	if(fo.GetDMInit()) afMusic2::InitMusic2();
	afSound::SetSoundQuality(16);

	//	�V�X�e���ݒ�
	SetExitProc(_ExitProc);

	//	�V�X�e���N��
	SetActiveApp(&AppLogo,APP_INIT);

	return true;
}

///////////////////////////////////////////////////////////
//	�I���v���V�[�W��

bool _ExitProc()
{
	ClipCursor(NULL);
	return true;
}

///////////////////////////////////////////////////////////
//	���C��

void afMain()
{
	RECT	rc;

	//	�J�[�\���ړ��͈͐ݒ�
	GetClipCursor(&rc);
	if(rc.left !=  2 || rc.top	 !=  2 ||
	   rc.right!=638 || rc.bottom!=478)
	{
		rc.left =  2;	rc.top	 =  2;
		rc.right=638;	rc.bottom=478;
		ClipCursor(&rc);
	}

	//	���C������
	CallActiveApp();
}
