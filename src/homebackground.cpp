//
//	�w�i�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/28
//	Last  Edition 2001/09/02
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "homebackground.h"

///////////////////////////////////////////////////////////
//	�쐬

void homeBackGround::CreateBackGround()
{
	//	�p�^�[���쐬
	BmpBackGround.LoadBitmap("bitmap\\map05.bmp",true);
	PatBackGround.CreatePattern(&BmpBackGround,0,0,64,64);

	//	������
	cProg=-1;
}

void homeBackGround::ReleaseBackGround()
{
	BmpBackGround.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�X�V

void homeBackGround::Update()
{
	if(++cProg==64) cProg=0;
}

///////////////////////////////////////////////////////////
//	�\��

void homeBackGround::Show()
{
	if(cProg<0) cProg=0;

	PatBackGround.TileOpaque(-cProg,cProg-64,640+64,480+64);
}
