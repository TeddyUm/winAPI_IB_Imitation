#pragma once
#include "Field.h"
#include "objectText.h"

enum REDDOLL_DIRECTION
{
	DOLL_UP,
	DOLL_DOWN,
	DOLL_RIGHT,
	DOLL_LEFT
};

class green2 : public Field
{
private:
	objectText* _objectText;
	REDDOLL_DIRECTION _dollDirection;
	image* _dialogueW;
	image* _redDoll;
	image* _blueRose;

	RECT _rcBlueRose;
	RECT _rcRedDoll;
	RECT _rcPicture1;
	RECT _rcPicture2;
	RECT _rcPicture3;
	RECT _rcPicture4;
	RECT _rcPicture5;
	RECT _rcPicture6;

	bool _endTalk;
	bool _blueRoseEvent;
	bool _dollMove;
	bool _pictureEvent1;
	bool _pictureEvent2;
	bool _pictureEvent3;
	bool _pictureEvent4;
	bool _pictureEvent5;
	bool _pictureEvent6;

	int _framecount;
	int _frameXDoll;
	int _frameYDoll;

public:
	green2();
	~green2();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void DollMove();
};