#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::Init()
{
	_menu = IMAGEMANAGER->AddImage("menu", "image/menu.bmp", 0, 0, 640, 480, false, false);
	_menuIb = IMAGEMANAGER->AddImage("menuIb", "image/menu_ib.bmp", 10, 50, 250, 380, true, RGB(0, 0, 0));

	return S_OK;
}
void inventory::Release()
{
}
void inventory::Update()
{
}
void inventory::Render()
{
	_menu->Render(GetMemDC());
	_menuIb->Render(GetMemDC());
	IB->Inventory(GetMemDC());
}
