//
//	�R�s�[���C�g�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/08/30
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "titlecopyright.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define USELESSCOPYRIGHT	2000
#define	ENDENTRANCE			1000

///////////////////////////////////////////////////////////
//	�쐬

void titleCopyright::CreateCopyright()
{
	//	�r�b�g�}�b�v�ǂݍ���
	BmpCopyright.LoadBitmap("bitmap\\logo03.bmp");

	//	���̑�������
	PosX=0;
	PosY=0;
	cProg=USELESSCOPYRIGHT;
}

void titleCopyright::ReleaseCopyright()
{
	BmpCopyright.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void titleCopyright::ResetCopyrightMenuCall()
{
	cProg=-1;
}

void titleCopyright::ResetCopyrightMain()
{
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void titleCopyright::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool titleCopyright::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�X�V

void titleCopyright::Update()
{
	if(cProg==USELESSCOPYRIGHT) return;
	if(cProg==ENDENTRANCE)		return;
	if(++cProg<8) return;
	cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void titleCopyright::Show()
{
	int	b;

	if(cProg==USELESSCOPYRIGHT) return;
	if(cProg<0) cProg=0;

	b=32;
	if(0 FROMTO(cProg) 8) b=64-cProg*4;

	BmpCopyright.Bright(PosX,PosY,b,0,0,284,104);
}
