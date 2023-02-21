#include "stdafx.h"
#include "museumS.h"


museumS::museumS()
{
}


museumS::~museumS()
{
}

HRESULT museumS::Init()
{
	//SOUNDMANAGER->AddSound("museum", "sound/museum.mp3", true, true);
	//SOUNDMANAGER->AddSound("itemopen", "sound/itemopen.wav", false, false);
	//SOUNDMANAGER->AddSound("itemclose", "sound/itemclose.wav", false, false);
	if (IB->GetFlags()._start != true)
	{
		//SOUNDMANAGER->Play("museum", 1.0f);
	}
	_back = IMAGEMANAGER->AddImage("museumS", "image/map/museumS.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("museumS_b", "image/map/museumS_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer", 640, 480);

	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_counter = IMAGEMANAGER->AddFrameImage("counter", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_guest = IMAGEMANAGER->AddFrameImage("guest", "image/character/subchara.bmp", 480, 256, 10, 4, true, RGB(32, 156, 0));
	_father = IMAGEMANAGER->AddFrameImage("father", "image/character/father.bmp", 144, 256, 3, 4, true, RGB(32, 156, 0));
	_mother = IMAGEMANAGER->AddFrameImage("mother", "image/character/mother.bmp", 144, 256, 3, 4, true, RGB(32, 156, 0));
	_dialogue = IMAGEMANAGER->AddImage("dialogue", "image/dialogue.bmp", 480, 120, false, false);
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_motherP1 = IMAGEMANAGER->AddImage("motherP1", "image/portrait/motherP1.bmp", 120, 115, false, false);
	_fatherP1 = IMAGEMANAGER->AddImage("fatherP1", "image/portrait/fatherP1.bmp", 120, 115, false, false);
	_motherP2 = IMAGEMANAGER->AddImage("motherP2", "image/portrait/motherP2.bmp", 120, 115, false, false);
	_motherP3 = IMAGEMANAGER->AddImage("motherP3", "image/portrait/motherP3.bmp", 120, 115, false, false);

	_objectText = new objectText;
	_endTalk = false;
	_startEvent = false;
	_guestEvent = false;
	_counterEvent = false;
	_entEvent = false;
	_pampEvent = false;
	_windowEvent = false;
	_motherEvent = false;
	_fatherEvent = false;
	_anotherCheck = false;
	_anotherText = false;
	_countLight = 0;
	_alpha = 255;

	if (IB->GetFlags()._start == false)
	{
		IB->SetNextPos(275, 325);
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}
	else
	{
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;

	if (IB->GetFlags()._anotherWorld != true)
	{
		_rcGuest = RectMake(187, 245, 30, 20);
		_rcCounter = RectMake(330, 220, 50, 50);
		_rcFather = RectMake(320, 315, 25, 20);
		_rcMother = RectMake(290, 315, 25, 20);
	}
	_rcPamp = RectMake(260, 285, 25, 30);
	_rcWindow = RectMake(87, 220, 50, 30);
	_rcEnt = RectMake(0, 260, 50, 130);

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	_objectText->Init();
	_objectText->SetTextNum(0);

	return S_OK;
}

void museumS::Release()
{

}

void museumS::Update()
{
	RECT _rcTemp;
	Move();

	//// 시작 이벤트
	if (IB->GetFlags()._start == false)
	{
		_startEvent = true;
	
		if (_objectText->GetTextNum() < 10)
		{
			_objectText->Update();
			_state = ST_STOP;
		}
	
		if (_objectText->GetTextNum() > 9)
		{
			_state = ST_IDLE;
			_startEvent = false;
			stFlags flags = IB->GetFlags();
			//flags._anotherCheck = false;
			flags._start = true;
			IB->SetFlags(flags);
		}
	}

	// 각종 자잘한 이벤트들 초기화, 다른 세계가 아닐때
	if (IB->GetFlags()._anotherWorld != true)
	{
		if (IntersectRect(&_rcTemp, &_rc, &_rcWindow) && KEY->IsOnceKeyDown('Z'))
		{
			if (_windowEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(14);
				_windowEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcMother) && KEY->IsOnceKeyDown('Z'))
		{
			if (_motherEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(10);
				_motherEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcFather) && KEY->IsOnceKeyDown('Z'))
		{
			if (_fatherEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(11);
				_fatherEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcPamp) && KEY->IsOnceKeyDown('Z') && _startEvent == false)
		{
			if (_pampEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(16);
				_pampEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcGuest) && KEY->IsOnceKeyDown('Z'))
		{
			if (_guestEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(13);
				_guestEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcCounter) && _ibMoveC == false)
		{
			if (_counterEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(12);
				_counterEvent = true;
			}
		}
		if (IntersectRect(&_rcTemp, &_rc, &_rcEnt) && _ibMoveE == false)
		{
			if (_entEvent == false)
			{
				_objectText->Init();
				_objectText->SetTextNum(15);
				_entEvent = true;
			}
		}
	}

	// 각종 자잘한 이벤트들 초기화, 다른 세계일 때
	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}

	// 이벤트 진행 업데이트 란, 다른 세계가 아닐때
	if (IB->GetFlags()._anotherWorld != true)
	{
		if (_windowEvent == true)
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
		if (_guestEvent == true)
		{
			if (_objectText->GetTextNum() < 14)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 13)
			{
				_state = ST_IDLE;
				_guestEvent = false;
			}
		}
		if (_pampEvent == true)
		{
			if (_objectText->GetTextNum() < 18)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 17)
			{
				_state = ST_IDLE;
				_pampEvent = false;
			}
		}
		if (_motherEvent == true)
		{
			if (_objectText->GetTextNum() < 11)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 10)
			{
				_state = ST_IDLE;
				_motherEvent = false;
			}
		}
		if (_fatherEvent == true)
		{
			if (_objectText->GetTextNum() < 12)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 11)
			{
				_state = ST_IDLE;
				_fatherEvent = false;
			}
		}
		if (_counterEvent == true)
		{
			if (_objectText->GetTextNum() < 13)
			{
				_objectText->Update();
				_state = ST_STOP;
				_ibMoveC = true;
			}

			if (_objectText->GetTextNum() > 12)
			{
				_state = ST_IDLE;
				_counterEvent = false;
			}
		}
		if (_entEvent == true)
		{
			if (_objectText->GetTextNum() < 16)
			{
				_objectText->Update();
				_state = ST_STOP;
				_ibMoveE = true;
			}

			if (_objectText->GetTextNum() > 15)
			{
				_state = ST_IDLE;
				_entEvent = false;
			}
		}
	}

	if (_ibMoveE == true && _state == ST_IDLE)
	{
		_x += 100 * TIMEMANAGER->GetElapsedTime();
		FrameCount();
		_frameY = 1;
	}
	if (_x > 80)
	{
		_ibMoveE = false;
	}

	if (_ibMoveC == true && _state == ST_IDLE)
	{
		_x += 100 * TIMEMANAGER->GetElapsedTime();
		FrameCount();
		_frameY = 1;
	}
	if (_x > 410)
	{
		_ibMoveC = false;
	}

	// 이벤트 진행 업데이트 란, 다른 세계일 때
	if (IB->GetFlags()._anotherWorld == true)
	{

	}

	// 다른세계 첫 진입 시
	if (IB->GetFlags()._anotherWorld == true && IB->GetFlags()._anotherCheck != true)
	{
		_anotherCheck = true;
		stFlags _flags = IB->GetFlags();
		_flags._anotherCheck = true;
		IB->SetFlags(_flags);
	}

	// 다른 세계 진입 시 깜빡임
	if (_anotherCheck == true)
	{
		_state = ST_STOP;
		_countLight++;
		if (_countLight < 10)
		{
			_alpha = 150;
		}
		else if (_countLight > 9 && _countLight < 20)
		{
			_alpha = 255;
		}
		else if (_countLight > 19 && _countLight < 30)
		{
			_alpha = 150;
		}
		else if (_countLight > 29 && _countLight < 40)
		{
			_alpha = 255;
		}
		else if (_countLight > 39 && _countLight < 50)
		{
			_alpha = 150;
		}
		else if (_countLight > 49 && _countLight < 60)
		{
			_alpha = 255;
		}
		if (_countLight > 59)
		{
			_state = ST_IDLE;
			_anotherCheck = false;
			_alpha = 150;
			if (_anotherText == false)
			{
				_anotherText = true;
				_objectText->Init();
				_objectText->SetTextNum(31);
			}
		}
	}

	if (_anotherText == true)
	{
		if (_objectText->GetTextNum() < 32)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 31)
		{
			_state = ST_IDLE;
			_anotherText = false;
		}
	}

	// 다른 층 이동 픽셀 충동
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		if (IB->GetFlags()._anotherWorld != true)
		{
			stFlags flags = IB->GetFlags();
			flags._start = true;
			IB->SetFlags(flags);
		}

		IB->SetNextPos(140, 300);
		SCENEMANAGER->ChangeScene("museum2F_1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 255, 0))
	{
		if (IB->GetFlags()._anotherWorld != true)
		{
			stFlags flags = IB->GetFlags();
			flags._start = true;
			IB->SetFlags(flags);
		}

		IB->SetNextPos(100, 450);
		SCENEMANAGER->ChangeScene("museum1F_1");
	}
}

