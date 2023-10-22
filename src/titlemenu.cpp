//
//	���j���[�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/05
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "titlemenu.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define USELESSMENU	2000
#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	�쐬

void titleMenu::CreateMenu()
{
	//	���̑�������
	PosX=0;
	PosY=0;
	cProg=USELESSMENU;
}

void titleMenu::ReleaseMenu()
{
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void titleMenu::ResetMenuMenuCall()
{
	cProg=-1;
}

void titleMenu::ResetMenuMain()
{
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void titleMenu::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool titleMenu::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

int titleMenu::IsMenu(int mx,int my)
{
	if(PosX+12<=mx && mx<PosX+180 &&
	   PosY+ 6<=my && my<PosY+28)	return TM_MENU_START;
	if(PosX+38<=mx && mx<PosX+156 &&
	   PosY+42<=my && my<PosY+64)	return TM_MENU_OPTION;
	if(PosX+12<=mx && mx<PosX+181 &&
	   PosY+78<=my && my<PosY+101)	return TM_MENU_END;

	return TM_MENU_NONE;
}

///////////////////////////////////////////////////////////
//	�X�V

void titleMenu::Update()
{
	if(cProg==USELESSMENU) return;
	if(cProg==ENDENTRANCE) return;
	if(++cProg<18) return;
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void titleMenu::Show(int mx,int my)
{
	libFont	lf;
	int		x,n;

	if(cProg==USELESSMENU) return;
	if(cProg<0) cProg=0;

	//	�ߓn�\��
	if(0 FROMTO(cProg) 18)
	{
		x=1024>>cProg;
		lf.PutFont(PosX+x,PosY,"26�Q�[���X�^�[�g0");
		x=8192>>cProg;
		lf.PutFont(PosX+x,PosY+36,"26�I�v�V����0");
		x=65536>>cProg;
		lf.PutFont(PosX+x,PosY+72,"26�Q�[������߂�0");
		return;
	}

	//	���\��
	n=IsMenu(mx,my);
	if(n!=TM_MENU_START)  lf.PutFont(PosX,PosY,"26�Q�[���X�^�[�g0");
	else				  lf.PutFont(PosX,PosY,"26�Q�[���X�^�[�g1");
	if(n!=TM_MENU_OPTION) lf.PutFont(PosX,PosY+36,"26�I�v�V����0");
	else				  lf.PutFont(PosX,PosY+36,"26�I�v�V����1");
	if(n!=TM_MENU_END)	  lf.PutFont(PosX,PosY+72,"26�Q�[������߂�0");
	else				  lf.PutFont(PosX,PosY+72,"26�Q�[������߂�1");
}
