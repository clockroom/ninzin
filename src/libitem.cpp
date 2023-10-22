//
//	���ڃ��C�u���� by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/09
//	Last  Edition 2001/08/22
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libitem.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define PAT_MAP	9

///////////////////////////////////////////////////////////
//	�N���X�ϐ�

afBitmap  libItem::BmpMap;
afPattern libItem::dPatMap[PAT_MAP];

///////////////////////////////////////////////////////////
//	������

void libItem::InitLibrary()
{
	int	i;

	//	�p�^�[���쐬
	BmpMap.LoadBitmap("bitmap\\map04.bmp");
	for(i=0;i<PAT_MAP;i++)
	{
		dPatMap[i].CreatePattern(&BmpMap,(i%3)*8,(i/3)*8,8,8);
	}
}

void libItem::FinalLibrary()
{
	BmpMap.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�`��

void libItem::PutItem(int x,int y,int w,int h)
{
	int	m,n;
	int	i,j;

	w/=8; h/=8;
	for(i=0;i<w;i++)for(j=0;j<h;j++)
	{
		m=1; n=3;
		if(i==0)   m=0;
		if(i==w-1) m=2;
		if(j==0)   n=0;
		if(j==h-1) n=6;
		dPatMap[m+n].Put(x+i*8,y+j*8);
	}
}
