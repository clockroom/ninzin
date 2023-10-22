//
//	�N���A�T�C���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/07/22
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "libfont.h"
#include "libsound.h"
#include "farmclearsign.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDSIGN	60

///////////////////////////////////////////////////////////
//	�쐬

void farmClearSign::CreateClearSign()
{
	PosX=0;
	PosY=0;
	cProg=ENDSIGN;
}

void farmClearSign::ReleaseClearSign()
{
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void farmClearSign::ResetClearSign()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void farmClearSign::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool farmClearSign::IsEndSign()
{
	if(cProg<ENDSIGN) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	�X�V

void farmClearSign::Update()
{
	if(cProg>=ENDSIGN) return;
	cProg++;
}

///////////////////////////////////////////////////////////
//	�\��

void farmClearSign::Show()
{
	afScreen	scr;
	libFont		lf;
	libSound	ls;
	int	x,b;

	if(cProg>=ENDSIGN) return;
	if(cProg<0) cProg=0;

	//	���ʐݒ�
	x=0;
	b=64;

	//	�ύX
	if(0 FROMTO(cProg) 20)
	{
		x=-(1<<9)>>(cProg/2);
		b=cProg*32/20;
	}
	if(40 FROMTO(cProg) 60)
	{
		x=1<<((cProg-40)/2);
		b=(59-cProg)*32/20;
	}

	//	�\��
	scr.SetDrawArea(0,0,480,480);
	lf.BlendFont(PosX+x,PosY,b,"21clear");
	scr.SetDrawArea();

	//	�����Đ�
	if(cProg== 0) ls.PlaySound(17);
	if(cProg==40) ls.PlaySound(18);
}
