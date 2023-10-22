//
//	�t�@�[���}�b�v�t�@�C�� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/09/15
//

#ifndef _FILEFARMMAP_H_
#define _FILEFARMMAP_H_

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <windows.h>

///////////////////////////////////////////////////////////
//	�N���X�錾

class fileFarmMap;

///////////////////////////////////////////////////////////
//	�N���X

class fileFarmMap
{
	public:
		fileFarmMap();

		void	Clear();
		void	LoadFarmMap(int);

		int		GetMusic();
		BYTE	(*GetMap())[8];
		BYTE	*GetRequest();

	private:
		void	_LoadMusic(int);
		void	_LoadCarrot(int,int,int);
		void	_LoadRequest(int,int);

	private:
		BYTE	dMap[8][8];
		BYTE	dRequest[36];
		int		nMusic;
		int		cRequest;
};

#endif	//	_FILEFARMMAP_H_
