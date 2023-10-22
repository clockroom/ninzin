//
//	�߂�{�^���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/06
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "optreturn.h"

///////////////////////////////////////////////////////////
//	�쐬

void optReturn::CreateReturn()
{
	//	������
	PosX=0;
	PosY=0;
}

void optReturn::ReleaseReturn()
{
}

///////////////////////////////////////////////////////////
//	�ݒ�

void optReturn::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool optReturn::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<3 || 169<=mx) return false;
	if(my<3 ||  24<=my) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	�\��

void optReturn::Show(int mx,int my)
{
	libFont	lf;

	//	�\��
	if(IsButton(mx,my)) lf.PutFont(PosX,PosY,"25�^�C�g���ɖ߂�1");
	else				lf.PutFont(PosX,PosY,"25�^�C�g���ɖ߂�0");
}
