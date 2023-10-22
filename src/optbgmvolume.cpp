//
//	�a�f�l�����ʃN���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "libcarrot.h"
#include "optbgmvolume.h"

///////////////////////////////////////////////////////////
//	�쐬

void optBGMVolume::CreateBGMVolume()
{
	//	�r�b�g�}�b�v�ǂݍ���
	BmpVolume.LoadBitmap("bitmap\\object07.bmp");

	//	������
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
//	�ݒ�

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
//	�擾

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
//	�\��

void optBGMVolume::Show()
{
	libFont		lf;
	libCarrot	lc;

	if(fEnable)
	{
		lf.PutFont(PosX,PosY+9,"23�a�f�l�̉���");
		BmpVolume.Opaque(PosX+208,PosY,0,0,300,48);
		lc[11].Put(PosX+227+(Volume+10)*12,PosY+4);
	}
	else
	{
		lf.BrightFont(PosX,PosY+9,56,"23�a�f�l�̉���");
		BmpVolume.BrightOpaque(PosX+208,PosY,56,0,0,300,48);
		lc[11].Bright(PosX+227+(Volume+10)*12,PosY+4,56);
	}
}
