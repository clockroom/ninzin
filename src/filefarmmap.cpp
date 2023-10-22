//
//	�t�@�[���}�b�v�t�@�C�� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/07/22
//	Last  Edition 2001/09/15
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "common.h"
#include "filefarmmap.h"

///////////////////////////////////////////////////////////
//	�\�z

fileFarmMap::fileFarmMap()
{
	Clear();
}

///////////////////////////////////////////////////////////
//	����

void fileFarmMap::Clear()
{
	int	i,j;

	for(i=0;i<8;i++)for(j=0;j<8;j++)
	{
		dMap[i][j]=0x08;
	}
	for(i=0;i<36;i++) dRequest[i]=0x08;

	nMusic=0;
	cRequest=0;
}

///////////////////////////////////////////////////////////
//	�ǂݍ���

void fileFarmMap::LoadFarmMap(int no)
{
	afErrorBox	eb;
	FILE	*fp;
	char	str[1024];
	char	buf[256];
	int		cno;
	int		a,b,c,d;

	//	����
	Clear();

	//	�}�b�v�I�[�v��
	sprintf(buf,"farm\\farm%02d.map",no);
	GetFullPathFileName(str,buf);
	if((fp=fopen(str,"rt"))==NULL)
	{
		eb.SetTitle("�G���[ - �s�v�c�ȃj���W����");
		eb.SetMessage("�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B");
		eb.OpenBox();
		ExitProgram();
		return;
	}

	//	�}�b�v�ǂݍ���
	while(fscanf(fp,"%d %d,%d,%d,%d",&cno,&a,&b,&c,&d)!=EOF)
	{
		switch(cno)
		{
		case  1:_LoadMusic(a);		break;
		case 11:_LoadCarrot(a,b,c);	break;
		case 12:_LoadRequest(a,b);	break;
		}
	}

	//	�}�b�v�N���[�Y
	fclose(fp);
}

///////////////////////////////////////////////////////////
//	�e�ǂݍ���

void fileFarmMap::_LoadMusic(int n)
{
	nMusic=n;
}

void fileFarmMap::_LoadCarrot(int x,int y,int c)
{
	dMap[x][y]=c;
}

void fileFarmMap::_LoadRequest(int c,int r)
{
	int	i;

	for(i=0;i<r;i++) dRequest[cRequest++]=c;
}

///////////////////////////////////////////////////////////
//	�擾

int fileFarmMap::GetMusic()
{
	return nMusic;
}

BYTE (*fileFarmMap::GetMap())[8]
{
	return dMap;
}

BYTE *fileFarmMap::GetRequest()
{
	return dRequest;
}
