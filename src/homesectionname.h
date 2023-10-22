//
//	�Z�N�V�������N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/01
//	Last  Edition 2001/09/06
//

#ifndef _HOMESECTIONNAME_H_
#define _HOMESECTIONNAME_H_

///////////////////////////////////////////////////////////
//	�N���X�錾

class homeSectionName;

///////////////////////////////////////////////////////////
//	�N���X

class homeSectionName
{
	public:
		void	CreateSectionName();
		void	ReleaseSectionName();
		void	ResetSectionName();

		void	SetPos(int,int);

		bool	IsEndEntrance();

		void	Update();
		void	Show();

	private:
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_HOMESECTIONNAME_H_
