#include "stdafx.h"
#include "museum2F_1.h"


museum2F_1::museum2F_1()
{
}


museum2F_1::~museum2F_1()
{
}

HRESULT museum2F_1::Init()
{
	_back = IMAGEMANAGER->AddImage("museum2F_1", "image/map/museum2F_1.bmp", 640, 797, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum2F_1_b", "image/map/museum2F_1_b.bmp", 640, 797, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum2F_1_b", 640, 797);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));

	_guest1 = IMAGEMANAGER->AddFrameImage("guest1", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest2 = IMAGEMANAGER->AddFrameImage("garry2", "image/character/garry.bmp", 192, 264, 4, 4, true, RGB(2, 156, 0));
	_guest3 = IMAGEMANAGER->AddFrameImage("guest3", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest4 = IMAGEMANAGER->AddFrameImage("guest4", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_window = IMAGEMANAGER->AddFrameImage("windowH", "image/map/m2F_window.bmp", 380, 35, 9, 1, true, RGB(32, 156, 0));

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest1 = RectMake(232, 160, 25, 20);
		_rcGuest2 = RectMake(335, 150, 25, 20);
		_rcGuest3 = RectMake(265, 350, 25, 20);
		_rcGuest4 = RectMake(370, 595, 25, 20);
	}

	_rcPicture1 = RectMake(330, 420, 30, 20);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_alpha = 255;

	_objectText = new objectText;
	_endTalk = false;
	_guestEvent1 = false;
	_pictureEvent1 = false;
	_guestEvent2 = false;

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcWindow = RectMakeCenter(50, 150, 800, 200);
	_rcWindowD = RectMakeCenter(140, 150, 30, 20);

	_frameX = 0;
	_frameY = 0;
	_count = 0;
	_frameXWindow = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum2F_1::Release()
{
}

void museum2F_1::Update()
{
	RECT _rcTemp;

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (IntersectRect(&_rcTemp, &_rc, &_rcWindow) && IB->GetFlags()._anotherCheck == true)
	{
		_count++;
		if (_count == 10)
		{
			_frameXWindow++;
			if (_frameXWindow > 8) _frameXWindow = 8;
		}
		if (_count > 10) _count = 0;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest3) && _endTalk == false)
	{
		_guestEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(51);
	}

	if (_guestEvent1 == true)
	{
		if (_objectText->GetTextNum() < 52)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 51)
		{
			_state = ST_IDLE;
			_guestEvent1 = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcWindowD) && _endTalk == false)
	{
		_windowEvent = true;
		_endTalk = true;
		_objectText->Init();
		if(IB->GetFlags()._anotherCheck == true) _objectText->SetTextNum(19);
		if(IB->GetFlags()._anotherCheck != true) _objectText->SetTextNum(14);
	}

	if (_windowEvent == true)
	{
		if (IB->GetFlags()._anotherCheck == true)
		{
			if (_objectText->GetTextNum() < 20)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 19)
			{
				_state = ST_IDLE;
				_windowEvent = false;
			}
		}
		if (IB->GetFlags()._anotherCheck != true)
		{
			if (_objectText->GetTextNum() < 15)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 14)
			{
				_state = ST_IDLE;
				_windowEvent = false;
			}
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest2) && _endTalk == false)
	{
		_guestEvent2 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(50);
	}

	if (_guestEvent2 == true)
	{
		if (_objectText->GetTextNum() < 51)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 50)
		{
			_state = ST_IDLE;
			_guestEvent2 = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture1) && _endTalk == false)
	{
		_pictureEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(52);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 53)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 52)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}
	Move();

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(530, 130	);
		SCENEMANAGER->ChangeScene("museumS");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 255, 0))
	{
		IB->SetNextPos(50, 325);
		SCENEMANAGER->ChangeScene("museum2F_2");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(50, 325);
		SCENEMANAGER->ChangeScene("museum2F_3");
	}
}

void museum2F_1::Render()
{
	//_backPX->Render(_backRC->GetMemDC());

	if (IB->GetFlags()._anotherWorld != true)
	{
		_back->Render(_backRC->GetMemDC());

		_guest1->FrameRender(_backRC->GetMemDC(), _rcGuest1.left - 12, _rcGuest1.bottom - _guest1->GetFrameHeight(), 3, 1);
		_guest2->FrameRender(_backRC->GetMemDC(), _rcGuest2.left - 12, _rcGuest2.bottom - _guest1->GetFrameHeight(), 1, 0);
		_guest3->FrameRender(_backRC->GetMemDC(), _rcGuest3.left - 12, _rcGuest3.bottom - _guest1->GetFrameHeight(), 9, 1);
		_guest4->FrameRender(_backRC->GetMemDC(), _rcGuest4.left - 12, _rcGuest4.bottom - _guest1->GetFrameHeight(), 5, 2);
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
	//RectDraw(_backRC->GetMemDC(), _rcWindowD);

	_window->FrameRender(_backRC->GetMemDC(), 118, 100, _frameXWindow, 0);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_guestEvent1 == true || _pictureEvent1 == true || _guestEvent2 == true || _windowEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}
	Menu();
}