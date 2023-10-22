//
//	���N�G�X�g�j���W���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/08
//	Last  Edition 2001/07/22
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "farmflycarrot.h"
#include "farmreqcarrot.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define ENDREQUEST	1000

///////////////////////////////////////////////////////////
//	�쐬

void farmReqCarrot::CreateReqCarrot()
{
	//	���̑�������
	PosX=0;
	PosY=0;
	cProg=ENDREQUEST;
	ClearReqCarrot();
}

void farmReqCarrot::ReleaseReqCarrot()
{
}

void farmReqCarrot::ClearReqCarrot()
{
	int	i;

	for(i=0;i<36;i++) dRequest[i]=0x08;
	Total =0;
	TotalB=0;
}

///////////////////////////////////////////////////////////
//	���Z�b�g

void farmReqCarrot::ResetReqCarrot()
{
	cProg =-1;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void farmReqCarrot::SetReqCarrot(BYTE *dr)
{
	BYTE	a,b;
	int		i,j;

	//	������
	ClearReqCarrot();

	//	�o�^
	for(i=0;i<36;i++)
	{
		if(dr[i]&0x08) break;
		dRequest[i]=dr[i]&0x07;
	}
	Total=TotalB=i;

	//	���בւ�
	for(j=0;j<35;j++)for(i=0;i<35-j;i++)
	{
		a=dRequest[i];
		b=dRequest[i+1];
		if(a<=b) continue;
		dRequest[i]  =b;
		dRequest[i+1]=a;
	}
}

void farmReqCarrot::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�擾

bool farmReqCarrot::IsEndRequest()
{
	if(cProg<ENDREQUEST) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	�X�V

void farmReqCarrot::Update()
{
	BYTE	r;

	if(cProg>=ENDREQUEST) return;
	cProg++;

	if(cProg>=60 && Total==0) cProg=ENDREQUEST;

	if(Total==0)   return;
	if(cProg<40)   return;
	if(cProg%5!=0) return;

	//	��s�j���W���쐬
	r=dRequest[--Total];
	farmFlyCarrot::CreateFlyReqCarrot(r,PosX+Total*10,PosY);

	if(cProg>=60 && Total==0) cProg=ENDREQUEST;
}

///////////////////////////////////////////////////////////
//	�\��

void farmReqCarrot::Show()
{
	libCarrot	lc;
	BYTE	r;
	int		i;
	int		x;

	if(Total==0) return;
	if(cProg>=ENDREQUEST) return;
	if(cProg<0) cProg=0;

	x=0;
	if(0 FROMTO(cProg) 20) x=(1<<9)>>(cProg/2);

	for(i=0;i<Total;i++)
	{
		r=dRequest[i];
		lc[r].Put(PosX+i*10-x,PosY);
	}
}

void farmReqCarrot::ShowFont()
{
	libFont	lf;
	int		x;

	if(cProg>=60) return;
	if(cProg<0) cProg=0;

	x=0;
	if( 0 FROMTO(cProg) 20) x=(1<<9)>>(cProg/2);
	if(40 FROMTO(cProg) 60) x=1<<((cProg-40)/2);

	lf.PutFont(PosX+TotalB*10-x,PosY+16,"22request");
}
