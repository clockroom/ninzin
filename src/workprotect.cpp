//
//	�v���e�N�g���[�`�� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/14
//	Last  Edition 2001/09/14
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "common.h"
#include "workprotect.h"

///////////////////////////////////////////////////////////
//	�\�z

workProtect::workProtect()
{
}

///////////////////////////////////////////////////////////
//	�v���e�N�g

bool workProtect::Protect()
{
	if(!_ProtectMap()) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	�}�b�v�p�v���e�N�g

bool workProtect::_ProtectMap()
{
	FILE	*fp;
	DWORD	dCode[128];
	DWORD	sum;
	BYTE	data;
	int		i,j;
	char	str[1024];
	char	buf[128];

	//	�v���e�N�g�R�[�h�ǂݍ���
	GetFullPathFileName(str,"farm\\protect.bin");
	if((fp=fopen(str,"rb"))==NULL) return false;
	fread(dCode,sizeof(DWORD),128,fp);
	fclose(fp);

	//	�v���e�N�g
	for(i=1,sum=0;i<=MAX_FARM;i++)
	{
		//	�}�b�v���J��
		sprintf(buf,"farm\\farm%02d.map",i);
		GetFullPathFileName(str,buf);
		if((fp=fopen(str,"rb"))==NULL) return false;

		//	�`�F�b�N�T���v�Z
		for(j=0;fread(&data,sizeof(BYTE),1,fp)==1;j++)
		{
			sum+=data*(j%256);
		}
		sum+=i;

		//	�}�b�v�����
		fclose(fp);

		//	�R�[�h�ƍ�
		if(sum!=dCode[i]) return false;
	}

	return true;
}
