//
//	�t���[���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/08/21
//

#ifndef _FARMFRAME_H_
#define _FARMFRAME_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�萔��`

#define FF_PAT_MAP	9

///////////////////////////////////////////////////////////
//	�N���X�錾

class farmFrame;

///////////////////////////////////////////////////////////
//	�N���X

class farmFrame
{
	public:
		void	CreateFrame();
		void	ReleaseFrame();

		void	SetPos(int,int);

		void	Show();

	private:
		afBitmap	BmpMap;
		afPattern	dPatMap[FF_PAT_MAP];
		int	PosX,PosY;
};

#endif	//	_FARMFRAME_H_
