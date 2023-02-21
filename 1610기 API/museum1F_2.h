#pragma once
#include "Field.h"
#include "objectText.h"

class museum1F_2 : public Field
{
private:
	image* _guest1;
	image* _dialogueW;
	image* _picture;

	RECT _rcGuest1;
	RECT _rcPicture;
	RECT _rcPictureH;
	objectText* _objectText;
	bool _endTalk;
	bool _guestEvent1;
	bool _pictureEvent1;
	int _frameXpicture;
	int _count;

public:
	museum1F_2();
	~museum1F_2();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};