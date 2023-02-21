#pragma once
#include "gameNode.h"
#include "inventory.h"

enum fieldState
{
	ST_IDLE,
	ST_MENU,
	ST_STOP
};

class Field : public gameNode
{
protected:
	image* _back;
	image* _backPX;
	image* _backRC;
	image* _ibImg;
	image* _redRose1;
	image* _redRose2;
	image* _redRose3;
	image* _redRose4;
	image* _redRose5;

	inventory* _inven;

	fieldState _state;

	int _alpha;

	RECT _rc;
	int _x;
	int _y;

	int _count;
	int _frameX;
	int _frameY;

	bool _lStop;
	bool _rStop;
	bool _uStop;
	bool _dStop;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	virtual void Move();
	virtual void FrameCount();
	virtual void Menu();

	Field();
	~Field();
};

