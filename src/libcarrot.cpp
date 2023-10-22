//
//	�j���W�����C�u���� by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/10
//	Last  Edition 2001/07/10
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libcarrot.h"

///////////////////////////////////////////////////////////
//	�N���X�ϐ�

afBitmap  libCarrot::BmpCarrot;
afPattern libCarrot::dPatCarrot[12];

///////////////////////////////////////////////////////////
//	������

void libCarrot::InitLibrary()
{
	int	i;

	BmpCarrot.LoadBitmap("bitmap\\carrot01.bmp");
	for(i=0;i<12;i++)
	{
		dPatCarrot[i].CreatePattern(&BmpCarrot,(i%4)*32,(i/4)*32,32,32);
	}
}

void libCarrot::FinalLibrary()
{
	BmpCarrot.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�I�y���[�^

afPattern &libCarrot::operator[](int n)
{
	return dPatCarrot[n];
}
