//
//	�߂�{�^���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/02
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "homereturn.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	�쐬

void homeReturn::CreateReturn()
{
	//	������
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeReturn::ReleaseReturn()
{
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void homeReturn::ResetReturn()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void homeReturn::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool homeReturn::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<3 || 172<=mx) return false;
	if(my<4 ||  24<=my) return false;

	return true;;
}

bool homeReturn::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�X�V

void homeReturn::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==76) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void homeReturn::Show(int mx,int my)
{
	libFont		lf;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<56) return;

	//	�\���ʒu�ݒ�
	py=PosY;
	if(56 FROMTO(cProg) 76) py+=(1<<9)>>((cProg-56)/2);

	//	�\��
	if(IsButton(mx,my)) lf.BlendFont(PosX,py,24,"27�^�C�g���ɖ߂�1");
	else				lf.BlendFont(PosX,py,24,"27�^�C�g���ɖ߂�0");
}
