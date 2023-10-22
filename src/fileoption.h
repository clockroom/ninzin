//
//	オプションファイル ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/06
//	Last  Edition 2001/09/21
//

#ifndef _FILEOPTION_H_
#define _FILEOPTION_H_

///////////////////////////////////////////////////////////
//	クラス宣言

class fileOption;

///////////////////////////////////////////////////////////
//	クラス

class fileOption
{
	public:
		fileOption();

		void	Clear();
		void	LoadOption();
		void	SaveOption();

		void	SetBGMOutput(bool);
		void	SetBGMVolume(int);
		void	SetSEVolume(int);
		void	SetTurnLR(bool);

		bool	GetDMInit();
		bool	GetBGMOutput();
		int		GetBGMVolume();
		int		GetSEVolume();
		bool	GetTurnLR();

	private:
		int		LoadINIInt(const char*,const char*,int);
		void	SaveINIInt(const char*,const char*,int);

	private:
		int		BGMVolume;
		int		SEVolume;
		bool	fDMInit;
		bool	fBGMOutput;
		bool	fTurnLR;
};

#endif	//	_FILEOPTION_H_
