//
//	�J�n�T�C���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/07
//	Last  Edition 2001/09/07
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include "libfont.h"
#include "libsound.h"
#include "farmstartsign.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDSIGN	140

///////////////////////////////////////////////////////////
//	�쐬

void farmStartSign::CreateStartSign()
{
	PosX=0;
	PosY=0;
	FarmNo=0;
	cProg=ENDSIGN;
}

void farmStartSign::ReleaseStartSign()
{
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void farmStartSign::ResetStartSign()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void farmStartSign::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void farmStartSign::SetFarmNo(int n)
{
	FarmNo=n;
}

///////////////////////////////////////////////////////////
//	�擾

bool farmStartSign::IsEndSign()
{
	if(cProg<ENDSIGN) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	�X�V

void farmStartSign::Update()
{
	if(cProg>=ENDSIGN) return;
	cProg++;
}

///////////////////////////////////////////////////////////
//	�\��

void farmStartSign::Show()
{
	afScreen	scr;
	libFont		lf;
	libSound	ls;
	int		x,b;
	bool	fn;
	char	str[32];

	if(cProg>=ENDSIGN) return;
	if(cProg<0) cProg=0;

	//	���ʐݒ�
	x=0;
	b=32;
	fn=true;
	sprintf(str,"16%02d",FarmNo);

	//	�ύX
	if(0 FROMTO(cProg) 20)
	{
		x=-(1<<9)>>(cProg/2);
		b=cProg*32/20;
	}
	if(20 FROMTO(cProg) 120)
	{
		if((cProg-20)%50>=25) fn=false;
	}
	if(120 FROMTO(cProg) 140)
	{
		x=1<<((cProg-120)/2);
		b=(139-cProg)*32/20;
	}

	//	�\��
	scr.SetDrawArea(0,0,480,480);
	lf.BlendFont(PosX+x,PosY,b,"21farm");
	if(fn) lf.BlendFont(PosX+x+132,PosY+4,b,str);
	scr.SetDrawArea();

	//	�����Đ�
	if(cProg==  0) ls.PlaySound(17);
	if(cProg==120) ls.PlaySound(18);
	if(21 FROMTO(cProg) 121)
	{
		if((cProg-20)%50==0) ls.PlaySound(19);
	}
}
