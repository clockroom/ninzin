//
//	ファームマップファイル ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/09/15
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "common.h"
#include "filefarmmap.h"

///////////////////////////////////////////////////////////
//	構築

fileFarmMap::fileFarmMap()
{
	Clear();
}

///////////////////////////////////////////////////////////
//	消去

void fileFarmMap::Clear()
{
	int	i,j;

	for(i=0;i<8;i++)for(j=0;j<8;j++)
	{
		dMap[i][j]=0x08;
	}
	for(i=0;i<36;i++) dRequest[i]=0x08;

	nMusic=0;
	cRequest=0;
}

///////////////////////////////////////////////////////////
//	読み込み

void fileFarmMap::LoadFarmMap(int no)
{
	afErrorBox	eb;
	FILE	*fp;
	char	str[1024];
	char	buf[256];
	int		cno;
	int		a,b,c,d;

	//	消去
	Clear();

	//	マップオープン
	sprintf(buf,"farm\\farm%02d.map",no);
	GetFullPathFileName(str,buf);
	if((fp=fopen(str,"rt"))==NULL)
	{
		eb.SetTitle("エラー - 不思議なニンジン畑");
		eb.SetMessage("マップデータの読み込みに失敗しました。");
		eb.OpenBox();
		ExitProgram();
		return;
	}

	//	マップ読み込み
	while(fscanf(fp,"%d %d,%d,%d,%d",&cno,&a,&b,&c,&d)!=EOF)
	{
		switch(cno)
		{
		case  1:_LoadMusic(a);		break;
		case 11:_LoadCarrot(a,b,c);	break;
		case 12:_LoadRequest(a,b);	break;
		}
	}

	//	マップクローズ
	fclose(fp);
}

///////////////////////////////////////////////////////////
//	各読み込み

void fileFarmMap::_LoadMusic(int n)
{
	nMusic=n;
}

void fileFarmMap::_LoadCarrot(int x,int y,int c)
{
	dMap[x][y]=c;
}

void fileFarmMap::_LoadRequest(int c,int r)
{
	int	i;

	for(i=0;i<r;i++) dRequest[cRequest++]=c;
}

///////////////////////////////////////////////////////////
//	取得

int fileFarmMap::GetMusic()
{
	return nMusic;
}

BYTE (*fileFarmMap::GetMap())[8]
{
	return dMap;
}

BYTE *fileFarmMap::GetRequest()
{
	return dRequest;
}
