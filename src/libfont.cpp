//
//	フォントライブラリ by ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/06/24
//	Last  Edition 2001/09/20
//

///////////////////////////////////////////////////////////
//	インクルード

#include <afl.h>
#include "libfont.h"

///////////////////////////////////////////////////////////
//	定数定義

#define PAT_FONT11	14
#define PAT_FONT16	10
#define PAT_FONT17	 6
#define PAT_FONT21	 4
#define PAT_FONT22	 7
#define PAT_FONT23	 8
#define PAT_FONT24	 1
#define PAT_FONT25	 8
#define PAT_FONT26	 6
#define PAT_FONT27	 2
#define PAT_FONT28	 6

///////////////////////////////////////////////////////////
//	クラス変数

afBitmap  libFont::BmpFont11;
afBitmap  libFont::BmpFont16;
afBitmap  libFont::BmpFont17;
afBitmap  libFont::BmpFont21;
afBitmap  libFont::BmpFont22;
afBitmap  libFont::BmpFont23;
afBitmap  libFont::BmpFont24;
afBitmap  libFont::BmpFont25;
afBitmap  libFont::BmpFont26;
afBitmap  libFont::BmpFont27;
afBitmap  libFont::BmpFont28;

afPattern libFont::dPatFont11[PAT_FONT11];
afPattern libFont::dPatFont12[PAT_FONT11];
afPattern libFont::dPatFont13[PAT_FONT11];
afPattern libFont::dPatFont16[PAT_FONT16];
afPattern libFont::dPatFont17[PAT_FONT17];
afPattern libFont::dPatFont21[PAT_FONT21];
afPattern libFont::dPatFont22[PAT_FONT22];
afPattern libFont::dPatFont23[PAT_FONT23];
afPattern libFont::dPatFont24[PAT_FONT24];
afPattern libFont::dPatFont25[PAT_FONT25];
afPattern libFont::dPatFont26[PAT_FONT26];
afPattern libFont::dPatFont27[PAT_FONT27];
afPattern libFont::dPatFont28[PAT_FONT28];

///////////////////////////////////////////////////////////
//	初期化

void libFont::InitLibrary()
{
	InitLibrary(11);
	InitLibrary(21);
	InitLibrary(22);
}

void libFont::InitLibrary(int no)
{
	int	i;

	switch(no)
	{
	case 11:
		BmpFont11.LoadBitmap("bitmap\\font11.bmp");
		for(i=0;i<PAT_FONT11;i++)
		{
			dPatFont11[i].CreatePattern(&BmpFont11,i*16, 0,16,16);
			dPatFont12[i].CreatePattern(&BmpFont11,i*16,16,16,16);
			dPatFont13[i].CreatePattern(&BmpFont11,i*16,32,16,16);
		}
		break;

	case 16:
		BmpFont16.LoadBitmap("bitmap\\font16.bmp");
		for(i=0;i<PAT_FONT16;i++)
		{
			dPatFont16[i].CreatePattern(&BmpFont16,i*40,0,40,48);
		}
		break;

	case 17:
		BmpFont17.LoadBitmap("bitmap\\font17.bmp");
		for(i=0;i<PAT_FONT17;i++)
		{
			dPatFont17[i].CreatePattern(&BmpFont17,i*20,0,20,18);
		}
		break;

	case 21:
		BmpFont21.LoadBitmap("bitmap\\font21.bmp");
		for(i=0;i<PAT_FONT21;i++)
		{
			dPatFont21[i].CreatePattern(&BmpFont21,0,i*52,208,52);
		}
		break;

	case 22:
		BmpFont22.LoadBitmap("bitmap\\font22.bmp");
		for(i=0;i<PAT_FONT22;i++)
		{
			dPatFont22[i].CreatePattern(&BmpFont22,0,i*24,96,24);
		}
		break;

	case 23:
		BmpFont23.LoadBitmap("bitmap\\font23.bmp");
		for(i=0;i<PAT_FONT23;i++)
		{
			dPatFont23[i].CreatePattern(&BmpFont23,0,i*30,154,30);
		}
		break;

	case 24:
		BmpFont24.LoadBitmap("bitmap\\font24.bmp");
		for(i=0;i<PAT_FONT24;i++)
		{
			dPatFont24[i].CreatePattern(&BmpFont24,0,i*54,152,54);
		}
		break;

	case 25:
		BmpFont25.LoadBitmap("bitmap\\font25.bmp");
		for(i=0;i<PAT_FONT25;i++)
		{
			dPatFont25[i].CreatePattern(&BmpFont25,0,i*30,176,30);
		}
		break;

	case 26:
		BmpFont26.LoadBitmap("bitmap\\font26.bmp");
		for(i=0;i<PAT_FONT26;i++)
		{
			dPatFont26[i].CreatePattern(&BmpFont26,0,i*32,192,32);
		}
		break;

	case 27:
		BmpFont27.LoadBitmap("bitmap\\font27.bmp");
		for(i=0;i<PAT_FONT27;i++)
		{
			dPatFont27[i].CreatePattern(&BmpFont27,0,i*26,176,26);
		}
		break;

	case 28:
		BmpFont28.LoadBitmap("bitmap\\font28.bmp");
		for(i=0;i<PAT_FONT28;i++)
		{
			dPatFont28[i].CreatePattern(&BmpFont28,0,i*16,160,16);
		}
		break;
	}
}

