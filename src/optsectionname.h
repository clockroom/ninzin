//
//	セクション名クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/05
//

#ifndef _OPTSECTIONNAME_H_
#define _OPTSECTIONNAME_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class optSectionName;

///////////////////////////////////////////////////////////
//	クラス

class optSectionName
{
	public:
		void	CreateSectionName();
		void	ReleaseSectionName();

		void	SetPos(int,int);

		void	Show();

	private:
		int	PosX,PosY;
};

#endif	//	_OPTSECTIONNAME_H_
