//
//	�w���v�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/17
//	Last  Edition 2001/09/16
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "fileoption.h"
#include "farmhelp.h"

///////////////////////////////////////////////////////////
//	�쐬

void farmHelp::CreateHelp()
{
	PosX=0;
	PosY=0;
	nHelp=0;
	fShow=false;
}

void farmHelp::ReleaseHelp()
{
	BmpHelp.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�r�b�g�}�b�v�쐬

void farmHelp::_CreateHelpBitmap(int n)
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	fileOption	fo;
	afScreen	scr;
	afDC		dc;
	char	str[1024];
	char	hand[2][8];
	bool	fturn,fmos;

	//	�r�b�g�}�b�v�쐬
	BmpHelp.CreateBitmap(384,288);

	//	�E�B���h�E�쐬
	scr.SetWorkScreen(&BmpHelp);
	scr.SetDrawArea(0,0,384,288);
	lw.PutWindow(0,0,384,288);
	lf.PutFont(8,8,"22help");
	li.PutItem(8,40,368,240);
	scr.RestoreWorkScreen();
	scr.SetDrawArea();

	//	�{�^�������擾
	fo.LoadOption();
	fturn=fo.GetTurnLR();
	fmos =(GetSystemMetrics(SM_SWAPBUTTON)==0)?false:true;

	//	�{�^�����ݒ�
	if((!fturn && !fmos) || (fturn && fmos))
	{
		strcpy(hand[0],"��");
		strcpy(hand[1],"�E");
	}
	else
	{
		strcpy(hand[0],"�E");
		strcpy(hand[1],"��");
	}

	//	DC�擾
	BmpHelp.GetDC(&dc);

	//	�w���v�`��
	switch(n)
	{
	case 0:
		dc.Text(15, 48,"�� ���[��",16,true,RGB(255,192,192));
		dc.Text(15, 68,"�j���W���ɐ��������ĐF��ς��A�E�̕\�ŗv",16,true,RGB(255,255,255));
		dc.Text(15, 88,"������Ă���ʂ�Ɏ��n���Ă��������B",16,true,RGB(255,255,255));
		dc.Text(15,108,"�\�̌�����",16,true,RGB(255,255,255));
		dc.Text(15,128,"�i���n�������j�^�i�v�����ꂽ���j  �ł��B",16,true,RGB(255,255,255));
		dc.Text(15,156,"�� ������@",16,true,RGB(255,192,192));
		sprintf(str,"%s�N���b�N�Ő���������",hand[0]);
		dc.Text(15,176,str,16,true,RGB(255,255,255));
		sprintf(str,"%s�N���b�N�Ŏ��n����",hand[1]);
		dc.Text(15,196,str,16,true,RGB(255,255,255));
		dc.Text(15,224,"�� �ڂ����͕t���̎戵��������������������",16,true,RGB(255,192,192));
		break;

	case 1:
		dc.Text(15, 48,"�悤�����I�s�v�c�ȃj���W������",16,true,RGB(255,255,255));
		dc.Text(15, 76,"���̃Q�[���́u���̎O���F�v�̍��F�������Ƃ���",16,true,RGB(255,255,255));
		dc.Text(15, 96,"�F�V�т̃p�Y���Q�[���ł��B",16,true,RGB(255,255,255));
		dc.Text(15,124,"�� ���n�̗��K",16,true,RGB(255,192,192));
		sprintf(str,"�j���W���ɃJ�[�\�������킹��%s�N���b�N�����",hand[1]);
		dc.Text(15,144,str,16,true,RGB(255,255,255));
		dc.Text(15,164,"�j���W�������n���邱�Ƃ��ł��܂��B",16,true,RGB(255,255,255));
		dc.Text(15,184,"���̖ʂ͎��n�����ŃN���A�ł���̂ŁA�������n",16,true,RGB(255,255,255));
		dc.Text(15,204,"���Ă݂܂��傤�B",16,true,RGB(255,255,255));
		break;

	case 2:
		dc.Text(15, 48,"�� �����̗��K",16,true,RGB(255,192,192));
		sprintf(str,"�j���W���ɃJ�[�\�������킹��%s�N���b�N�����",hand[0]);
		dc.Text(15, 68,str,16,true,RGB(255,255,255));
		dc.Text(15, 88,"�j���W���ɐ��������邱�Ƃ��ł��܂��B",16,true,RGB(255,255,255));
		dc.Text(15,108,"�j���W���ɐ���������ƁA�����������j���W����",16,true,RGB(255,255,255));
		dc.Text(15,128,"����i�㉺���E�j�̃j���W���̐F���A����������",16,true,RGB(255,255,255));
		dc.Text(15,148,"�j���W���̐F�ƍ������ĕω����܂��B",16,true,RGB(255,255,255));
		dc.Text(15,168,"�j���W���ɃJ�[�\�������킹�����ɕ\�������g",16,true,RGB(255,255,255));
		dc.Text(15,188,"�̐F�́A������������̃j���W���̐F�ł��B",16,true,RGB(255,255,255));
		dc.Text(15,208,"���̖ʂ́A�Ԃ��j���W���ɂP�񂾂�������������",16,true,RGB(255,255,255));
		dc.Text(15,228,"�Ɏ��n����ƃN���A�ł��܂��B",16,true,RGB(255,255,255));
		break;

	case 3:
		dc.Text(15, 48,"�� �F�̕ω��ɂ���",16,true,RGB(255,192,192));
		dc.Text(15, 68,"�Ⴆ�΁A�Ԃ��j���W���ɐ���������ƁA��������",16,true,RGB(255,255,255));
		dc.Text(15, 88,"���j���W���̎���̃j���W���̐F���ԐF�ƍ�����",16,true,RGB(255,255,255));
		dc.Text(15,108,"�ĕω����邱�Ƃ͑O�̖ʂł킩��܂����B",16,true,RGB(255,255,255));
		dc.Text(15,128,"�t�ɁA���łɐԂ��j���W���ɐԐF��������ƁA��",16,true,RGB(255,255,255));
		dc.Text(15,148,"�F�͔����Ă��܂��܂��B",16,true,RGB(255,255,255));
		dc.Text(15,168,"���Ȃ݂ɁA�J�[�\���𔨂��牓������ƃj���W��",16,true,RGB(255,255,255));
		dc.Text(15,188,"�̐F�f�������\������܂��B",16,true,RGB(255,255,255));
		dc.Text(15,208,"���̖ʂ́A�Ԃ��j���W���ɂP�񂾂�������������",16,true,RGB(255,255,255));
		dc.Text(15,228,"�Ɏ��n����ƃN���A�ł��܂��B",16,true,RGB(255,255,255));
		break;

	case 4:
		dc.Text(15, 48,"�� �N���A���@",16,true,RGB(255,192,192));
		dc.Text(15, 68,"�E�̕\�ŗv������Ă���ʂ�Ƀj���W�������n��",16,true,RGB(255,255,255));
		dc.Text(15, 88,"��ƃN���A�ł��B",16,true,RGB(255,255,255));
		dc.Text(15,108,"�\�̌�����",16,true,RGB(255,255,255));
		dc.Text(15,128,"�i���n�������j�^�i�v�����ꂽ���j  �ł��B",16,true,RGB(255,255,255));
		dc.Text(15,148,"���̖ʂ̏ꍇ�́A���E�ԁE���F�̃j���W��������",16,true,RGB(255,255,255));
		dc.Text(15,168,"����P�{�����n����ƃN���A�ł��B",16,true,RGB(255,255,255));
		dc.Text(15,188,"���n���������v�����ꂽ��������Ƒ����s�ł�",16,true,RGB(255,192,192));
		dc.Text(15,208,"�̂ŋC��t���Ă��������B",16,true,RGB(255,192,192));
		break;

	case 5:
		dc.Text(15, 48,"�� �ڕW�萔",16,true,RGB(255,192,192));
		dc.Text(15, 68,"�E���́g�v���������h�ƕ\������Ă��鏊�̂���",16,true,RGB(255,255,255));
		dc.Text(15, 88,"�ɉE�ɂ��鐔���͖ڕW�萔�ł��B",16,true,RGB(255,255,255));
		dc.Text(15, 108,"�萔�Ƃ̓j���W���ɐ����������񐔂̂��Ƃł��B",16,true,RGB(255,255,255));
		dc.Text(15, 128,"�萔���ڕW�萔�������Ă����s�ɂ͂Ȃ�܂���",16,true,RGB(255,255,255));
		dc.Text(15, 148,"���A�ł��邾���ڕW�萔�ɋ߂��萔�ł̃N���A��",16,true,RGB(255,255,255));
		dc.Text(15, 168,"�ڎw���Ċ撣���Ă��������B",16,true,RGB(255,255,255));
		dc.Text(15, 188,"�Ȃ��A�j���W���ɐ�������������ɂ����P�x����",16,true,RGB(255,255,255));
		dc.Text(15, 208,"�j���W���ɐ���������ƂP�肾���߂��܂��B",16,true,RGB(255,255,255));
		break;

	case 18:
		dc.Text(15, 48,"�� ���n�̃^�C�~���O",16,true,RGB(255,192,192));
		dc.Text(15, 68,"���n�́A�K�������������������ƂɈ�C�ɂ�����",16,true,RGB(255,255,255));
		dc.Text(15, 88,"���Ƃ͌���܂���B",16,true,RGB(255,255,255));
		dc.Text(15, 108,"���������Ă���Œ��Ɏ��n���Ȃ���΂Ȃ�Ȃ���",16,true,RGB(255,255,255));
		dc.Text(15, 128,"�����̐悢�������݂��܂��B",16,true,RGB(255,255,255));
		dc.Text(15, 148,"���̖ʂ͂��������p�^�[���̂ق�̈��ł��B",16,true,RGB(255,255,255));
		dc.Text(15, 168,"�����A�ǂ�����ĉ����܂����H",16,true,RGB(255,255,255));
		break;

	case 25:
		dc.Text(15, 48,"�� �^�C���A�^�b�N�I�I",16,true,RGB(255,192,192));
		dc.Text(15, 68,"���S�̂��j���W���Ŗ��߂�����Ĉꌩ�����",16,true,RGB(255,255,255));
		dc.Text(15, 88,"�Ɍ����邯�ǁA���͂��̂������ȒP�B",16,true,RGB(255,255,255));
		dc.Text(15, 108,"�����āA�Ђ�������n���邾���ŗǂ��񂾂���B",16,true,RGB(255,255,255));
		sprintf(str,"���̖ʂł͔�ꂽ������������x�߂ĂƂɂ���%s",hand[1]);
		dc.Text(15, 128,str,16,true,RGB(255,255,255));
		dc.Text(15, 148,"�N���b�N�A�^�C���A�^�b�N�ɒ��킾�I",16,true,RGB(255,255,255));
		break;
	}

	//	������@
	if(!fmos) strcpy(str,"�� ���N���b�N�Ńw���v�����");
	else	  strcpy(str,"�� �E�N���b�N�Ńw���v�����");
	dc.Text(136,260,str,16,true,RGB(255,255,255));

	//	DC���
	BmpHelp.ReleaseDC(&dc);
}

///////////////////////////////////////////////////////////
//	�ݒ�

void farmHelp::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool farmHelp::IsRequestAutoHelp(int no)
{
	switch(no)
	{
	case  1:
	case  2:
	case  3:
	case  4:
	case  5:
	case 18:
	case 25:
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////
//	����

void farmHelp::Open(int n)
{
	libSound	ls;

	_CreateHelpBitmap(n);
	ls.PlaySound(6);
	nHelp=n;
	fShow=true;
}

void farmHelp::Close()
{
	libSound	ls;

	BmpHelp.ReleaseBitmap();
	ls.PlaySound(7);
	fShow=false;
}

///////////////////////////////////////////////////////////
//	�\��

void farmHelp::Show()
{
	if(!fShow) return;

	if(BmpHelp.IsLost()) _CreateHelpBitmap(nHelp);
	BmpHelp.Put(PosX,PosY,0,0,384,288);
}
