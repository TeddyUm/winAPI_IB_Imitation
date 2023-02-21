#pragma once
#include "Field.h"
#include "objectText.h"

class museumS : public Field
{
private:
	RECT _rcGuest;
	RECT _rcFather;
	RECT _rcMother;
	RECT _rcCounter;
	RECT _rcEnt;
	RECT _rcPamp;
	RECT _rcWindow;

	image* _guest;
	image* _counter;
	image* _father;
	image* _mother;
	image* _dialogue;
	image* _dialogueW;
	image* _motherP1;
	image* _fatherP1;
	image* _motherP2;
	image* _motherP3;

	ITEMIDX _itemIdx;

	objectText* _objectText;

	bool _endTalk;
	bool _startEvent;
	bool _guestEvent;
	bool _counterEvent;
	bool _entEvent;
	bool _pampEvent;
	bool _windowEvent;
	bool _motherEvent;
	bool _fatherEvent;
	bool _ibMoveE;
	bool _ibMoveC;
	bool _anotherCheck;
	bool _anotherText;

	int _countLight;

public:

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	museumS();
	~museumS();
};

