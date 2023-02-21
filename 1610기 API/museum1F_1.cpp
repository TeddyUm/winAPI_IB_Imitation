#include "stdafx.h"
#include "museum1F_1.h"


museum1F_1::museum1F_1()
{
}


museum1F_1::~museum1F_1()
{
}

HRESULT museum1F_1::Init()
{
	//SOUNDMANAGER->AddSound("water", "sound/water.wav", false, false);

	_back = IMAGEMANAGER->AddImage("museum1F_1a", "image/map/museum1F_1a.bmp", 640, 797, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum1F_1_b", "image/map/museum1F_1b.bmp", 640, 797, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum1F_1_b", 640, 797);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));

	_wall = IMAGEMANAGER->AddImage("museum1F_1_wall", "image/map/museum1F_1_wall.bmp", 277, 348, 90, 35, false, false);
	_guest1 = IMAGEMANAGER->AddFrameImage("guest1", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest2 = IMAGEMANAGER->AddFrameImage("guest2", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest3 = IMAGEMANAGER->AddFrameImage("guest3", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest4 = IMAGEMANAGER->AddFrameImage("guest4", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest5 = IMAGEMANAGER->AddFrameImage("guest5", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest6 = IMAGEMANAGER->AddFrameImage("guest6", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest7 = IMAGEMANAGER->AddFrameImage("guest7", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest8 = IMAGEMANAGER->AddFrameImage("guest8", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);

	_rcPicture1 = RectMake(163, 220, 25, 20);
	_rcPicture2 = RectMake(303, 220, 30, 20);
	_rcPicture3 = RectMake(303, 590, 40, 20);

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest1 = RectMake(367, 232, 25, 20);
		_rcGuest2 = RectMake(250, 325, 25, 20);
		_rcGuest3 = RectMake(365, 325, 25, 20);
		_rcGuest4 = RectMake(175, 435, 25, 20);
		_rcGuest5 = RectMake(175, 470, 25, 20);
		_rcGuest6 = RectMake(440, 420, 25, 20);
		_rcGuest7 = RectMake(290, 610, 25, 20);
		_rcGuest8 = RectMake(390, 595, 25, 20);
	}

	_alpha = 255;

	_objectText = new objectText;
	_endTalk = false;

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum1F_1::Release()
{
}

void museum1F_1::Update()
{
	RECT _rcTemp;
	Move();

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest1) && _endTalk == false)
	{
		_guest1Event = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(28);
	}

	if (_guest1Event == true)
	{
		if (_objectText->GetTextNum() < 30)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 29)
		{
			_state = ST_IDLE;
			_guest1Event = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest3) && _endTalk == false)
	{
		_guest2Event = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(30);
	}

	if (_guest2Event == true)
	{
		if (_objectText->GetTextNum() < 31)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 30)
		{
			_state = ST_IDLE;
			_guest2Event = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture1) && _endTalk == false)
	{
		_picture1Event = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(21);
	}

	if (_picture1Event == true)
	{
		if (_objectText->GetTextNum() < 24)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 23)
		{
			_state = ST_IDLE;
			_picture1Event = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture2) && _endTalk == false)
	{
		_picture2Event = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(24);
	}

	if (_picture2Event == true)
	{
		if (_objectText->GetTextNum() < 26)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 25)
		{
			_state = ST_IDLE;
			_picture2Event = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture3) && _endTalk == false)
	{
		_picture3Event = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(26);
	}

	if (_picture3Event == true)
	{
		if (_objectText->GetTextNum() < 28)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 27)
		{
			_state = ST_IDLE;
			_picture3Event = false;
		}
	}

	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(550, 350);
		SCENEMANAGER->ChangeScene("museumS");
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 255, 0))
	{
		IB->SetNextPos(70, 320);
		SCENEMANAGER->ChangeScene("museum1F_3");
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(325, 70);
		SCENEMANAGER->ChangeScene("museum1F_2");
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(200, 200, 0))
	{
		//SOUNDMANAGER->Play("water", 1.f);
		IB->SetNextPos(310, 70);
		stFlags flags = IB->GetFlags();
		flags._anotherWorld = false;
		IB->SetFlags(flags);
		SCENEMANAGER->ChangeScene("blue1");
	}
}

void museum1F_1::Render()
{
	PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
	_back->AlphaRender(_backRC->GetMemDC(), _alpha);
	//_backPX->Render(_backRC->GetMemDC());

	if (IB->GetFlags()._anotherWorld != true)
	{
		PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
		_back->AlphaRender(_backRC->GetMemDC(), _alpha);
		_guest1->FrameRender(_backRC->GetMemDC(), _rcGuest1.left - 12, _rcGuest1.bottom - _guest1->GetFrameHeight(), 5, 1);
		_guest2->FrameRender(_backRC->GetMemDC(), _rcGuest2.left - 12, _rcGuest2.bottom - _guest1->GetFrameHeight(), 0, 1);
		_guest3->FrameRender(_backRC->GetMemDC(), _rcGuest3.left - 12, _rcGuest3.bottom - _guest1->GetFrameHeight(), 2, 1);
		_guest4->FrameRender(_backRC->GetMemDC(), _rcGuest4.left - 12, _rcGuest4.bottom - _guest1->GetFrameHeight(), 6, 1);
		_guest5->FrameRender(_backRC->GetMemDC(), _rcGuest5.left - 12, _rcGuest5.bottom - _guest1->GetFrameHeight(), 8, 1);
		_guest6->FrameRender(_backRC->GetMemDC(), _rcGuest6.left, _rcGuest6.bottom - _guest1->GetFrameHeight(), 2, 2);
		_guest7->FrameRender(_backRC->GetMemDC(), _rcGuest7.left - 12, _rcGuest7.bottom - _guest1->GetFrameHeight(), 3, 2);
		_guest8->FrameRender(_backRC->GetMemDC(), _rcGuest8.left - 12, _rcGuest8.bottom - _guest1->GetFrameHeight(), 0, 2);
	}
	else
	{
		PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
		_back->AlphaRender(_backRC->GetMemDC(), _alpha);
	}

	//RectDraw(_backRC->GetMemDC(), _rcGuest1);
	//RectDraw(_backRC->GetMemDC(), _rcGuest2);
	//RectDraw(_backRC->GetMemDC(), _rcGuest3);
	//RectDraw(_backRC->GetMemDC(), _rcGuest4);
	//RectDraw(_backRC->GetMemDC(), _rcGuest5);
	//RectDraw(_backRC->GetMemDC(), _rcGuest6);
	//RectDraw(_backRC->GetMemDC(), _rcGuest7);
	//RectDraw(_backRC->GetMemDC(), _rcGuest8);
	//RectDraw(_backRC->GetMemDC(), _rc);

	if (IB->GetFlags()._underWorld == true)
	{
		_back = IMAGEMANAGER->AddImage("museum1F_1", "image/map/museum1F_1.bmp", 640, 797, false, false);
	}

	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_guest1Event == true || _guest2Event == true || _guest3Event == true || 
		_picture1Event == true || _picture2Event == true || _picture3Event == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}

	Menu();
}