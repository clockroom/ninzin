//
//	�w���v�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/07
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "homehelp.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	�쐬

void homeHelp::CreateHelp()
{
	//	�r�b�g�}�b�v�쐬
	_CreateHelpBitmap();

	//	������
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeHelp::ReleaseHelp()
{
	BmpHelp.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�쐬

void homeHelp::_CreateHelpBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	afScreen	scr;
	afDC		dc;

	//	�r�b�g�}�b�v�쐬
	BmpHelp.CreateBitmap(272,100);

	//	�E�B���h�E�`��
	scr.SetWorkScreen(&BmpHelp);
	scr.SetDrawArea(0,0,272,100);
	lw.PutWindow(0,0,272,100);
	lf.PutFont(8,8,"22help");
	li.PutItem(8,36,256,56);
	scr.RestoreWorkScreen();
	scr.SetDrawArea();

	//	�����`��
	BmpHelp.GetDC(&dc);
	dc.Text(16,47,"�E�̃t�@�[���ꗗ�\����v���C��",16,true,RGB(255,255,255));
	dc.Text(16,67,"�����ʂ�I�����Ă��������B",16,true,RGB(255,255,255));
	BmpHelp.ReleaseDC(&dc);
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void homeHelp::ResetHelp()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void homeHelp::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool homeHelp::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�X�V

void homeHelp::Updata()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==68) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void homeHelp::Show()
{
	libSound	ls;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<48) return;

	//	�\���ʒu�ݒ�
	py=PosY;
	if(48 FROMTO(cProg) 68) py+=(1<<9)>>((cProg-48)/2);

	//	�w���v�\��
	if(BmpHelp.IsLost()) _CreateHelpBitmap();
	BmpHelp.Put(PosX,py,0,0,272,100);

	//	�����Đ�
	if(cProg==50) ls.PlaySound(16);
}
