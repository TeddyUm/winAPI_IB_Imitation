#pragma once
#include "Field.h"
#include "objectText.h"

class green3 : public Field
{
private:
	objectText* _objectText;
	image* _dialogueW;
	image* _antPicture;
	RECT _rcAntPicture;
	RECT _rcAntPictureB;
	bool _antPictureEvent;
	bool _endTalk;

public:
	green3();
	~green3();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};