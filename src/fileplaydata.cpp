//
//	プレイデータファイル ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/08/29
//	Last  Edition 2001/09/15
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "common.h"
#include "fileplaydata.h"

///////////////////////////////////////////////////////////
//	構築

filePlayData::filePlayData()
{
	Clear();
}

///////////////////////////////////////////////////////////
//	消去

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
//	読み込み

void filePlayData::LoadPlayData()
{
	//	消去
	Clear();

	//	読み込み
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

	//	オープン
	GetFullPathFileName(str,"record.bin");
	if((fp=fopen(str,"rb"))==NULL) return;

	//	ヘッダ読み込み
	fread(data,sizeof(WORD),32,fp);
	sum1=*((DWORD*)&data[24]);

	//	レコード読み込み
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

		//	チェックサム
		sum2+=_CalculateSum(data,8);
	}
	if(MODE_EDIT) ClearCount=MAX_FARM;

	//	クローズ
	fclose(fp);

	//	チェックサム確認
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
		//	オープン
		sprintf(buf,"farm\\farm%02d.map",i);
		GetFullPathFileName(str,buf);
		if((fp=fopen(str,"rt"))==NULL)
		{
			eb.SetTitle("エラー - 不思議なニンジン畑");
			eb.SetMessage("マップデータの読み込みに失敗しました。");
			eb.OpenBox();
			ExitProgram();
			return;
		}

		//	マップ読み込み
		while(fscanf(fp,"%d %d,%*d,%*d,%*d",&cno,&gw)!=EOF)
		{
			if(cno!=13) continue;

			dFarmData[i].GoodWater=gw;
			break;
		}

		//	クローズ
		fclose(fp);
	}
}

///////////////////////////////////////////////////////////
//	書き込み

void filePlayData::SavePlayData()
{
	afErrorBox	eb;
	FILE	*fp;
	DWORD	sum;
	WORD	data[32];
	char	str[1024];
	int		i;

	//	オープン
	GetFullPathFileName(str,"record.bin");
	if((fp=fopen(str,"wb"))==NULL)
	{
		eb.SetTitle("エラー - 不思議なニンジン畑");
		eb.SetMessage("レコードデータの書き込みに失敗しました。");
		eb.OpenBox();
		ExitProgram();
		return;
	}

	//	ヘッダ書き込み
	ZeroMemory(data,sizeof(WORD)*32);
	fwrite(data,sizeof(WORD),32,fp);

	//	レコード書き込み
	for(i=0,sum=0;i<128;i++)
	{
		ZeroMemory(data,sizeof(WORD)*32);
		data[0]=_Encode(dFarmData[i].BestWater);
		data[1]=_Encode(dFarmData[i].BestTime);
		fwrite(data,sizeof(WORD),8,fp);

		//	チェックサム
		sum+=_CalculateSum(data,8);
	}

	//	チェックサム記録
	fseek(fp,sizeof(WORD)*24,SEEK_SET);
	fwrite(&sum,sizeof(DWORD),1,fp);

	//	クローズ
	fclose(fp);
}

///////////////////////////////////////////////////////////
//	エンコード

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
//	デコード

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
//	チェックサム計算

DWORD filePlayData::_CalculateSum(WORD *pd,int n)
{
	int	i;
	int	sum;

	for(i=0,sum=0;i<n;i++) sum+=pd[i];

	return sum;
}

///////////////////////////////////////////////////////////
//	取得

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
//	設定

void filePlayData::SetFarmRecord(int no,int w,int t)
{
	dFarmData[no].BestWater=w;
	dFarmData[no].BestTime =t;
}
