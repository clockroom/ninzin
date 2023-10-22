//
//	戻るボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/06
//

#ifndef _OPTRETURN_H_
#define _OPTRETURN_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class optReturn;

///////////////////////////////////////////////////////////
//	クラス

class optReturn
{
	public:
		void	CreateReturn();
		void	ReleaseReturn();

		void	SetPos(int,int);

		bool	IsButton(int,int);

		void	Show(int,int);

	private:
		int		PosX,PosY;
};

#endif	//	_OPTRETURN_H_
