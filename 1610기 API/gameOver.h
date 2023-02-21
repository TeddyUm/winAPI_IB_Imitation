#pragma once
#include "gameNode.h"

class gameOver : public gameNode
{
private:
	int _alpha;
	image* _blank;
	image* _ending;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	gameOver();
	~gameOver();
};