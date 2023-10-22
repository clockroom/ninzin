//
//	���R�[�h�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/16
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "common.h"
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "fileplaydata.h"
#include "homerecord.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	�쐬

void homeRecord::CreateRecord(filePlayData *ppd)
{
	//	������
	pPlayData=ppd;
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;

	//	�r�b�g�}�b�v�쐬
	_CreateRecordBitmap();
}

void homeRecord::ReleaseRecord()
{
	BmpRecord.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void homeRecord::ResetRecord()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�쐬

void homeRecord::_CreateRecordBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	afScreen	scr;
	char	str[256];
	char	r;
	int		a;
	int		c,gw,bw,bt;

	//	�r�b�g�}�b�v�쐬
	BmpRecord.CreateBitmap(272,120);

	scr.SetWorkScreen(&BmpRecord);
	scr.SetDrawArea(0,0,272,120);

	//	�x�[�X�`��
	lw.PutWindow(0,0,272,120);

	//	�����`��
	lf.PutFont(8, 8,"22rank");
	lf.PutFont(8,64,"22record");

	//	���ڕ`��
	li.PutItem(  8,32, 48,24);
	li.PutItem( 64,32,200,24);
	li.PutItem(  8,88, 48,24);
	li.PutItem( 64,88, 64,24);
	li.PutItem(136,88,128,24);

	//	�f�[�^�擾
	c=pPlayData->GetClearCount();
	pPlayData->GetTotalRecord(&gw,&bw,&bt);

	//	�����N����
	r='F';
	if(c>=26) r='E';
	if(c==MAX_FARM)
	{
		a=bw-gw;
		r='D';
		if(a<=30) r='C';
		if(a<=10) r='B';
		if(a<= 0) r='A';
	}

	//	�����N�`��
	sprintf(str,"17%c",r);
	lf.PutFont(23,36,str);
	sprintf(str,"28%c",r);
	lf.PutFont(84,36,str);

	//	���R�[�h�`��
	sprintf(str,"11%02d",c);
	lf.PutFont(16,92,str);

	if(bw<1000) sprintf(str,"11%03d",bw);
	else	   sprintf(str,"11---");
	lf.PutFont(72,92,str);

	if(bt<500000) sprintf(str,"11t#%06.1f",bt/50.0);
	else		 sprintf(str,"11t#----.-");
	lf.PutFont(146,92,str);

	scr.RestoreWorkScreen();
	scr.SetDrawArea();
}

///////////////////////////////////////////////////////////
//	�ݒ�

void homeRecord::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool homeRecord::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�X�V

void homeRecord::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==60) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	�\��

void homeRecord::Show()
{
	libSound	ls;
	int	py;

	if(cProg<0) cProg=0;
	if(cProg<40) return;

	//	�\���ʒu�ݒ�
	py=PosY;
	if(40 FROMTO(cProg) 60) py+=(1<<9)>>((cProg-40)/2);

	//	�E�B���h�E�\��
	if(BmpRecord.IsLost()) _CreateRecordBitmap();
	BmpRecord.Put(PosX,py,0,0,272,120);

	//	�����Đ�
	if(cProg==42) ls.PlaySound(16);
}
