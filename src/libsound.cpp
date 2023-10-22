//
//	音声ライブラリ ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/06
//	Last  Edition 2001/09/20
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libsound.h"

///////////////////////////////////////////////////////////
//	定数定義

#define SND_SE	22

///////////////////////////////////////////////////////////
//	クラス変数

afSound libSound::dSndSE[SND_SE];

///////////////////////////////////////////////////////////
//	初期化

void libSound::InitLibrary()
{
	InitLibrary(6,1);
	InitLibrary(7,1);
}

void libSound::InitLibrary(int no,int poly)
{
	char	str[1024];
	char	buf[256];

	if(dSndSE[no].IsPlaying()) return;

	sprintf(buf,"sound\\sound%02d.wav",no);
	GetFullPathFileName(str,buf);
	dSndSE[no].LoadSound(str,poly);
}

void libSound::FinalLibrary()
{
	int	i;

	for(i=0;i<SND_SE;i++)
	{
		if(dSndSE[i].IsPlaying()) continue;
		dSndSE[i].ReleaseSound();
	}
}

///////////////////////////////////////////////////////////
//	再生

void libSound::PlaySound(int no)
{
	dSndSE[no].Play();
}
