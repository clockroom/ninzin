//
//	�Z�N�V�������N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/01
//	Last  Edition 2001/09/23
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "homesectionname.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	�쐬

void homeSectionName::CreateSectionName()
{
	//	������
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
}

void homeSectionName::ReleaseSectionName()
{
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void homeSectionName::ResetSectionName()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void homeSectionName::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool homeSectionName::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�X�V

void homeSectionName::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==30) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void homeSectionName::Show()
{
	libFont		lf;
	int	px;

	if(cProg<0) cProg=0;

	//	�����\���P
	px=PosX;
	if(0 FROMTO(cProg) 22) px+=(1<<10)>>(cProg/2);
	lf.PutFont(px,PosY,"21farm");

	//	�����\���Q
	if(cProg<8) return;
	px=PosX;
	if(8 FROMTO(cProg) 30) px+=(1<<10)>>((cProg-8)/2);
	lf.PutFont(px+64,PosY+52,"21select");
}
