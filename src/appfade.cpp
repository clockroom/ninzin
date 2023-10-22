//
//	�t�F�[�h�A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "appfade.h"

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appFade AppFade;

///////////////////////////////////////////////////////////
//	�\�z

appFade::appFade():OscFrmLim(40,10)
{
}

///////////////////////////////////////////////////////////
//	������

void appFade::InitApp()
{
	//	������
	cProg=-1;

	//	�����ݒ�
	SetActiveApp(this,APP_MAIN);
}

void appFade::FinalApp()
{
	//	�r�b�g�}�b�v���
	BmpScreen.ReleaseBitmap();

	//	�����ݒ�
	SetActiveApp(pApp,fpFunc);
}

///////////////////////////////////////////////////////////
//	���C��

void appFade::Main()
{
	//	�t���[�����~�b�^
	if(!OscFrmLim) return;

	//	�J�E���g
	cProg++;
	if(cProg<0) return;
	if(cProg>Frame)
	{
		SetActiveApp(this,APP_FINAL);
		return;
	}

	//	�t�F�[�h
	switch(nFade)
	{
	case AF_FADE_NONE:	  _FadeNone();	  break;
	case AF_FADE_BLACKOUT:_FadeBlackOut();break;
	case AF_FADE_BLACKIN: _FadeBlackIn(); break;
	case AF_FADE_WHITEOUT:_FadeWhiteOut();break;
	case AF_FADE_WHITEIN: _FadeWhiteIn() ;break;
	}
}

///////////////////////////////////////////////////////////
//	�t�F�[�h����

void appFade::_FadeNone()
{
	BmpScreen.Opaque(0,0,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�u���b�N�A�E�g

void appFade::_FadeBlackOut()
{
	BmpScreen.BrightOpaque(0,0,32-cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�u���b�N�C��

void appFade::_FadeBlackIn()
{
	BmpScreen.BrightOpaque(0,0,cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�z���C�g�A�E�g

void appFade::_FadeWhiteOut()
{
	BmpScreen.BrightOpaque(0,0,32+cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�z���C�g�C��

void appFade::_FadeWhiteIn()
{
	BmpScreen.BrightOpaque(0,0,64-cProg*32/Frame,0,0,640,480);
	ms.Refresh();
}

///////////////////////////////////////////////////////////
//	�t�F�[�h�Ăяo��

void appFade::CallFade(int n,int f,afApp *p,FPAPPFUNC fp)
{
	//	�r�b�g�}�b�v�쐬
	BmpScreen.CreateBitmap(640,480);
	BmpScreen.ClipScreen(0,0,640,480);

	//	�t�F�[�h���ݒ�
	pApp=p;
	fpFunc=fp;
	nFade=n;
	Frame=f;

	//	�����ݒ�
	SetActiveApp(this,APP_INIT);
}
