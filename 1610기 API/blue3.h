#pragma once
#include "Field.h"
#include "objectText.h"

class blue3 : public Field
{
private:
	objectText* _objectText;
	image* _dialogueW;
	image* _blueKey;
	image* _smileFace;

	RECT _rcKey;
	RECT _rcPicture;

	int _countFace;
	int _currentFrame;
	bool _endTalk;
	bool _faceEvent;
	bool _blueKeyEvent;
	bool _pictureEvent1;

public:
	blue3();
	~blue3();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};