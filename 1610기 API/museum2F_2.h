#pragma once
#include "Field.h"
#include "objectText.h"

class museum2F_2 : public Field
{
public:
	museum2F_2();
	~museum2F_2();

	image* _guest1;
	image* _guest2;
	image* _guest3;
	image* _guest4;
	image* _guest5;
	image* _guest6;
	image* _guest7;
	image* _guest8;
	image* _dialogueW;

	RECT _rcGuest1;
	RECT _rcGuest2;
	RECT _rcGuest3;
	RECT _rcGuest4;
	RECT _rcGuest5;
	RECT _rcGuest6;
	RECT _rcGuest7;
	RECT _rcGuest8;
	RECT _rcPicture1;

	objectText* _objectText;
	bool _endTalk;
	bool _guestEvent1;
	bool _pictureEvent1;

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};