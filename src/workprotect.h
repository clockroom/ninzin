//
//	�v���e�N�g���[�`�� ClockRoom 2001
//	Program by Y.Kumagai ClockRoom 2001
//
//	First Edition 2001/09/14
//	Last  Edition 2001/09/14
//

#ifndef _WORKPROTECT_H_
#define _WORKPROTECT_H_

///////////////////////////////////////////////////////////
//	�N���X�錾

class workProtect;

///////////////////////////////////////////////////////////
//	�N���X

class workProtect
{
	public:
		workProtect();

		bool	Protect();

	private:
		bool	_ProtectMap();
};

#endif	//	_WORKPROTECT_H_
