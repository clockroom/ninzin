//
//	ＢＧＭ音量クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

#ifndef _OPTBGMVOLUME_H_
#define _OPTBGMVOLUME_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	定数定義

#define OB_VOLUME_NONE	1000

///////////////////////////////////////////////////////////
//	クラス宣言

class optBGMVolume;

///////////////////////////////////////////////////////////
//	クラス

class optBGMVolume
{
	public:
		void	CreateBGMVolume();
		void	ReleaseBGMVolume();

		void	SetPos(int,int);
		void	SetEnable(bool);
		void	SetVolume(int);

		int		GetVolume();
		int		IsVolume(int,int);

		void	Show();

	private:
		afBitmap	BmpVolume;
		int		PosX,PosY;
		int		Volume;
		bool	fEnable;
};

#endif	//	_OPTBGMVOLUME_H_
