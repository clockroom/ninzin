//
//	�t�@�[�����X�g�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/07
//

#ifndef _HOMEFARMLIST_H_
#define _HOMEFARMLIST_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class filePlayData;
class homeFarmList;

///////////////////////////////////////////////////////////
//	�N���X

class homeFarmList
{
	public:
		homeFarmList();

		void	CreateFarmList(filePlayData*);
		void	ReleaseFarmList();
		void	ResetFarmList();

		void	SetPos(int,int);
		void	AddPage(int);

		int		IsFarm(int,int);
		int		IsButton(int,int);
		bool	IsEndEntrance();

		void	Update();
		void	Show(int,int);

	private:
		void	_CreateFarmListBitmap();

	private:
		filePlayData	*pPlayData;
		afBitmap	BmpFarmList;
		afBitmap	BmpButton;
		afPattern	dPatButton[4];
		int	PosX,PosY;
		int	Page;
		int	cProg;
		int	nFocus;
};

#endif	//	_HOMEFARMLIST_H_
