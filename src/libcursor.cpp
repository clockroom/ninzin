//
//	�J�[�\�����C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/21
//	Last  Edition 2001/08/21
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libcursor.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define PAT_CURSOR	12

///////////////////////////////////////////////////////////
//	�N���X�ϐ�

afBitmap  libCursor::BmpCursor;
afPattern libCursor::dPatCursor[PAT_CURSOR];

///////////////////////////////////////////////////////////
//	������

void libCursor::InitLibrary()
{
	int	i;

	BmpCursor.LoadBitmap("bitmap\\cursor01.bmp");
	for(i=0;i<PAT_CURSOR;i++)
	{
		dPatCursor[i].CreatePattern(&BmpCursor,(i%4)*48,(i/4)*48,48,48);
	}
}

void libCursor::FinalLibrary()
{
	BmpCursor.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	��

void libCursor::ProvideMouseCursor(afMouse *pMos,int n)
{
	int	x,y;

	x=0; y=0;
	if(n==0) {x= 0; y= 0;}
	if(n==1) {x=-4; y=52;}
	if(n==2) {x= 7; y=30;}

	pMos->SetPattern(&dPatCursor[n]);
	pMos->SetHotSpot(x,y);
}

///////////////////////////////////////////////////////////
//	�I�y���[�^

afPattern &libCursor::operator[](int n)
{
	return dPatCursor[n];
}
