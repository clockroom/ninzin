//
//	���ʉ����ʃN���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/06
//

#ifndef _OPTSEVOLUME_H_
#define _OPTSEVOLUME_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�萔��`

#define OS_VOLUME_NONE	1000

///////////////////////////////////////////////////////////
//	�N���X�錾

class optSEVolume;

///////////////////////////////////////////////////////////
//	�N���X

class optSEVolume
{
	public:
		void	CreateSEVolume();
		void	ReleaseSEVolume();

		void	SetPos(int,int);
		void	SetVolume(int);

		int		GetVolume();
		int		IsVolume(int,int);

		void	Show();

	private:
		afBitmap	BmpVolume;
		int	PosX,PosY;
		int	Volume;
};

#endif	//	_OPTSEVOLUME_H_
