//
//	ファームリストクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/11
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "common.h"
#include "libfont.h"
#include "libitem.h"
#include "libsound.h"
#include "libwindow.h"
#include "libcarrot.h"
#include "fileplaydata.h"
#include "homefarmlist.h"

///////////////////////////////////////////////////////////
//	定数定義

#define ENDENTRANCE	1000

///////////////////////////////////////////////////////////
//	構築

homeFarmList::homeFarmList()
{
	Page=0;
}

///////////////////////////////////////////////////////////
//	作成

void homeFarmList::CreateFarmList(filePlayData *ppd)
{
	int	i;

	//	初期化
	pPlayData=ppd;
	PosX=0;
	PosY=0;
	cProg=ENDENTRANCE;
	nFocus=0;

	//	パターン作成
	BmpButton.LoadBitmap("bitmap\\button02.bmp");
	for(i=0;i<4;i++)
	{
		dPatButton[i].CreatePattern(&BmpButton,(i%2)*24,(i/2)*24,24,24);
	}

	//	ウィンドウ作成
	_CreateFarmListBitmap();
}

void homeFarmList::ReleaseFarmList()
{
	BmpFarmList.ReleaseBitmap();
	BmpButton.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	リセット

void homeFarmList::ResetFarmList()
{
	cProg=-1;
}

///////////////////////////////////////////////////////////
//	ビットマップ作成

void homeFarmList::_CreateFarmListBitmap()
{
	libFont		lf;
	libItem		li;
	libWindow	lw;
	libCarrot	lc;
	afScreen	scr;
	char	str[256];
	char	buf[256];
	int		gw,bw,bt;
	int		c,m;
	int		a,b;
	int		i;

	//	ビットマップ作成
	BmpFarmList.CreateBitmap(324,404,true);

	scr.SetWorkScreen(&BmpFarmList);
	scr.SetDrawArea(0,0,324,404);

	//	ベース描画
	lw.PutWindow(0,0,324,404);

	//	文字描画
	lf.PutFont( 8,8,"22farm");
	lf.PutFont(68,8,"22water");

	//	ファーム情報描画
	c=pPlayData->GetClearCount();
	c=(c<MAX_FARM)?c+1:MAX_FARM;
	m=(c-(Page*10+10)>=0)?10:c%10;
	for(i=0;i<m;i++)
	{
		//	項目描画
		li.PutItem(  8,32+i*34, 56,24);
		li.PutItem( 68,32+i*34, 56,24);
		li.PutItem(128,32+i*34,152,24);

		//	データ描画
		pPlayData->GetFarmRecord(&gw,&bw,&bt,Page*10+i+1);

		sprintf(str,"11%02d",Page*10+i+1);
		lf.PutFont(20,36+i*34,str);

		sprintf(str,"11%02d",gw);
		lf.PutFont(80,36+i*34,str);

		if(bw<100) sprintf(str,"11%02d",bw);
		else	   sprintf(str,"11--");
		if(bt<50000) sprintf(buf,"###t#%05.1f",(bt/5)/10.0);
		else		 sprintf(buf,"###t#---.-");
		strcat(str,buf);
		lf.PutFont(136,36+i*34,str);

		if(bw!=FP_NOCLEAR && bw!=FP_FIRSTLOAD)
		{
			a=bw-gw;
			b=11;
			if(a<=4) b=10;
			if(a<=2) b=9;
			if(a<=0) b=8;
			lc[b].Put(284,24+i*34);
		}
	}

	//	ページ送りボタン描画
	dPatButton[0].Put(268,372);
	dPatButton[2].Put(292,372);

	scr.RestoreWorkScreen();
	scr.SetDrawArea();
}

///////////////////////////////////////////////////////////
//	設定

void homeFarmList::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void homeFarmList::AddPage(int p)
{
	int	c;

	switch(p)
	{
	case -1:
		if(Page==0) return;
		Page--;
		break;

	case 1:
		c =pPlayData->GetClearCount()+1;
		c =(c>MAX_FARM)?MAX_FARM:c;
		c-=Page*10;
		if(c<=10) return;
		Page++;
		break;

	default:
		return;
	}

	_CreateFarmListBitmap();
}

///////////////////////////////////////////////////////////
//	取得

int homeFarmList::IsFarm(int mx,int my)
{
	int	i,c;

	//	座標系変換
	mx-=PosX;
	my-=PosY;

	//	検索
	for(i=0;i<10;i++)
	{
		if(mx<8 || 316<=mx) continue;
		if(my<32+i*34 || 56+i*34<=my) continue;
		break;
	}
	if(i==10) return 0;

	//	有効処理
	i+=Page*10+1;
	c =pPlayData->GetClearCount()+1;
	c =(c>MAX_FARM)?MAX_FARM:c;
	if(i>c) return 0;

	return i;
}

int homeFarmList::IsButton(int mx,int my)
{
	int	c;

	//	座標系変換
	mx-=PosX;
	my-=PosY;

	//	Y検索
	if(my<373 || 395<=my) return  0;

	//	X検索
	if(273<=mx && mx<287)
	{
		if(Page==0) return 0;
		return -1;
	}
	if(295<=mx && mx<309)
	{
		c =pPlayData->GetClearCount()+1;
		c =(c>MAX_FARM)?MAX_FARM:c;
		c-=Page*10;
		if(c<=10) return 0;
		return 1;
	}

	return 0;
}

bool homeFarmList::IsEndEntrance()
{
	if(cProg==ENDENTRANCE) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	更新

void homeFarmList::Update()
{
	if(cProg==ENDENTRANCE) return;
	if(++cProg==54) cProg=ENDENTRANCE;
}

///////////////////////////////////////////////////////////
//	表示

void homeFarmList::Show(int mx,int my)
{
	libFont		lf;
	libSound	ls;
	char	str[256];
	char	buf[256];
	int		gw,bw,bt;
	int		s,p;
	int		px;

	if(cProg<0) cProg=0;
	if(cProg<32) return;

	//	表示位置設定
	px=PosX;
	if(32 FROMTO(cProg) 54) px-=(1<<10)>>((cProg-32)/2);

	//	ウィンドウ表示
	if(BmpFarmList.IsLost()) _CreateFarmListBitmap();
	BmpFarmList.Put(px,PosY,0,0,324,404);

	//	選択表示
	s=IsFarm(mx,my);
	if(s!=0)
	{
		p=s-Page*10-1;

		//	カーソル
		dPatButton[3].Put(PosX-  8,PosY+32+p*34);
		dPatButton[1].Put(PosX+272,PosY+32+p*34);

		//	データ
		pPlayData->GetFarmRecord(&gw,&bw,&bt,s);

		sprintf(str,"12%02d",s);
		lf.PutFont(PosX+20,PosY+36+p*34,str);

		sprintf(str,"12%02d",gw);
		lf.PutFont(PosX+80,PosY+36+p*34,str);

		if(bw<100) sprintf(str,"12%02d",bw);
		else	   sprintf(str,"12--");
		if(bt<50000) sprintf(buf,"###t#%05.1f",(bt/5)/10.0);
		else		 sprintf(buf,"###t#---.-");
		strcat(str,buf);
		lf.PutFont(PosX+136,PosY+36+p*34,str);

		//	音声再生
		if(nFocus!=s) ls.PlaySound(15);
	}
	nFocus=s;
	
	//	ボタン点燈
	switch(IsButton(mx,my))
	{
	case -1:
		dPatButton[1].Put(PosX+268,PosY+372);
		break;
	case 1:
		dPatButton[3].Put(PosX+292,PosY+372);
		break;
	}

	//	音声再生
	if(cProg==34) ls.PlaySound(16);
}
