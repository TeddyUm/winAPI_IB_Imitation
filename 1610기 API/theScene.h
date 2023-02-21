#pragma once

#include "gameNode.h"

class theScene : public gameNode
{
private:
	float _freq;

public:
	theScene();
	~theScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

