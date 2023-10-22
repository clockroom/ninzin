//
//	�L�^�폜�{�^���N���X ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/05
//	Last  Edition 2001/09/06
//

///////////////////////////////////////////////////////////
//	�C���N���[�h

#include <afl.h>
#include "libfont.h"
#include "optdelrecord.h"

///////////////////////////////////////////////////////////
//	�쐬

void optDelRecord::CreateDelRecord()
{
	//	������
	DelCount=0;
	PosX=0;
	PosY=0;
}

void optDelRecord::ReleaseDelRecord()
{
}

///////////////////////////////////////////////////////////
//	�ݒ�

void optDelRecord::SetPos(int x,int y)
{
	PosX=x;
	PosY=y;
}

void optDelRecord::SetDelCount(int c)
{
	DelCount=c;
}

void optDelRecord::AddDelCount(int a)
{
	DelCount+=a;
	if(DelCount<0) DelCount=0;
}

///////////////////////////////////////////////////////////
//	�擾

int optDelRecord::GetDelCount()
{
	return DelCount;
}

bool optDelRecord::IsButton(int mx,int my)
{
	mx-=PosX;
	my-=PosY;

	if(DelCount<=0)		 return false;
	if(mx< 4 || 124<=mx) return false;
	if(my<22 ||  44<=my) return false;

	return true;
}

bool optDelRecord::IsDelete()
{
	if(DelCount==0) return true;
	return false;
}

///////////////////////////////////////////////////////////
//	�\��

void optDelRecord::Show(int mx,int my)
{
	libFont	lf;
	char	str[256];

	if(IsButton(mx,my)) lf.PutFont(PosX,PosY+18,"25�L�^���폜1");
	else				lf.PutFont(PosX,PosY+18,"25�L�^���폜0");

	if(DelCount>0)
	{
		sprintf(str,"16%d",DelCount);
		lf.PutFont(PosX+208,PosY+18,"23�폜�܂ł���");
		lf.PutFont(PosX+364,PosY,str);
	}
	else
	{
		lf.PutFont(PosX+208,PosY+18,"23�폜�����I�I");
	}
}
