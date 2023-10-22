//
//	レコードクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/06
//

#ifndef _HOMERECORD_H_
#define _HOMERECORD_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class filePlayData;
class homeRecord;

///////////////////////////////////////////////////////////
//	クラス

class homeRecord
{
	public:
		void	CreateRecord(filePlayData*);
		void	ReleaseRecord();
		void	ResetRecord();

		void	SetPos(int,int);

		bool	IsEndEntrance();

		void	Update();
		void	Show();

	private:
		void	_CreateRecordBitmap();

	private:
		filePlayData	*pPlayData;
		afBitmap	BmpRecord;
		int	PosX,PosY;
		int	cProg;
};

#endif	//	_HOMERECORD_H_
