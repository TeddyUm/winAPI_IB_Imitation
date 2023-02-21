#pragma once
#include "gameNode.h"

class inventory : public gameNode
{
private:
	stFlags _flags;
public:
	image* _menu;
	image* _menuIb;
	image* _itemHankie;
	image* _itemRedRose;
	image* _itemBlueKey;
	image* _itemAntPicture;
	image* _itemButterfly;

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	inventory();
	~inventory();
};