void libFont::FinalLiblary()
{
	BmpFont11.ReleaseBitmap();
	BmpFont16.ReleaseBitmap();
	BmpFont21.ReleaseBitmap();
	BmpFont22.ReleaseBitmap();
	BmpFont23.ReleaseBitmap();
	BmpFont24.ReleaseBitmap();
	BmpFont25.ReleaseBitmap();
	BmpFont26.ReleaseBitmap();
	BmpFont27.ReleaseBitmap();
}

///////////////////////////////////////////////////////////
//	通常描画

void libFont::PutFont(int x,int y,const char *str)
{
	BlendFont(x,y,64,str);
}

///////////////////////////////////////////////////////////
//	調光描画

void libFont::BrightFont(int x,int y,int b,const char *str)
{
	BlendFont(x,y,b,str);
}

///////////////////////////////////////////////////////////
//	半透明描画

void libFont::BlendFont(int x,int y,int b,const char *str)
{
	int	code=(str[0]-'0')*10+(str[1]-'0');

	switch(code)
	{
	case 11:_PutFont11(dPatFont11,x,y,b,&str[2]);break;
	case 12:_PutFont11(dPatFont12,x,y,b,&str[2]);break;
	case 13:_PutFont11(dPatFont13,x,y,b,&str[2]);break;
	case 16:_PutFont16(x,y,b,&str[2]);break;
	case 17:_PutFont17(x,y,b,&str[2]);break;
	case 21:_PutFont21(x,y,b,&str[2]);break;
	case 22:_PutFont22(x,y,b,&str[2]);break;
	case 23:_PutFont23(x,y,b,&str[2]);break;
	case 24:_PutFont24(x,y,b,&str[2]);break;
	case 25:_PutFont25(x,y,b,&str[2]);break;
	case 26:_PutFont26(x,y,b,&str[2]);break;
	case 27:_PutFont27(x,y,b,&str[2]);break;
	case 28:_PutFont28(x,y,b,&str[2]);break;
	}
}

///////////////////////////////////////////////////////////
//	描画11

void libFont::_PutFont11(afPattern *dpat,int x,int y,int b,const char *str)
{
	int		i,n;
	int		p,s;
	char	c;

	for(i=0,p=0;i<(int)strlen(str);i++)
	{
		c=str[i];
		n=-1;
		s=16;

		if('0'<=c && c<='9') n=c-'0';
		if(c=='/') n=10;
		if(c=='-') n=11;
		if(c=='t') n=12;
		if(c=='.') {n=13;s=8;}
		if(c=='#') s=4;

		if(n!=-1) dpat[n].Blend(x+p,y,b);
		p+=s;
	}
}

///////////////////////////////////////////////////////////
//	描画16

void libFont::_PutFont16(int x,int y,int b,const char *str)
{
	int		i,n;
	char	c;

	for(i=0;i<(int)strlen(str);i++)
	{
		c=str[i];
		n=-1;
		if('0'<=c && c<='9') n=c-'0';
		if(n==-1) continue;

		dPatFont16[n].Blend(x+i*40,y,b);
	}
}

///////////////////////////////////////////////////////////
//	描画17

