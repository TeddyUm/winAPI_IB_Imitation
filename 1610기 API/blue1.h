#pragma once
#include "Field.h"
#include "objectText.h"

enum GARRY_DIRECTION
{
	GARRY_UP,
	GARRY_DOWN,
	GARRY_RIGHT,
	GARRY_LEFT,
	GARRY_SIT,
	GARRY_STAND
};

class blue1 : public Field
{
private:
	objectText* _objectText;
	GARRY_DIRECTION _garryDirection;
	image* _dialogueW;
	image* _back2;
	image* _garryImg;
	image* _dialogue;
	image* _garryP1;
	image* _garryP2;
	image* _garryP3;

	RECT _rcGarry;
	RECT _rcGarryB;

	bool _endTalk;
	bool _garryTalk;
	bool _endingEvent;
	bool _move;
	bool _GarryMove;

	int _framecount;
	int _frameXGarry;
	int _frameYGarry;

public:
	blue1();
	~blue1();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void GarryMove();
};

