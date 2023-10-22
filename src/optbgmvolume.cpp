//
//	ＢＧＭ音音量クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "optbgmvolume.h"

///////////////////////////////////////////////////////////
//	作成

void optBGMVolume::CreateBGMVolume()
{
	//	ビットマップ読み込み
	BmpVolume.LoadBitmap("bitmap\\object07.bmp");

	//	初期化
	PosX=0;
	PosY=0;
	Volume=-10;
	fEnable=false;
}

void optBGMVolume::ReleaseBGMVolume()
{
	BmpVolume.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	設定

void optBGMVolume::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optBGMVolume::SetVolume(int vol)
{
	Volume=vol;
}

void optBGMVolume::SetEnable(bool f)
{
	fEnable=f;
}

///////////////////////////////////////////////////////////
//	取得

int optBGMVolume::GetVolume()
{
	return Volume;
}

int optBGMVolume::IsVolume(int mx,int my)
{
	int	i;
	int	x;

	mx-=PosX;
	my-=PosY;

	if(!fEnable)	   return OB_VOLUME_NONE;
	if(my<4 || 36<=my) return OB_VOLUME_NONE;
	for(i=0;i<=20;i++)
	{
		x=231+i*12;
		if(x<=mx && mx<x+12) return i-10;
	}

	return OB_VOLUME_NONE;
}

///////////////////////////////////////////////////////////
//	表示

void optBGMVolume::Show()
{
	libFont		lf;
	libCarrot	lc;

	if(fEnable)
	{
		lf.PutFont(PosX,PosY+9,"23ＢＧＭの音量");
		BmpVolume.Opaque(PosX+208,PosY,0,0,300,48);
		lc[11].Put(PosX+227+(Volume+10)*12,PosY+4);
	}
	else
	{
		lf.BrightFont(PosX,PosY+9,56,"23ＢＧＭの音量");
		BmpVolume.BrightOpaque(PosX+208,PosY,56,0,0,300,48);
		lc[11].Bright(PosX+227+(Volume+10)*12,PosY+4,56);
	}
}
