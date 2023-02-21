#pragma once
#include "Field.h"
#include "objectText.h"

class museum1F_3 : public Field
{
private:
	image* _guest1;
	image* _guest2;
	image* _guest3;
	image* _guest4;
	image* _guest5;
	image* _dialogueW;

	RECT _rcGuest1;
	RECT _rcGuest2;
	RECT _rcGuest3;
	RECT _rcGuest4;
	RECT _rcGuest5;

	objectText* _objectText;
	int _frameXWindow;
	bool _endTalk;
	bool _guestEvent1;
	bool _guestEvent2;

public:
	museum1F_3();
	~museum1F_3();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};