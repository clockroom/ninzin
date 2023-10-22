//
//	プロテクトルーチン ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/14
//	Last  Edition 2001/09/14
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "common.h"
#include "workprotect.h"

///////////////////////////////////////////////////////////
//	構築

workProtect::workProtect()
{
}

///////////////////////////////////////////////////////////
//	プロテクト

bool workProtect::Protect()
{
	if(!_ProtectMap()) return false;

	return true;
}

///////////////////////////////////////////////////////////
//	マップ用プロテクト

bool workProtect::_ProtectMap()
{
	FILE	*fp;
	DWORD	dCode[128];
	DWORD	sum;
	BYTE	data;
	int		i,j;
	char	str[1024];
	char	buf[128];

	//	プロテクトコード読み込み
	GetFullPathFileName(str,"farm\\protect.bin");
	if((fp=fopen(str,"rb"))==NULL) return false;
	fread(dCode,sizeof(DWORD),128,fp);
	fclose(fp);

	//	プロテクト
	for(i=1,sum=0;i<=MAX_FARM;i++)
	{
		//	マップを開く
		sprintf(buf,"farm\\farm%02d.map",i);
		GetFullPathFileName(str,buf);
		if((fp=fopen(str,"rb"))==NULL) return false;

		//	チェックサム計算
		for(j=0;fread(&data,sizeof(BYTE),1,fp)==1;j++)
		{
			sum+=data*(j%256);
		}
		sum+=i;

		//	マップを閉じる
		fclose(fp);

		//	コード照合
		if(sum!=dCode[i]) return false;
	}

	return true;
}
