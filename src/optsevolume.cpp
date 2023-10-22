//
//	効果音音量クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/17
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "optsevolume.h"

///////////////////////////////////////////////////////////
//	作成

void optSEVolume::CreateSEVolume()
{
	//	ビットマップ読み込み
	BmpVolume.LoadBitmap("bitmap\\object01.bmp");

	//	初期化
	PosX=0;
	PosY=0;
	Volume=-10;
}

void optSEVolume::ReleaseSEVolume()
{
	BmpVolume.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	設定

void optSEVolume::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optSEVolume::SetVolume(int vol)
{
	Volume=vol;
}

///////////////////////////////////////////////////////////
//	取得

int optSEVolume::GetVolume()
{
	return Volume;
}

int optSEVolume::IsVolume(int mx,int my)
{
	int	i;
	int	x;

	mx-=PosX;
	my-=PosY;

	if(my<4 || 36<=my) return OS_VOLUME_NONE;
	for(i=0;i<=20;i++)
	{
		x=231+i*12;
		if(x<=mx && mx<x+12) return i-20;
	}

	return OS_VOLUME_NONE;
}

///////////////////////////////////////////////////////////
//	表示

void optSEVolume::Show()
{
	libFont		lf;
	libCarrot	lc;

	lf.PutFont(PosX,PosY+9,"23効果音の音量");
	BmpVolume.Opaque(PosX+208,PosY,0,0,300,48);
	lc[11].Put(PosX+227+(Volume+20)*12,PosY+4);
}
