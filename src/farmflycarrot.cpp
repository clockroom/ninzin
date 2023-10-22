//
//	飛行ニンジンクラス by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/26
//	Last  Edition 2001/09/07
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libsound.h"
#include "libcarrot.h"
#include "farmflycarrot.h"
#include "farmmap.h"
#include "farmcount.h"

///////////////////////////////////////////////////////////
//	定数定義

#define FLYSPEED	16
#define TYPE_PULL	0
#define TYPE_REQ	1

///////////////////////////////////////////////////////////
//	クラス変数

farmFlyCarrot *farmFlyCarrot::pChainTop=NULL;

farmCount *farmFlyCarrot::pCount=NULL;
farmMap   *farmFlyCarrot::pMap	=NULL;

///////////////////////////////////////////////////////////
//	初期化

void farmFlyCarrot::InitFlyCarrot(farmMap *pm,farmCount *pc)
{
	//	その他初期化
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
//	作成

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
//	全破棄

void farmFlyCarrot::DestroyAll()
{
	if(pChainTop!=NULL) pChainTop->_Destroy();
}

///////////////////////////////////////////////////////////
//	全更新

void farmFlyCarrot::UpdateAll()
{
	if(pChainTop!=NULL) pChainTop->_Update();
}

///////////////////////////////////////////////////////////
//	全表示

void farmFlyCarrot::ShowAll()
{
	if(pChainTop!=NULL) pChainTop->_Show();
}

///////////////////////////////////////////////////////////
//	全取得

bool farmFlyCarrot::IsEndFlyReqCarrot()
{
	if(pChainTop==NULL) return true;
	return pChainTop->_IsEndFlyReqCarrot();
}

///////////////////////////////////////////////////////////
//	構築

farmFlyCarrot::farmFlyCarrot(int t,BYTE n,int sx,int sy,int ex,int ey)
{
	//	チェーン追加
	pChainNext=pChainTop;
	pChainTop=this;

	//	オブジェクト設定
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

	//	チェーントップの場合
	if(pChainTop==this)
	{
		pChainTop=pChainNext;
		return;
	}

	//	チェーントップ以外の場合
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
//	破棄

void farmFlyCarrot::_Destroy()
{
	if(pChainNext!=NULL) pChainNext->_Destroy();
	delete this;
}

///////////////////////////////////////////////////////////
//	更新

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
//	表示

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
//	取得

bool farmFlyCarrot::_IsEndFlyReqCarrot()
{
	if(nType==TYPE_REQ)  return false;
	if(pChainNext==NULL) return true;
	return pChainNext->_IsEndFlyReqCarrot();
}
