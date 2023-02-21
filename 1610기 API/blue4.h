#pragma once
#include "Field.h"
#include "objectText.h"

class blue4 : public Field
{
private:
	objectText* _objectText;
	image* _dialogueW;
	RECT _rcSave;
	RECT _rcDoor;
	RECT _rcDoorB;
	RECT _rcPicture;

	bool _saveEvent;
	bool _doorLockEvent;
	bool _doorLockText;
	bool _doorOpenEvent;
	bool _doorOpenText;
	bool _pictureEvent1;
	bool _endTalk;

public:
	blue4();
	~blue4();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};