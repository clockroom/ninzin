//
//	ＢＧＭ方式ボタンクラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/20
//	Last  Edition 2001/09/20
//

#ifndef _OPTBGMOUTPUT_H_
#define _OPTBGMOUTPUT_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	クラス宣言

class optBGMOutput;

///////////////////////////////////////////////////////////
//	クラス

class optBGMOutput
{
	public:
		void	CreateBGMOutput();
		void	ReleaseBGMOutput();

		void	SetPos(int,int);
		void	SetBGMOutput(bool);
		void	SetBGMOutput();

		bool	GetBGMOutput();
		bool	IsButton(int,int);

		void	Show(int,int);

	private:
		int		PosX,PosY;
		bool	fDirectMusic;
};

#endif	//	_OPTBGMOUTPUT_H_
