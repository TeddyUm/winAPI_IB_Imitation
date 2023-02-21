#include "stdafx.h"
#include "museum2F_2.h"


museum2F_2::museum2F_2()
{
}


museum2F_2::~museum2F_2()
{
}

HRESULT museum2F_2::Init()
{
	_back = IMAGEMANAGER->AddImage("museum2F_2", "image/map/museum2F_2.bmp", 640, 1250, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum2F_2_b", "image/map/museum2F_2_b.bmp", 640, 1250, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum2F_2_b", 640, 1250);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));

	_guest1 = IMAGEMANAGER->AddFrameImage("guest1", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest2 = IMAGEMANAGER->AddFrameImage("guest2", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest3 = IMAGEMANAGER->AddFrameImage("guest3", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest4 = IMAGEMANAGER->AddFrameImage("guest4", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest5 = IMAGEMANAGER->AddFrameImage("guest5", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest6 = IMAGEMANAGER->AddFrameImage("guest6", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest7 = IMAGEMANAGER->AddFrameImage("guest7", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest8 = IMAGEMANAGER->AddFrameImage("guest8", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest1 = RectMake(227, 235, 25, 20);
		_rcGuest2 = RectMake(482, 235, 25, 20);
		_rcGuest3 = RectMake(425, 520, 25, 20);
		_rcGuest4 = RectMake(455, 520, 25, 20);
		_rcGuest5 = RectMake(370, 655, 25, 20);
		_rcGuest6 = RectMake(433, 850, 25, 20);
		_rcGuest7 = RectMake(165, 942, 25, 20);
		_rcGuest8 = RectMake(195, 942, 25, 20);
	}

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_alpha = 255;

	_objectText = new objectText;
	_endTalk = false;
	_guestEvent1 = false;
	_pictureEvent1 = false;

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcPicture1 = RectMakeCenter(350, 220, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum2F_2::Release()
{
}

void museum2F_2::Update()
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
		_objectText->SetTextNum(56);
	}

	if (_guestEvent1 == true)
	{
		if (_objectText->GetTextNum() < 59)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 58)
		{
			_state = ST_IDLE;
			_guestEvent1 = false;
		}
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture1) && _endTalk == false)
	{
		_pictureEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(59);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 60)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 59)
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
		IB->SetNextPos(600, 230);
		SCENEMANAGER->ChangeScene("museum2F_1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(600, 325);
		SCENEMANAGER->ChangeScene("museum2F_3");
	}
}

void museum2F_2::Render()
{
	//_backPX->Render(_backRC->GetMemDC());

	if (IB->GetFlags()._anotherWorld != true)
	{
		_back->Render(_backRC->GetMemDC());

		_guest1->FrameRender(_backRC->GetMemDC(), _rcGuest1.left - 12, _rcGuest1.bottom - _guest1->GetFrameHeight(), 4, 0);
		_guest2->FrameRender(_backRC->GetMemDC(), _rcGuest2.left - 12, _rcGuest2.bottom - _guest1->GetFrameHeight(), 8, 3);
		_guest3->FrameRender(_backRC->GetMemDC(), _rcGuest3.left - 12, _rcGuest3.bottom - _guest1->GetFrameHeight(), 7, 0);
		_guest4->FrameRender(_backRC->GetMemDC(), _rcGuest4.left - 12, _rcGuest4.bottom - _guest1->GetFrameHeight(), 3, 3);
		_guest5->FrameRender(_backRC->GetMemDC(), _rcGuest5.left - 20, _rcGuest5.bottom - _guest1->GetFrameHeight(), 6, 2);
		_guest6->FrameRender(_backRC->GetMemDC(), _rcGuest6.left - 12, _rcGuest6.bottom - _guest1->GetFrameHeight(), 6, 3);
		_guest7->FrameRender(_backRC->GetMemDC(), _rcGuest7.left - 12, _rcGuest7.bottom - _guest1->GetFrameHeight(), 1, 0);
		_guest8->FrameRender(_backRC->GetMemDC(), _rcGuest8.left - 12, _rcGuest8.bottom - _guest1->GetFrameHeight(), 0, 0);
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

	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_guestEvent1 == true || _pictureEvent1 == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}

	Menu();
}