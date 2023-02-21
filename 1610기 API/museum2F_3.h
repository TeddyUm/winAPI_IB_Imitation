#pragma once
#include "Field.h"
#include "objectText.h"

class museum2F_3 : public Field
{
private:
	image* _liquid;
	image* _liquidText;
	image* _dialogueW;
	image* _ibText;

	RECT _rcAnother;
	RECT _rcLiquid;
	objectText* _objectText;

	bool _endTalk;
	bool _anotherCheck;
	bool _anotherText;
	bool _liquidEvent;
	bool _liquidTextEvent;
	bool _textEvent;

	int _frameXText;
	int _count;
	int _countLight;

public:
	museum2F_3();
	~museum2F_3();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};