//
//	��s�j���W���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/26
//	Last  Edition 2001/09/07
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libsound.h"
#include "libcarrot.h"
#include "farmflycarrot.h"
#include "farmmap.h"
#include "farmcount.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define FLYSPEED	16
#define TYPE_PULL	0
#define TYPE_REQ	1

///////////////////////////////////////////////////////////
//	�N���X�ϐ�

farmFlyCarrot *farmFlyCarrot::pChainTop=NULL;

farmCount *farmFlyCarrot::pCount=NULL;
farmMap   *farmFlyCarrot::pMap	=NULL;

///////////////////////////////////////////////////////////
//	������

void farmFlyCarrot::InitFlyCarrot(farmMap *pm,farmCount *pc)
{
	//	���̑�������
	DestroyAll();
	pChainTop=NULL;
	pMap  =pm;
	pCount=pc;
}

void farmFlyCarrot::FinalFlyCarrot()
{
	DestroyAll();
}

///////////////////////////////////////////////////////////
//	�쐬

void farmFlyCarrot::CreateFlyPullCarrot(BYTE n,int x,int y)
{
	int	mx,my,cx,cy;
	int	sx,sy,ex,ey;
	int	fx,fy;

	pMap->GetFarmPos(&fx,&fy,x,y);
	pMap->GetPos(&mx,&my);
	pCount->GetPos(&cx,&cy);

	n&=0x07;
	sx=mx+fx*48+8;
	sy=my+fy*48+8;
	ex=cx+32;
	ey=cy+n*34;

	new farmFlyCarrot(TYPE_PULL,n,sx,sy,ex,ey);
}

void farmFlyCarrot::CreateFlyReqCarrot(BYTE n,int x,int y)
{
	libSound	ls;
	int	cx,cy;
	int	sx,sy,ex,ey;

	pCount->GetPos(&cx,&cy);

	n&=0x07;
	sx=x;
	sy=y;
	ex=cx+64;
	ey=cy+n*34;

	new farmFlyCarrot(TYPE_REQ,n,sx,sy,ex,ey);
	ls.PlaySound(10);
}

///////////////////////////////////////////////////////////
//	�S�j��

void farmFlyCarrot::DestroyAll()
{
	if(pChainTop!=NULL) pChainTop->_Destroy();
}

///////////////////////////////////////////////////////////
//	�S�X�V

void farmFlyCarrot::UpdateAll()
{
	if(pChainTop!=NULL) pChainTop->_Update();
}

///////////////////////////////////////////////////////////
//	�S�\��

void farmFlyCarrot::ShowAll()
{
	if(pChainTop!=NULL) pChainTop->_Show();
}

///////////////////////////////////////////////////////////
//	�S�擾

bool farmFlyCarrot::IsEndFlyReqCarrot()
{
	if(pChainTop==NULL) return true;
	return pChainTop->_IsEndFlyReqCarrot();
}

///////////////////////////////////////////////////////////
//	�\�z

farmFlyCarrot::farmFlyCarrot(int t,BYTE n,int sx,int sy,int ex,int ey)
{
	//	�`�F�[���ǉ�
	pChainNext=pChainTop;
	pChainTop=this;

	//	�I�u�W�F�N�g�ݒ�
	nType=t;
	nCarrot=n;
	SX=sx; SY=sy;
	EX=ex; EY=ey;
	cProg=-1;
}

farmFlyCarrot::~farmFlyCarrot()
{
	farmFlyCarrot	*p;
	afErrorBox	eb;

	//	�`�F�[���g�b�v�̏ꍇ
	if(pChainTop==this)
	{
		pChainTop=pChainNext;
		return;
	}

	//	�`�F�[���g�b�v�ȊO�̏ꍇ
	p=pChainTop;
	while(true)
	{
		if(p->pChainNext==this)
		{
			p->pChainNext=pChainNext;
			break;
		}
		p=p->pChainNext;
	}
}

///////////////////////////////////////////////////////////
//	�j��

void farmFlyCarrot::_Destroy()
{
	if(pChainNext!=NULL) pChainNext->_Destroy();
	delete this;
}

///////////////////////////////////////////////////////////
//	�X�V

void farmFlyCarrot::_Update()
{
	libSound	ls;

	if(pChainNext!=NULL) pChainNext->_Update();
	if(cProg++<FLYSPEED) return;

	ls.PlaySound(11);
	if(nType==TYPE_PULL) pCount->AddCount(nCarrot);
	if(nType==TYPE_REQ)  pCount->AddRequest(nCarrot);
	delete this;
}

///////////////////////////////////////////////////////////
//	�\��

void farmFlyCarrot::_Show()
{
	libCarrot	lc;
	int	x,y;
	int	a,b;

	if(pChainNext!=NULL) pChainNext->_Show();
	if(cProg>FLYSPEED) return;
	if(cProg<0) cProg=0;

	a =EX-SX;
	b =EY-SY;
	x =SX+a*cProg/FLYSPEED;
	y =SY+b*cProg/FLYSPEED;
	a =cProg-FLYSPEED/2;
	y-=128-a*a*2;
	lc[nCarrot].Put(x,y);
}

///////////////////////////////////////////////////////////
//	�擾

bool farmFlyCarrot::_IsEndFlyReqCarrot()
{
	if(nType==TYPE_REQ)  return false;
	if(pChainNext==NULL) return true;
	return pChainNext->_IsEndFlyReqCarrot();
}
