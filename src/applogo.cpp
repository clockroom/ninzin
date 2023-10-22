//
//	���[�J���S�A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "applogo.h"
#include "apptitle.h"

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appLogo AppLogo;

///////////////////////////////////////////////////////////
//	�\�z

appLogo::appLogo():OscFrmLim(40,10)
{
}

///////////////////////////////////////////////////////////
//	������

void appLogo::InitApp()
{
	//	�r�b�g�}�b�v�ǂݍ���
	BmpLogo.LoadBitmap("bitmap\\logo01.bmp");

	//	������
	cProg=-1;

	//	�����ݒ�
	SetActiveApp(this,APP_MAIN);
}

void appLogo::FinalApp()
{
	//	�r�b�g�}�b�v���
	BmpLogo.ReleaseBitmap();

	//	�����ݒ�
	SetActiveApp(&AppTitle,(FPAPPFUNC)appTitle::InitAppFromLogo);
}

void appLogo::Main()
{
	//	�t���[�����~�b�^
	if(!OscFrmLim) return;

	//	�J�E���g
	if(++cProg<0) cProg=0;
	if(cProg>=128)
	{
		SetActiveApp(this,APP_FINAL);
		return;
	}

	//	�\��
	_Show();
}

///////////////////////////////////////////////////////////
//	�\��

void appLogo::_Show()
{
	//	��ʏ���
	ms.ClearWhite();

	//	�t�F�[�h�C��
	if(32 FROMTO(cProg) 48)
	{
		BmpLogo.BrightOpaque(184,208,(64-cProg)*2,0,0,272,64);
	}

	//	��~
	if(48 FROMTO(cProg) 96)
	{
		BmpLogo.Opaque(184,208,0,0,272,64);
	}

	//	�t�F�[�h�A�E�g
	if(96 FROMTO(cProg) 112)
	{
		BmpLogo.BrightOpaque(184,208,(cProg-80)*2,0,0,272,64);
	}

	//	��ʍX�V
	ms.Refresh();
}
