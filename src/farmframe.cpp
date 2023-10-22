//
//	�t���[���N���X by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/08/21
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "farmframe.h"

///////////////////////////////////////////////////////////
//	�t�@�C���ϐ�

static const int dMap[10][10]=
{
	4,4, 4, 4, 4, 4, 4, 4,4,4,
	4,0, 3, 3, 3, 3, 3, 3,6,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,1,-1,-1,-1,-1,-1,-1,7,4,
	4,2, 5, 5, 5, 5, 5, 5,8,4,
	4,4, 4, 4, 4, 4, 4, 4,4,4
};

///////////////////////////////////////////////////////////
//	�쐬

void farmFrame::CreateFrame()
{
	int	i;

	//	�p�^�[���쐬
	BmpMap.LoadBitmap("bitmap\\map02.bmp",true);
	for(i=0;i<FF_PAT_MAP;i++)
	{
		dPatMap[i].CreatePattern(&BmpMap,(i%3)*48,(i/3)*48,48,48);
	}

	//	���̑�������
	PosX=0;
	PosY=0;
}

void farmFrame::ReleaseFrame()
{
	BmpMap.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	�ݒ�

void farmFrame::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

///////////////////////////////////////////////////////////
//	�\��

void farmFrame::Show()
{
	int	i,j;
	int	n;

	for(i=0;i<10;i++)for(j=0;j<10;j++)
	{
		n=dMap[i][j];
		if(n<0) continue;
		dPatMap[n].Put(PosX+i*48,PosY+j*48);
	}
}
