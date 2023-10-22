//
//	�G���f�B���O�A�v���P�[�V���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/16
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "main.h"
#include "libmusic.h"
#include "fileplaydata.h"
#include "appfade.h"
#include "apphome.h"
#include "appending.h"

///////////////////////////////////////////////////////////
//	�O���[�o���ϐ�

appEnding AppEnding;

///////////////////////////////////////////////////////////
//	�\�z

appEnding::appEnding():OscFrmLim(20,5)
{
}

///////////////////////////////////////////////////////////
//	������

void appEnding::InitApp()
{
	libMusic		lm;
	filePlayData	fpd;
	int	gw,bw;

	//	�}�E�X������
	mos.ResetKey();

	//	�r�b�g�}�b�v�ǂݍ���
	BmpMsg1.LoadBitmap("bitmap\\object03.bmp");
	BmpMsg2.LoadBitmap("bitmap\\object04.bmp");
	BmpMsg3.LoadBitmap("bitmap\\object05.bmp");
	BmpStaff.LoadBitmap("bitmap\\object06.bmp");

	//	�����N�擾
	fpd.LoadPlayData();
	fpd.GetTotalRecord(&gw,&bw,NULL);
	if(bw<=gw) fRankA=true;
	else	   fRankA=false;

	//	BGM��~
	lm.StopMusic();

	//	�t�F�[�h�C��
	ms.Clear();
	DrawObject();
	AppFade.CallFade(AF_FADE_BLACKIN,16,this,(FPAPPFUNC)appEnding::Main);
}

void appEnding::FinalApp()
{
	BmpMsg1.ReleaseBitmap();
	BmpMsg2.ReleaseBitmap();
	BmpMsg3.ReleaseBitmap();
	BmpStaff.ReleaseBitmap();

	//	�z�[���ֈړ�
	SetActiveApp(&AppHome,(FPAPPFUNC)appHome::InitApp);
}

///////////////////////////////////////////////////////////
//	���C��

void appEnding::Main()
{
	//	�}�E�X�X�V
	mos.UpdateKey();

	//	�\��
	ms.Clear();
	DrawObject();
	ms.Refresh();

	//	�X�^�b�t���[����
	if(mos.GetKeyL()==KEY_PULL)
	{
		cProg=0;
		AppFade.CallFade(AF_FADE_BLACKOUT,16,this,(FPAPPFUNC)appEnding::StaffRoll);
	}
}

///////////////////////////////////////////////////////////
//	�X�^�b�t���[��

void appEnding::StaffRoll()
{
	//	�t���[�����~�b�^
	if(!OscFrmLim) return;

	//	�\��
	ms.Clear();
	BmpStaff.Opaque(120,520-cProg,0,0,402,162);
	ms.Refresh();

	//	�J�E���g
	if(++cProg>840) SetActiveApp(this,APP_FINAL);
}

///////////////////////////////////////////////////////////
//	�I�u�W�F�N�g�`��

void appEnding::DrawObject()
{
	if(!fRankA)
	{
		BmpMsg1.Opaque(110,112,0,0,406,60);
		BmpMsg2.Opaque(134,208,0,0,374,70);
		BmpMsg3.Opaque(60,304,0,0,522,68);
	}
	else
	{
		BmpMsg1.Opaque(110,160,0,0,406,60);
		BmpMsg2.Opaque(134,256,0,0,374,70);
	}
}
