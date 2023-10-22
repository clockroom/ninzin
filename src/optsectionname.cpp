//
//	セクション名クラス ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/05
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"
#include "optsectionname.h"

///////////////////////////////////////////////////////////
//	作成

void optSectionName::CreateSectionName()
{
	//	初期化
	PosX=0;
	PosY=0;
}

void optSectionName::ReleaseSectionName()
{
}

///////////////////////////////////////////////////////////
//	設定

void optSectionName::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	表示

void optSectionName::Show()
{
	libFont	lf;

	lf.PutFont(PosX,PosY,"24option");
}
