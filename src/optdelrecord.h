//
//	記録削除ボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/05
//

#ifndef _OPTDELRECORD_H_
#define _OPTDELRECORD_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class optDelRecord;

///////////////////////////////////////////////////////////
//	クラス

class optDelRecord
{
	public:
		void	CreateDelRecord();
		void	ReleaseDelRecord();

		void	SetPos(int,int);
		void	SetDelCount(int);
		void	AddDelCount(int);

		int		GetDelCount();
		bool	IsButton(int,int);
		bool	IsDelete();

		void	Show(int,int);

	private:
		int		DelCount;
		int		PosX,PosY;
};

#endif	//	_OPTDELRECORD_H_
