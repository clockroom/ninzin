//
//	プレイデータファイル ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/14
//

#ifndef _FILEPLAYDATA_H_
#define _FILEPLAYDATA_H_

///////////////////////////////////////////////////////////
//	定数宣言

#define FP_FIRSTLOAD	65000
#define FP_NOCLEAR		60000

///////////////////////////////////////////////////////////
//	クラス宣言

class filePlayData;

///////////////////////////////////////////////////////////
//	クラス

class filePlayData
{
	private:
		struct dataFarmData
		{
			int	GoodWater;
			int	BestWater;
			int	BestTime;
		};

	public:
		filePlayData();

		void	Clear();
		void	LoadPlayData();
		void	SavePlayData();

		int		GetClearCount();
		void	GetFarmRecord(int*,int*,int*,int);
		void	GetTotalRecord(int*,int*,int*);

		void	SetFarmRecord(int,int,int);

	private:
		void	_LoadFarm();
		void	_LoadRecord();
		WORD	_Encode(WORD);
		WORD	_Decode(WORD);
		DWORD	_CalculateSum(WORD*,int);

	private:
		dataFarmData	dFarmData[128];
		int	ClearCount;
};

#endif	//	_FILEPLAYDATA_H_
