//
//	�������C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/06
//	Last  Edition 2001/09/20
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libsound.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define SND_SE	22

///////////////////////////////////////////////////////////
//	�N���X�ϐ�

afSound libSound::dSndSE[SND_SE];

///////////////////////////////////////////////////////////
//	������

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
//	�Đ�

void libSound::PlaySound(int no)
{
	dSndSE[no].Play();
}
