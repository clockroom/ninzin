//
//	�v���C�f�[�^�t�@�C�� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/15
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "common.h"
#include "fileplaydata.h"

///////////////////////////////////////////////////////////
//	�\�z

filePlayData::filePlayData()
{
	Clear();
}

///////////////////////////////////////////////////////////
//	����

void filePlayData::Clear()
{
	int	i;

	ClearCount=0;

	for(i=0;i<128;i++)
	{
		dFarmData[i].GoodWater=0;
		dFarmData[i].BestWater=FP_FIRSTLOAD;
		dFarmData[i].BestTime =FP_FIRSTLOAD;
	}
}

///////////////////////////////////////////////////////////
//	�ǂݍ���

void filePlayData::LoadPlayData()
{
	//	����
	Clear();

	//	�ǂݍ���
	_LoadRecord();
	_LoadFarm();
}

void filePlayData::_LoadRecord()
{
	FILE	*fp;
	DWORD	sum1,sum2;
	WORD	data[32];
	char	str[1024];
	int		i;

	//	�I�[�v��
	GetFullPathFileName(str,"record.bin");
	if((fp=fopen(str,"rb"))==NULL) return;

	//	�w�b�_�ǂݍ���
	fread(data,sizeof(WORD),32,fp);
	sum1=*((DWORD*)&data[24]);

	//	���R�[�h�ǂݍ���
	for(i=0,sum2=0;i<128;i++)
	{
		fread(data,sizeof(WORD),8,fp);
		if(_Decode(data[0])!=FP_NOCLEAR &&
		   _Decode(data[0])!=FP_FIRSTLOAD)
		{
			ClearCount++;
		}
		dFarmData[i].BestWater=_Decode(data[0]);
		dFarmData[i].BestTime =_Decode(data[1]);

		//	�`�F�b�N�T��
		sum2+=_CalculateSum(data,8);
	}
	if(MODE_EDIT) ClearCount=MAX_FARM;

	//	�N���[�Y
	fclose(fp);

	//	�`�F�b�N�T���m�F
	if(sum1!=sum2) Clear();
}

void filePlayData::_LoadFarm()
{
	afErrorBox	eb;
	FILE	*fp;
	char	buf[256];
	char	str[1024];
	int		cno,gw;
	int		i;

	for(i=1;i<=MAX_FARM;i++)
	{
		//	�I�[�v��
		sprintf(buf,"farm\\farm%02d.map",i);
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
		while(fscanf(fp,"%d %d,%*d,%*d,%*d",&cno,&gw)!=EOF)
		{
			if(cno!=13) continue;

			dFarmData[i].GoodWater=gw;
			break;
		}

		//	�N���[�Y
		fclose(fp);
	}
}

///////////////////////////////////////////////////////////
//	��������

void filePlayData::SavePlayData()
{
	afErrorBox	eb;
	FILE	*fp;
	DWORD	sum;
	WORD	data[32];
	char	str[1024];
	int		i;

	//	�I�[�v��
	GetFullPathFileName(str,"record.bin");
	if((fp=fopen(str,"wb"))==NULL)
	{
		eb.SetTitle("�G���[ - �s�v�c�ȃj���W����");
		eb.SetMessage("���R�[�h�f�[�^�̏������݂Ɏ��s���܂����B");
		eb.OpenBox();
		ExitProgram();
		return;
	}

	//	�w�b�_��������
	ZeroMemory(data,sizeof(WORD)*32);
	fwrite(data,sizeof(WORD),32,fp);

	//	���R�[�h��������
	for(i=0,sum=0;i<128;i++)
	{
		ZeroMemory(data,sizeof(WORD)*32);
		data[0]=_Encode(dFarmData[i].BestWater);
		data[1]=_Encode(dFarmData[i].BestTime);
		fwrite(data,sizeof(WORD),8,fp);

		//	�`�F�b�N�T��
		sum+=_CalculateSum(data,8);
	}

	//	�`�F�b�N�T���L�^
	fseek(fp,sizeof(WORD)*24,SEEK_SET);
	fwrite(&sum,sizeof(DWORD),1,fp);

	//	�N���[�Y
	fclose(fp);
}

///////////////////////////////////////////////////////////
//	�G���R�[�h

WORD filePlayData::_Encode(WORD val)
{
	WORD	bin;
	WORD	a,b;

	a=(val<< 3)&0xfff8;
	b=(val>>13)&0x0007;
	bin=~(a|b);

	return bin;
}

///////////////////////////////////////////////////////////
//	�f�R�[�h

WORD filePlayData::_Decode(WORD bin)
{
	WORD	val;
	WORD	a,b;

	a=(bin>> 3)&0x1fff;
	b=(bin<<13)&0xe000;
	val=~(a|b);

	return val;
}

///////////////////////////////////////////////////////////
//	�`�F�b�N�T���v�Z

DWORD filePlayData::_CalculateSum(WORD *pd,int n)
{
	int	i;
	int	sum;

	for(i=0,sum=0;i<n;i++) sum+=pd[i];

	return sum;
}

///////////////////////////////////////////////////////////
//	�擾

int filePlayData::GetClearCount()
{
	return ClearCount;
}

void filePlayData::GetFarmRecord(int *pgw,int *pbw,int *pbt,int no)
{
	if(pgw!=NULL) *pgw=dFarmData[no].GoodWater;
	if(pbw!=NULL) *pbw=dFarmData[no].BestWater;
	if(pbt!=NULL) *pbt=dFarmData[no].BestTime;
}

void filePlayData::GetTotalRecord(int *pgw,int *pbw,int *pbt)
{
	int	i;
	int	sg,sw,st;

	for(i=1,sg=0,sw=0,st=0;i<=ClearCount;i++)
	{
		sg+=dFarmData[i].GoodWater;
		sw+=dFarmData[i].BestWater;
		st+=dFarmData[i].BestTime;
	}

	if(pgw!=NULL) *pgw=sg;
	if(pbw!=NULL) *pbw=sw;
	if(pbt!=NULL) *pbt=st;
}

///////////////////////////////////////////////////////////
//	�ݒ�

void filePlayData::SetFarmRecord(int no,int w,int t)
{
	dFarmData[no].BestWater=w;
	dFarmData[no].BestTime =t;
}
