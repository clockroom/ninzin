//
//	���j���[�N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/22
//	Last  Edition 2001/09/05
//

#ifndef _TITLEMENU_H_
#define _TITLEMENU_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>

///////////////////////////////////////////////////////////
//	�萔��`

#define TM_MENU_NONE	0
#define TM_MENU_START	1
#define	TM_MENU_OPTION	2
#define TM_MENU_END		3

///////////////////////////////////////////////////////////
//	�N���X�錾

class titleMenu;

///////////////////////////////////////////////////////////
//	�N���X

class titleMenu
{
	public:
		void	CreateMenu();
		void	ReleaseMenu();
		void	ResetMenuMenuCall();
		void	ResetMenuMain();

		void	SetPos(int,int);

		bool	IsEndEntrance();
		int		IsMenu(int,int);

		void	Update();
		void	Show(int,int);

	private:
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_TITLEMENU_H_
