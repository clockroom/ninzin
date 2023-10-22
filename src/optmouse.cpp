//
//	����{�^���{�^���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/13
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "optmouse.h"

///////////////////////////////////////////////////////////
//	�쐬

void optMouse::CreateMouse()
{
	//	�r�b�g�}�b�v�ǂݍ���
	BmpMouse.LoadBitmap("bitmap\\object02.bmp");

	//	������
	PosX=0;
	PosY=0;
	fTurnLR=false;
}

void optMouse::ReleaseMouse()
{
	BmpMouse.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�ݒ�

void optMouse::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optMouse::SetTurnLR(bool f)
{
	fTurnLR=f;
}

void optMouse::SetTurnLR()
{
	fTurnLR=!fTurnLR;
}

///////////////////////////////////////////////////////////
//	�擾

bool optMouse::GetTureLR()
{
	return fTurnLR;
}

bool optMouse::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(mx<4 || 124<=mx) return false;
	if(my<6 ||  27<=my) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	�\��

void optMouse::Show(int mx,int my)
{
	libFont	lf;
	bool	fmos;

	//	�{�^���\��
	if(IsButton(mx,my)) lf.PutFont(PosX,PosY+2,"25����{�^��1");
	else				lf.PutFont(PosX,PosY+2,"25����{�^��0");

	//	�󋵕\��
	fmos=(GetSystemMetrics(SM_SWAPBUTTON)==0)?false:true;
	if((!fmos && !fTurnLR) || (fmos && fTurnLR))
	{
		lf.PutFont(PosX+208,PosY+2,"23�����");
		BmpMouse.Opaque(PosX+288,PosY,0,0,32,32);
		lf.PutFont(PosX+323,PosY+2,"23���n");
	}
	else
	{
		lf.PutFont(PosX+208,PosY+2,"23���n");
		BmpMouse.Opaque(PosX+288,PosY,0,0,32,32);
		lf.PutFont(PosX+323,PosY+2,"23�����");
	}
}
