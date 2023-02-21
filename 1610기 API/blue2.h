#pragma once
#include "Field.h"
#include "objectText.h"

class blue2 : public Field
{
private:
	objectText* _objectText;
	image* _back2;
	image* _bottle;
	image* _dialogueW;
	image* _ibText;

	RECT _rcBottle;
	RECT _rcBottleB;
	RECT _rcText;
	bool _endTalk;
	bool _move;
	bool _bottleMove;
	bool _redRoseEvent;
	bool _textEvent;
	int _frameXText;
	int _count;

public:
	blue2();
	~blue2();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};