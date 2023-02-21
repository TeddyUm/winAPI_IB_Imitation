#include "stdafx.h"
#include "mainMenu.h"


mainMenu::mainMenu()
{
}


mainMenu::~mainMenu()
{
}


HRESULT mainMenu::Init()
{
	//SOUNDMANAGER->AddSound("title", "sound/title.mp3", true, true);
	//SOUNDMANAGER->AddSound("titleknock", "sound/title_knock.wav", false, false);
	//SOUNDMANAGER->AddSound("select", "sound/select.wav", false, false);
	//SOUNDMANAGER->Play("title", 1.0f);
	_titleImg = IMAGEMANAGER->AddImage("titleimage", "image/title.bmp", 640, 480, false, false);
	_titleMenu = IMAGEMANAGER->AddImage("titleMenu", "image/titleMenu.bmp", 220, 290, 175, 127, false, false);

	_y = 320;

	_select = 0;
	_count = 0;

	FONTMANAGER->AddFont("메인메뉴", 25, 0, "바탕체");

	return S_OK;
}

void mainMenu::Release()
{
	DeleteObject(SelectObject(GetMemDC(), newbrush));
	DeleteObject(SelectObject(GetMemDC(), newbrush1));
	DeleteObject(SelectObject(GetMemDC(), oldbrush));
	DeleteObject(SelectObject(GetMemDC(), oldbrush1));
}

void mainMenu::Update()
{
	_selectBox = RectMakeCenter(310, _y, 160, 20);

	if (KEY->IsOnceKeyDown(VK_UP))
	{
		//SOUNDMANAGER->Play("titleknock", 1.0f);
		if (_select > 0)
		{
			_select--;
			_y -= 35;
		}
	}
	if (KEY->IsOnceKeyDown(VK_DOWN))
	{
		//SOUNDMANAGER->Play("titleknock", 1.0f);
		if (_select < 2)
		{
			_select++;
			_y += 35;
		}
	}

	if (KEY->IsOnceKeyDown(VK_RETURN) || KEY->IsOnceKeyDown('Z'))
	{
		//SOUNDMANAGER->Play("select", 1.0f);
		//SOUNDMANAGER->Stop("title");
		if (_select == 0)
		{
			SCENEMANAGER->ChangeScene("opening");
		}
		else if (_select == 1)
		{
			IB->Load();
			SCENEMANAGER->ChangeScene(IB->GetSaveScene());
		}
		else if (_select == 2)
		{
			exit(0);
		}
	}
}

void mainMenu::Render()
{
	newbrush = CreateSolidBrush(RGB(30, 30, 30));
	newbrush1 = CreateSolidBrush(RGB(50, 50, 50));
	oldbrush = (HBRUSH)SelectObject(GetMemDC(), newbrush);
	oldbrush1 = (HBRUSH)SelectObject(GetMemDC(), newbrush1);

	_titleImg->Render(GetMemDC());
	_titleMenu->Render(GetMemDC());

	_count++;

	if (_select == 0)
	{
		if (_count % 20 == 0 || _count % 20 == 1 || _count % 20 == 2 || _count % 20 == 3 || _count % 20 == 4 || 
			_count % 20 == 5 || _count % 20 == 6 || _count % 20 == 7 || _count % 20 == 8 || _count % 20 == 9)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush);
		}

		if (_count % 20 == 10 || _count % 20 == 11 || _count % 20 == 12 || _count % 20 == 13 || _count % 20 == 14 
			|| _count % 20 == 15 || _count % 20 == 16 || _count % 20 == 17 || _count % 20 == 18 || _count % 20 == 19)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush1);
		}

		if (_count > 200) _count = 0;

		wstring str = (L"New game");
		FONTMANAGER->TextRender(GetMemDC(), 260, 305, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Continue");
		FONTMANAGER->TextRender(GetMemDC(), 260, 340, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Exit");
		FONTMANAGER->TextRender(GetMemDC(), 285, 375, str, "메인메뉴", RGB(255, 255, 255));
	}
	else if (_select == 1)
	{
		if (_count % 20 == 0 || _count % 20 == 1 || _count % 20 == 2 || _count % 20 == 3 || _count % 20 == 4 ||
			_count % 20 == 5 || _count % 20 == 6 || _count % 20 == 7 || _count % 20 == 8 || _count % 20 == 9)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush);
		}

		if (_count % 20 == 10 || _count % 20 == 11 || _count % 20 == 12 || _count % 20 == 13 || _count % 20 == 14
			|| _count % 20 == 15 || _count % 20 == 16 || _count % 20 == 17 || _count % 20 == 18 || _count % 20 == 19)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush1);
		}

		if (_count > 200) _count = 0;

		wstring str = (L"New game");
		FONTMANAGER->TextRender(GetMemDC(), 260, 305, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Continue");
		FONTMANAGER->TextRender(GetMemDC(), 260, 340, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Exit");
		FONTMANAGER->TextRender(GetMemDC(), 285, 375, str, "메인메뉴", RGB(255, 255, 255));

	}
	else if (_select == 2)
	{
		if (_count % 20 == 0 || _count % 20 == 1 || _count % 20 == 2 || _count % 20 == 3 || _count % 20 == 4 ||
			_count % 20 == 5 || _count % 20 == 6 || _count % 20 == 7 || _count % 20 == 8 || _count % 20 == 9)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush);
		}

		if (_count % 20 == 10 || _count % 20 == 11 || _count % 20 == 12 || _count % 20 == 13 || _count % 20 == 14
			|| _count % 20 == 15 || _count % 20 == 16 || _count % 20 == 17 || _count % 20 == 18 || _count % 20 == 19)
		{
			FillRect(GetMemDC(), &_selectBox, oldbrush1);
		}

		if (_count > 200) _count = 0;

		wstring str = (L"New game");
		FONTMANAGER->TextRender(GetMemDC(), 260, 305, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Continue");
		FONTMANAGER->TextRender(GetMemDC(), 260, 340, str, "메인메뉴", RGB(255, 255, 255));
		str = (L"Exit");
		FONTMANAGER->TextRender(GetMemDC(), 285, 375, str, "메인메뉴", RGB(255, 255, 255));
	}

}