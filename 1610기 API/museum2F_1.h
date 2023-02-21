#pragma once
#include "Field.h"
#include "objectText.h"

class museum2F_1 : public Field
{
private:
	image* _guest1;
	image* _guest2;
	image* _guest3;
	image* _guest4;
	image* _dialogueW;
	image* _window;

	RECT _rcGuest1;
	RECT _rcGuest2;
	RECT _rcGuest3;
	RECT _rcGuest4;
	RECT _rcPicture1;
	RECT _rcWindow;
	RECT _rcWindowD;

	objectText* _objectText;
	int _frameXWindow;
	int _count;
	bool _endTalk;
	bool _guestEvent1;
	bool _guestEvent2;
	bool _pictureEvent1;
	bool _windowEvent;

public:
	museum2F_1();
	~museum2F_1();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

