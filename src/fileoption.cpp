//
//	オプションファイル ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/06
//	Last  Edition 2001/09/21
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "fileoption.h"

///////////////////////////////////////////////////////////
//	構築

fileOption::fileOption()
{
	Clear();
}

///////////////////////////////////////////////////////////
//	消去

void fileOption::Clear()
{
	BGMVolume=0;
	SEVolume=-10;
	fDMInit=true;
	fBGMOutput=false;
	fTurnLR=false;
}

///////////////////////////////////////////////////////////
//	読み込み

void fileOption::LoadOption()
{
	BGMVolume =LoadINIInt("option","bgmvolume",-10);
	SEVolume  =LoadINIInt("option","sevolume",-20);
	fDMInit	  =LoadINIInt("option","dminit",true)?true:false;
	fBGMOutput=LoadINIInt("option","bgmoutput",false)?true:false;
	fTurnLR   =LoadINIInt("option","mouse",false)?true:false;
}

int fileOption::LoadINIInt(const char *app,const char *key,int def)
{
	char	str[1024];

	GetFullPathFileName(str,"ninzin.ini");
	return GetPrivateProfileInt(app,key,def,str);
}

///////////////////////////////////////////////////////////
//	書き込み

void fileOption::SaveOption()
{
	SaveINIInt("option","bgmoutput",fBGMOutput);
	SaveINIInt("option","bgmvolume",BGMVolume);
	SaveINIInt("option","sevolume",SEVolume);
	SaveINIInt("option","mouse",fTurnLR);
}

void fileOption::SaveINIInt(const char *app,const char *key,int data)
{
	char	str[1024];
	char	buf[128];

	GetFullPathFileName(str,"ninzin.ini");
	sprintf(buf,"%d",data);
	WritePrivateProfileString(app,key,buf,str);
}

///////////////////////////////////////////////////////////
//	設定

void fileOption::SetBGMOutput(bool f)
{
	fBGMOutput=f;
}

void fileOption::SetBGMVolume(int vol)
{
	BGMVolume=vol;
}

void fileOption::SetSEVolume(int vol)
{
	SEVolume=vol;
}

void fileOption::SetTurnLR(bool f)
{
	fTurnLR=f;
}

///////////////////////////////////////////////////////////
//	取得

bool fileOption::GetDMInit()
{
	return fDMInit;
}

bool fileOption::GetBGMOutput()
{
	return fBGMOutput;
}

int fileOption::GetBGMVolume()
{
	return BGMVolume;
}

int fileOption::GetSEVolume()
{
	return SEVolume;
}

bool fileOption::GetTurnLR()
{
	return fTurnLR;
}
