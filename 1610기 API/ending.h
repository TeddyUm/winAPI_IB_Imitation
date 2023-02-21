#pragma once
#include "gameNode.h"
#include "openingText.h"

class ending : public gameNode
{
private:
	openingText* _openingText;
	int _txtNum;
	int _alpha;
	image* _blank;
	image* _ending;


public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void SceneChange();

	ending();
	~ending();
};