//
//	マップクラス by ClocoRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/23
//	Last  Edition 2001/09/13
//

#ifndef _FARMMAP_H_
#define _FARMMAP_H_

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>

///////////////////////////////////////////////////////////
//	定数定義

#define FM_PAT_MAP	12
#define FM_SC_NONE	0
#define FM_SC_WATER	1
#define FM_SC_PULL	2

///////////////////////////////////////////////////////////
//	クラス宣言

class farmMap;

///////////////////////////////////////////////////////////
//	クラス

class farmMap
{
	public:
		void	CreateMap();
		void	ReleaseMap();
		void	ClearMap();
		void	ResetMap();

		void	SetMap(BYTE(*)[8]);
		void	SetPos(int,int);

		void	GetPos(int*,int*);
		void	GetFarmPos(int*,int*,int,int);
		bool	IsFarm(int,int);
		bool	IsEndPlant();

		bool	WaterCarrot(int,int);
		BYTE	PullCarrot(int,int);

		void	Update();
		void	Show(int,int,int);

	private:
		void	_ShowCursor(int,int,int);

	private:
		afBitmap	BmpMap;
		afBitmap	BmpColor;
		afPattern	dPatMap[FM_PAT_MAP];
		afPattern	dPatColor[4];
		afPattern	*pdPatCarrot;
		afPattern	*pPatFarm;
		BYTE	dMap[8][8];
		BYTE	*dpMap[37];
		int		PosX,PosY;
		int		cProg;
};

#endif	//	_FARMMAP_H_