void libFont::_PutFont17(int x,int y,int b,const char *str)
{
	int		i,n;
	char	c;

	for(i=0;i<(int)strlen(str);i++)
	{
		c=str[i];
		n=-1;
		if('A'<=c && c<='F') n=c-'A';
		if(n==-1) continue;

		dPatFont17[n].Blend(x+i*40,y,b);
	}
}

///////////////////////////////////////////////////////////
//	描画21

void libFont::_PutFont21(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"farm")   ==0) n=0;
	if(strcmp(str,"clear")  ==0) n=1;
	if(strcmp(str,"failure")==0) n=2;
	if(strcmp(str,"select") ==0) n=3;
	if(n==-1) return;

	dPatFont21[n].Blend(x,y,b);
}

///////////////////////////////////////////////////////////
//	描画22

void libFont::_PutFont22(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"request")==0) n=0;
	if(strcmp(str,"farm")   ==0) n=1;
	if(strcmp(str,"carrot") ==0) n=2;
	if(strcmp(str,"water")  ==0) n=3;
	if(strcmp(str,"help")   ==0) n=4;
	if(strcmp(str,"record") ==0) n=5;
	if(strcmp(str,"rank")   ==0) n=6;
	if(n==-1) return;

	dPatFont22[n].Blend(x,y,b);
}

///////////////////////////////////////////////////////////
//	描画23

void libFont::_PutFont23(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"効果音の音量")==0) n=0;
	if(strcmp(str,"削除まであと")==0) n=1;
	if(strcmp(str,"削除完了！！")==0) n=2;
	if(strcmp(str,"水やり")		 ==0) n=3;
	if(strcmp(str,"収穫")		 ==0) n=4;
	if(strcmp(str,"MCI")		 ==0) n=5;
	if(strcmp(str,"DirectMusic") ==0) n=6;
	if(strcmp(str,"ＢＧＭの音量")==0) n=7;
	if(n==-1) return;

	if(b==64) dPatFont23[n].Opaque(x,y);
	else	  dPatFont23[n].BrightOpaque(x,y,b);
}

///////////////////////////////////////////////////////////
//	描画24

void libFont::_PutFont24(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"option")==0) n=0;
	if(n==-1) return;

	dPatFont24[n].Opaque(x,y);
}

///////////////////////////////////////////////////////////
//	描画25

void libFont::_PutFont25(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"タイトルに戻る0")==0) n=0;
	if(strcmp(str,"タイトルに戻る1")==0) n=1;
	if(strcmp(str,"記録を削除0")	==0) n=2;
	if(strcmp(str,"記録を削除1")	==0) n=3;
	if(strcmp(str,"操作ボタン0")	==0) n=4;
	if(strcmp(str,"操作ボタン1")	==0) n=5;
	if(strcmp(str,"ＢＧＭ方式0")	==0) n=6;
	if(strcmp(str,"ＢＧＭ方式1")	==0) n=7;
	if(n==-1) return;

	dPatFont25[n].Opaque(x,y);
}

///////////////////////////////////////////////////////////
//	描画26

void libFont::_PutFont26(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"ゲームスタート0")==0) n=0;
	if(strcmp(str,"ゲームスタート1")==0) n=1;
	if(strcmp(str,"オプション0")	==0) n=2;
	if(strcmp(str,"オプション1")	==0) n=3;
	if(strcmp(str,"ゲームをやめる0")==0) n=4;
	if(strcmp(str,"ゲームをやめる1")==0) n=5;
	if(n==-1) return;

	dPatFont26[n].Opaque(x,y);
}

///////////////////////////////////////////////////////////
//	描画27

void libFont::_PutFont27(int x,int y,int b,const char *str)
{
	int	n;

	n=-1;
	if(strcmp(str,"タイトルに戻る0")==0) n=0;
	if(strcmp(str,"タイトルに戻る1")==0) n=1;
	if(n==-1) return;

	dPatFont27[n].Blend(x,y,b);
}

///////////////////////////////////////////////////////////
//	描画28

void libFont::_PutFont28(int x,int y,int b,const char *str)
{
	int		n;
	char	c;

	n=-1;
	c=str[0];
	if('A'<=c && c<='F') n=c-'A';
	if(n==-1) return;

	dPatFont28[n].Blend(x,y,b);
}
