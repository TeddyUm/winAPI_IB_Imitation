#pragma once
#include "Field.h"
#include "objectText.h"

class green1 : public Field
{
private:
	objectText* _objectText;
	image* _dialogueW;
	image* _antPicture;
	image* _hand1;
	image* _hand2;

	RECT _rcAnt;
	RECT _rcAntPicture;
	RECT _rcBanner;
	RECT _rcHand1;
	RECT _rcHand2;
	RECT _rcPicture;

	int _currentFrame;
	int _countHand;
	int _sound;
	int _sound2;

	bool _antEvent;
	bool _antPictureEvent;
	bool _hand1Event;
	bool _hand2Event;
	bool _bannerEvent;
	bool _pictureEvent1;
	bool _endTalk;

public:

	green1();
	~green1();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};