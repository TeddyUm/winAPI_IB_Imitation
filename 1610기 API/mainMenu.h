#pragma once
#include "gameNode.h"

class mainMenu : public gameNode
{
private:
	image* _titleImg;
	image* _titleMenu;
	RECT _selectBox;

	HBRUSH newbrush, newbrush1, oldbrush, oldbrush1;

	int _select;
	int _count;
	int _y;

public:
	mainMenu();
	~mainMenu();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

