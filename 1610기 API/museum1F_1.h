#pragma once
#include "Field.h"
#include "objectText.h"

class museum1F_1 : public Field
{
private:
	image* _wall;

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
	RECT _rcPicture2;
	RECT _rcPicture3;

	objectText* _objectText;

	bool _picture1Event;
	bool _picture2Event;
	bool _picture3Event;
	bool _guest1Event;
	bool _guest2Event;
	bool _guest3Event;
	bool _endTalk;

public:
	museum1F_1();
	~museum1F_1();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

