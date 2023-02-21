#include "stdafx.h"
#include "museum1F_2.h"


museum1F_2::museum1F_2()
{
}


museum1F_2::~museum1F_2()
{
}

HRESULT museum1F_2::Init()
{
	_back = IMAGEMANAGER->AddImage("museum1F_2", "image/map/museum1F_2.bmp", 640, 580, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum1F_2_b", "image/map/museum1F_2_b.bmp", 640, 580, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum1F_2_b", 640, 580);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_guest1 = IMAGEMANAGER->AddFrameImage("guest1", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_picture = IMAGEMANAGER->AddFrameImage("pictureH", "image/map/m1F_2_picture.bmp", 260, 44, 5, 1, true, RGB(32, 156, 0));

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest1 = RectMake(180, 260, 25, 20);
	}
	_rcPicture = RectMake(520, 230, 30, 20);
	_rcPictureH = RectMake(360, 150, 300, 450);
	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_alpha = 255;

	_objectText = new objectText;
	_endTalk = false;
	_guestEvent1 = false;

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;
	_frameXpicture = 0;
	_count = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum1F_2::Release()
{
}

void museum1F_2::Update()
{
	RECT _rcTemp;
	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}

	Move();

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcGuest1) && _endTalk == false)
	{
		_guestEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(44);
	}

	if (_guestEvent1 == true)
	{
		if (_objectText->GetTextNum() < 46)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 45)
		{
			_state = ST_IDLE;
			_guestEvent1 = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture) && _endTalk == false)
	{
		_pictureEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(43);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 44)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 43)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	if (IntersectRect(&_rcTemp, &_rc, &_rcPictureH) && IB->GetFlags()._anotherCheck == true)
	{
		_count++;
		if (_count == 10)
		{
			_frameXpicture++;
			if (_frameXpicture > 4) _frameXpicture = 4;
		}
		if (_count > 10) _count = 0;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(325, 700);
		SCENEMANAGER->ChangeScene("museum1F_1");
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(70, 1050);
		SCENEMANAGER->ChangeScene("museum1F_3");
	}
}

void museum1F_2::Render()
{
	//_backPX->Render(_backRC->GetMemDC());
	if (IB->GetFlags()._anotherWorld != true)
	{
		_back->Render(_backRC->GetMemDC());

		_guest1->FrameRender(_backRC->GetMemDC(), _rcGuest1.left - 12, _rcGuest1.bottom - _guest1->GetFrameHeight(), 3, 0);
	}
	else
	{
		PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
		_back->AlphaRender(_backRC->GetMemDC(), _alpha);
	}
	//RectDraw(_backRC->GetMemDC(), _rcGuest1);
	_picture->FrameRender(_backRC->GetMemDC(), 502, 148, _frameXpicture, 0);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);
	if (_guestEvent1 == true || _pictureEvent1 == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}
	
	Menu();
}