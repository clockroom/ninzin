//
//	マップクラス by ClocoRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/13
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libcursor.h"
#include "farmmap.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDPLANT	1000

///////////////////////////////////////////////////////////
//	作成

void farmMap::CreateMap()
{
	int	i;

	//	パターン作成
	BmpMap.LoadBitmap("bitmap\\map01.bmp",true);
	BmpColor.LoadBitmap("bitmap\\map06.bmp");
	for(i=0;i<FM_PAT_MAP;i++)
	{
		dPatMap[i].CreatePattern(&BmpMap,(i%4)*48,(i/4)*48,48,48);
	}
	for(i=0;i<4;i++)
	{
		dPatColor[i].CreatePattern(&BmpColor,i*8,0,8,8);
	}

	//	パターン設定
	pdPatCarrot=&dPatMap[0];
	pPatFarm  =&dPatMap[8];

	//	その他初期化
	PosX=0;
	PosY=0;
	cProg=ENDPLANT;
	ClearMap();
}

void farmMap::ReleaseMap()
{
	BmpMap.ReleaseBitmap();
}

void farmMap::ClearMap()
{
	int	i,j;

	for(i=0;i<8;i++)for(j=0;j<8;j++)
	{
		dMap[i][j]=0x08;
	}
}

///////////////////////////////////////////////////////////
//	リセット

void farmMap::ResetMap()
{
	BYTE	*p;
	int		i,j;
	int		a,b;
	int		n;

	//	マップリセット
	n=0;
	for(i=1;i<7;i++)for(j=1;j<7;j++)
	{
		dMap[i][j]|=0x10;

		if(dMap[i][j]&0x08) continue;
		dpMap[n++]=&dMap[i][j];
	}
	dpMap[n]=NULL;

	//	シャッフル
	for(i=0;n>0 && i<36;i++)
	{
		a=rand()%n;
		b=rand()%n;
		p=dpMap[a];
		dpMap[a]=dpMap[b];
		dpMap[b]=p;
	}

	cProg=-1;
}

///////////////////////////////////////////////////////////
//	設定

void farmMap::SetMap(BYTE (*dm)[8])
{
	int	i,j;

	//	初期化
	ClearMap();

	//	登録
	for(i=1;i<7;i++)for(j=1;j<7;j++)
	{
		dMap[i][j]=dm[i][j];
	}
}

void farmMap::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	取得

void farmMap::GetPos(int *px,int *py)
{
	if(px!=NULL) *px=PosX;
	if(py!=NULL) *py=PosY;
}

void farmMap::GetFarmPos(int *px,int *py,int x,int y)
{
	x=(x-PosX)/48;
	y=(y-PosY)/48;

	if(px!=NULL) *px=0;
	if(py!=NULL) *py=0;

	if(x<=0 || 7<=x) return;
	if(y<=0 || 7<=y) return;

	if(px!=NULL) *px=x;
	if(py!=NULL) *py=y;
}

bool farmMap::IsFarm(int x,int y)
{
	x=(x-PosX)/48;
	y=(y-PosY)/48;
	if(x<=0 || 7<=x) return false;
	if(y<=0 || 7<=y) return false;
	return true;
}

bool farmMap::IsEndPlant()
{
	if(cProg<ENDPLANT) return false;
	return true;
}

///////////////////////////////////////////////////////////
//	操作

bool farmMap::WaterCarrot(int mx,int my)
{
	BYTE	c;
	BYTE	d1,d2,d3,d4;
	int		fx,fy;

	if(!IsFarm(mx,my)) return false;

	GetFarmPos(&fx,&fy,mx,my);
	c=dMap[fx][fy];
	if(c&0x08) return false;
	if(c==0)   return false;

	d1=(dMap[fx-1][fy  ]^=c);
	d2=(dMap[fx+1][fy  ]^=c);
	d3=(dMap[fx  ][fy-1]^=c);
	d4=(dMap[fx  ][fy+1]^=c);
	if(d1&0x08 && d2&0x08 && d3&0x08 && d4&0x08) return false;

	return true;
}

BYTE farmMap::PullCarrot(int mx,int my)
{
	BYTE	c;
	int		fx,fy;

	if(!IsFarm(mx,my)) return 0x08;

	GetFarmPos(&fx,&fy,mx,my);
	c=dMap[fx][fy];
	dMap[fx][fy]=0x08;

	return c;
}

///////////////////////////////////////////////////////////
//	更新

void farmMap::Update()
{
	BYTE	*p;

	if(cProg>=ENDPLANT) return;
	if(++cProg<0) cProg=0;

	p=dpMap[cProg/5];
	if(p==NULL)
	{
		cProg=ENDPLANT;
		return;
	}
	*p&=0x0f;
}

///////////////////////////////////////////////////////////
//	表示

void farmMap::Show(int mx,int my,int f)
{
	BYTE	c;
	int		i,j;

	//	畑表示
	for(i=0;i<8;i++)for(j=0;j<8;j++)
	{
		pPatFarm->Opaque(PosX+i*48,PosY+j*48);
	}

	//	カーソル表示
	_ShowCursor(mx,my,f);

	//	ニンジン表示
	for(i=1;i<7;i++)for(j=1;j<7;j++)
	{
		c=dMap[i][j];
		if(c&0x18) continue;
		pdPatCarrot[c&0x07].Put(PosX+i*48,PosY+j*48);

		if(f==FM_SC_NONE) continue;
		if(IsFarm(mx,my)) continue;

		if(c&0x04) dPatColor[1].Put(PosX+i*48+11,PosY+j*48+39);
		else	   dPatColor[0].Put(PosX+i*48+11,PosY+j*48+39);
		if(c&0x02) dPatColor[2].Put(PosX+i*48+20,PosY+j*48+39);
		else	   dPatColor[0].Put(PosX+i*48+20,PosY+j*48+39);
		if(c&0x01) dPatColor[3].Put(PosX+i*48+29,PosY+j*48+39);
		else	   dPatColor[0].Put(PosX+i*48+29,PosY+j*48+39);
	}
}

void farmMap::_ShowCursor(int mx,int my,int f)
{
	libCursor	lc;
	BYTE	c;
	BYTE	d1,d2,d3,d4;
	int		fx,fy;

	if(f==FM_SC_NONE)  return;
	if(!IsFarm(mx,my)) return;

	//	中心表示
	GetFarmPos(&fx,&fy,mx,my);
	c=dMap[fx][fy];
	if(c&0x08) return;
	lc[(c&0x07)+4].Put(PosX+fx*48,PosY+fy*48);

	if(f==FM_SC_PULL) return;
	if(c==0) return;

	//	周囲表示
	d1=dMap[fx-1][fy];
	d2=dMap[fx+1][fy];
	d3=dMap[fx][fy-1];
	d4=dMap[fx][fy+1];
	if(!(d1&0x08)) lc[((c^d1)&0x07)+4].Put(PosX+fx*48-48,PosY+fy*48);
	if(!(d2&0x08)) lc[((c^d2)&0x07)+4].Put(PosX+fx*48+48,PosY+fy*48);
	if(!(d3&0x08)) lc[((c^d3)&0x07)+4].Put(PosX+fx*48,PosY+fy*48-48);
	if(!(d4&0x08)) lc[((c^d4)&0x07)+4].Put(PosX+fx*48,PosY+fy*48+48);
}
