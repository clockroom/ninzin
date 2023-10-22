//
//	���y���C�u���� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/21
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libmusic.h"

///////////////////////////////////////////////////////////
//	�萔��`

#define MUSIC_BGM	5

///////////////////////////////////////////////////////////
//	�N���X�ϐ���`

afMusic  libMusic::dMsc1BGM[MUSIC_BGM];
afMusic2 libMusic::dMsc2BGM[MUSIC_BGM];
bool	 libMusic::fDirectMusic=false;

///////////////////////////////////////////////////////////
//	������

void libMusic::InitLibrary(int no)
{
	DWORD	dls[]={0,0,4,4,4};
	DWORD	dle[]={0,0,20,164,116};
	bool	dfr[]={false,false,true,true,true};
	char	str[256];

	if(fDirectMusic)
	{
		if(dMsc2BGM[no].IsPlaying()) return;
		sprintf(str,"music\\music%02d.mid",no+10);
		dMsc2BGM[no].LoadMusic(str);
		dMsc2BGM[no].SetLoopPointByBeat(dls[no],dle[no]);
		dMsc2BGM[no].SetRepeat(dfr[no]);
	}
	else
	{
		if(dMsc1BGM[no].IsPlaying()) return;
		sprintf(str,"music\\music%02d.mid",no);
		dMsc1BGM[no].SetFileName(str);
		dMsc1BGM[no].SetRepeat(dfr[no]);
	}
}

void libMusic::FinalLibrary()
{
	int	i;

	for(i=0;i<MUSIC_BGM;i++)
	{
		if(dMsc2BGM[i].IsPlaying()) continue;
		dMsc2BGM[i].ReleaseMusic();
	}
}

///////////////////////////////////////////////////////////
//	�o�͕�����ݒ�

void libMusic::SetOutputSystem(bool f)
{
	fDirectMusic=f;
}

///////////////////////////////////////////////////////////
//	�Đ�

void libMusic::PlayMusic(int no)
{
	if(fDirectMusic)
	{
		if(dMsc2BGM[no].IsPlaying()) return;
		StopMusic();
		dMsc2BGM[no].Play();
	}
	else
	{
		if(dMsc1BGM[no].IsPlaying()) return;
		StopMusic();
		dMsc1BGM[no].Play();
	}
}

///////////////////////////////////////////////////////////
//	��~

void libMusic::StopMusic()
{
	afMusic ::StopAll();
	afMusic2::StopAll();
}
