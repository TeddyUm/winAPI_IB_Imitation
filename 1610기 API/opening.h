#pragma once
#include "gameNode.h"
#include "openingText.h"

class opening : public gameNode
{
private:
	openingText* _openingText;
	int _txtNum;
	image* _blank;

public:
	opening();
	~opening();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void SceneChange();
};