void museumS::Render()
{
	if (IB->GetFlags()._start == true)
	{
		if (IB->GetFlags()._anotherWorld != true)
		{
			_back->Render(_backRC->GetMemDC());

			_father->FrameRender(_backRC->GetMemDC(), _rcFather.left - 12, _rcFather.bottom - _father->GetFrameHeight(), 1, 0);
			_mother->FrameRender(_backRC->GetMemDC(), _rcMother.left - 12, _rcMother.bottom - _mother->GetFrameHeight(), 1, 0);
			_counter->FrameRender(_backRC->GetMemDC(), _rcCounter.left - 28, _rcCounter.bottom - _mother->GetFrameHeight() - 10, 7, 2);
			_guest->FrameRender(_backRC->GetMemDC(), _rcGuest.left - 12, _rcGuest.bottom - _mother->GetFrameHeight(), 5, 0);
		}
		else
		{
			PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
			_back->AlphaRender(_backRC->GetMemDC(), _alpha);
		}
		if (KEY->IsStayKeyDown('Q'))
		{
			_backPX->Render(_backRC->GetMemDC());
		}
		_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
		_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);
	}

	else
	{
		if (IB->GetFlags()._anotherWorld != true)
		{
			_back->Render(_backRC->GetMemDC());

			_father->FrameRender(_backRC->GetMemDC(), _rcFather.left - 12, _rcFather.bottom - _father->GetFrameHeight(), 1, 0);
			_mother->FrameRender(_backRC->GetMemDC(), _rcMother.left - 12, _rcMother.bottom - _mother->GetFrameHeight(), 1, 0);
			_counter->FrameRender(_backRC->GetMemDC(), _rcCounter.left - 28, _rcCounter.bottom - _mother->GetFrameHeight() - 10, 7, 2);
			_guest->FrameRender(_backRC->GetMemDC(), _rcGuest.left - 12, _rcGuest.bottom - _mother->GetFrameHeight(), 5, 0);
		}
		else
		{
			PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
			_back->AlphaRender(_backRC->GetMemDC(), _alpha);
		}

		_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);

		_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);
	}

	Menu();

	if (_startEvent == true)
	{
		_dialogue->Render(GetMemDC(),150, 350);
		if (_objectText->GetTextNum() < 4)
		{
			_motherP1->Render(GetMemDC(), 20, 350);
		}
		if (_objectText->GetTextNum() == 4)
		{
			_fatherP1->Render(GetMemDC(), 20, 350);
		}
		if (_objectText->GetTextNum() == 5)
		{
			_motherP1->Render(GetMemDC(), 20, 350);
		}
		if (_objectText->GetTextNum() == 6)
		{
			_motherP2->Render(GetMemDC(), 20, 350);
		}
		if (_objectText->GetTextNum() < 10 && _objectText->GetTextNum() > 6)
		{
			_motherP3->Render(GetMemDC(), 20, 350);
		}
		_objectText->Render(GetMemDC(), 170, 370);
	}

	if (_windowEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}
	if (_guestEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}
	if (_pampEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}
	if (_motherEvent == true)
	{
		_motherP1->Render(GetMemDC(), 20, 350);
		_dialogue->Render(GetMemDC(), 150, 350);
		_objectText->Render(GetMemDC(), 170, 370);
	}
	if (_fatherEvent == true)
	{
		_dialogue->Render(GetMemDC(), 150, 350);
		_objectText->Render(GetMemDC(), 170, 370);
	}
	if (_entEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}
	if (_counterEvent == true)
	{
		_motherP3->Render(GetMemDC(), 20, 350);
		_dialogue->Render(GetMemDC(), 150, 350);
		_objectText->Render(GetMemDC(), 170, 370);
	}

	if (_anotherText == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}

	//RectDraw(GetMemDC(), _rcGuest);
	//RectDraw(GetMemDC(), _rcCounter);
	//RectDraw(GetMemDC(), _rcFather);
	//RectDraw(GetMemDC(), _rcMother);
	//RectDraw(GetMemDC(), _rc);
	//RectDraw(GetMemDC(), _rcWindow);
	//RectDraw(GetMemDC(), _rcPamp);
	//RectDraw(GetMemDC(), _rcEnt);
}
