#include "stdafx.h"
#include "museum1F_3.h"


museum1F_3::museum1F_3()
{
}


museum1F_3::~museum1F_3()
{
}

HRESULT museum1F_3::Init()
{
	_back = IMAGEMANAGER->AddImage("museum1F_3", "image/map/museum1F_3.bmp", 640, 1250, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum1F_3_b", "image/map/museum1F_3_b.bmp", 640, 1250, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum1F_3_b", 640, 1250);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));

	_guest1 = IMAGEMANAGER->AddFrameImage("guest1", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest2 = IMAGEMANAGER->AddFrameImage("guest2", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest3 = IMAGEMANAGER->AddFrameImage("guest3", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest4 = IMAGEMANAGER->AddFrameImage("guest4", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest5 = IMAGEMANAGER->AddFrameImage("guest5", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest1 = RectMake(225, 240, 25, 20);
		_rcGuest2 = RectMake(480, 530, 25, 20);
		_rcGuest3 = RectMake(380, 750, 25, 20);
		_rcGuest4 = RectMake(390, 780, 25, 20);
		_rcGuest5 = RectMake(190, 950, 25, 20);
	}

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_alpha = 255;

	_objectText = new objectText;
	_endTalk = false;
	_guestEvent1 = false;
	_guestEvent2 = false;

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum1F_3::Release()
{
}

void museum1F_3::Update()
{
	RECT _rcTemp;

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest1) && _endTalk == false)
	{
		_guestEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(36);
	}

	if (_guestEvent1 == true)
	{
		if (_objectText->GetTextNum() < 37)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 36)
		{
			_state = ST_IDLE;
			_guestEvent1 = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest5) && _endTalk == false)
	{
		_guestEvent2 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(37);
	}

	if (_guestEvent2 == true)
	{
		if (_objectText->GetTextNum() < 38)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 37)
		{
			_state = ST_IDLE;
			_guestEvent2 = false;
		}
	}

	Move();
	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(540, 450);
		SCENEMANAGER->ChangeScene("museum1F_1");
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(580, 325);
		SCENEMANAGER->ChangeScene("museum1F_2");
	}
}

void museum1F_3::Render()
{
	//_backPX->Render(_backRC->GetMemDC());

	if (IB->GetFlags()._anotherWorld != true)
	{
		_back->Render(_backRC->GetMemDC());

		_guest1->FrameRender(_backRC->GetMemDC(), _rcGuest1.left - 12, _rcGuest1.bottom - _guest1->GetFrameHeight(), 2, 0);
		_guest2->FrameRender(_backRC->GetMemDC(), _rcGuest2.left - 12, _rcGuest2.bottom - _guest1->GetFrameHeight(), 8, 2);
		_guest3->FrameRender(_backRC->GetMemDC(), _rcGuest3.left - 12, _rcGuest3.bottom - _guest1->GetFrameHeight(), 6, 0);
		_guest4->FrameRender(_backRC->GetMemDC(), _rcGuest4.left - 12, _rcGuest4.bottom - _guest1->GetFrameHeight(), 8, 0);
		_guest5->FrameRender(_backRC->GetMemDC(), _rcGuest5.left - 12, _rcGuest5.bottom - _guest1->GetFrameHeight(), 5, 3);
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

	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_guestEvent1 == true || _guestEvent2 == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}

	Menu();
}