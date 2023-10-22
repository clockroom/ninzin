//
//	カウントクラス by ClockRoom 2001
//	Program by Y.Kumagai 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/08/19
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "farmcount.h"

///////////////////////////////////////////////////////////
//	作成

void farmCount::CreateCount()
{
	//	その他初期化
	PosX=0;
	PosY=0;
	ClearCount();
}

void farmCount::ReleaseCount()
{
}

void farmCount::ClearCount()
{
	int	i;

	for(i=0;i<8;i++)
	{
		dCount[i].cCarrot=0;
		dCount[i].ReqCarrot=0;
	}
}

///////////////////////////////////////////////////////////
//	設定

void farmCount::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void farmCount::AddCount(BYTE c)
{
	if(c&0x08) return;
	dCount[c&0x07].cCarrot++;
}

void farmCount::AddRequest(BYTE r)
{
	if(r&0x08) return;
	dCount[r&0x07].ReqCarrot++;
}

///////////////////////////////////////////////////////////
//	取得

void farmCount::GetPos(int *px,int *py)
{
	if(px!=NULL) *px=PosX;
	if(py!=NULL) *py=PosY;
}

bool farmCount::IsClear()
{
	int	i;

	for(i=0;i<8;i++)
	{
		if(dCount[i].cCarrot!=dCount[i].ReqCarrot)
		{
			return false;
		}
	}
	return true;
}

bool farmCount::IsFailure()
{
	int	i;

	for(i=0;i<8;i++)
	{
		if(dCount[i].cCarrot>dCount[i].ReqCarrot)
		{
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////
//	表示

void farmCount::Show()
{
	libFont		lf;
	libCarrot	lc;
	int		i;
	int		a,b;
	char	str1[32];
	char	str2[32];

	for(i=0;i<8;i++)
	{
		a=dCount[i].cCarrot;
		b=dCount[i].ReqCarrot;
		if(a==b) sprintf(str1,"11%d",a);
		if(a< b) sprintf(str1,"12%d",a);
		if(a> b) sprintf(str1,"13%d",a);
		sprintf(str2,"11 /%d",b);

		if(a==b)
		{
			lc[i].Blend(PosX,PosY+i*34,10);
			lf.BlendFont(PosX+34,PosY+i*34+14,10,str1);
			lf.BlendFont(PosX+34,PosY+i*34+14,10,str2);
		}
		else
		{
			lc[i].Put(PosX,PosY+i*34);
			lf.PutFont(PosX+34,PosY+i*34+14,str1);
			lf.PutFont(PosX+34,PosY+i*34+14,str2);
		}
	}
}
