//
//	�Z�N�V�������N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/05
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "optsectionname.h"

///////////////////////////////////////////////////////////
//	�쐬

void optSectionName::CreateSectionName()
{
	//	������
	PosX=0;
	PosY=0;
}

void optSectionName::ReleaseSectionName()
{
}

///////////////////////////////////////////////////////////
//	�ݒ�

void optSectionName::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�\��

void optSectionName::Show()
{
	libFont	lf;

	lf.PutFont(PosX,PosY,"24option");
}
