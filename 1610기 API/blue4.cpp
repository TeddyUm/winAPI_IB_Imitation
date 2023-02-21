#include "stdafx.h"
#include "blue4.h"


blue4::blue4()
{
}


blue4::~blue4()
{
}

HRESULT blue4::Init()
{
	//SOUNDMANAGER->AddSound("blue", "sound/blue.mp3", true, true);
	//SOUNDMANAGER->Play("blue", 1.f);
	//SOUNDMANAGER->AddSound("key", "sound/key.wav", false, false);
	_back = IMAGEMANAGER->AddImage("blue4", "image/map/blue4.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("blue4_b", "image/map/blue4_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_blue4_b", 640, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);

	if (IB->GetFlags()._savePoint == true)
	{
		IB->SetNextPos(170, 240);
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}
	else
	{
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcSave = RectMake(120, 220, 40, 40);
	_rcDoor = RectMake(220, 195, 40, 40);
	_rcDoorB = RectMake(210, 185, 60, 60);
	_rcPicture = RectMake(420, 230, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_objectText = new objectText;
	_endTalk = false;
	_doorLockEvent = false;
	_doorOpenEvent = false;
	_doorLockText = false;
	_doorOpenText = false;
	_pictureEvent1 = false;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void blue4::Release()
{
}

void blue4::Update()
{
	RECT _rcTemp;

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture) && _endTalk == false)
	{
		_pictureEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(99);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 101)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 100)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	Move();
	if (KEY->IsStayKeyDown(VK_UP) && IntersectRect(&_rcTemp, &_rc, &_rcDoor) && IB->GetFlags()._blueDoor != true)
	{
		_uStop = true;
		_y += 5;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcDoorB) && IB->GetFlags()._blueKey != true && _doorLockText == false && _doorOpenText == false)
	{
		_objectText->Init();
		_objectText->SetTextNum(102);
		_doorLockEvent = true;
		_doorLockText = true;
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcDoorB) && IB->GetFlags()._blueKey == true && _doorOpenText == false)
	{
		_objectText->Init();
		_objectText->SetTextNum(101);
		_doorOpenEvent = true; 
		_doorOpenText = true;
	}

	if (_doorLockEvent == true)
	{
		if (_objectText->GetTextNum() < 103)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 102)
		{
			_state = ST_IDLE;
			_doorLockEvent = false;
		}
	}

	if (_doorOpenEvent == true)
	{
		if (_objectText->GetTextNum() < 102)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 101)
		{
			//SOUNDMANAGER->Play("key", 1.f);
			IB->DeleteInvenItem(BLUEKEY);
			stFlags flags = IB->GetFlags();
			flags._blueKey = false;
			flags._blueDoor = true;
			IB->SetFlags(flags);

			_state = ST_IDLE;
			_doorOpenEvent = false;
		}
	}

	if (IntersectRect(&_rcTemp, &_rc, &_rcSave) && IB->GetFlags()._savePoint != true && KEY->IsOnceKeyDown('Z'))
	{
		_saveEvent = true;
		stFlags flags = IB->GetFlags();
		flags._savePoint = true;
		IB->SetFlags(flags);
		IB->SetSaveScene("blue4");
		IB->Save();

		_objectText->Init();
		_objectText->SetTextNum(97);
	}
	if (_saveEvent == true)
	{
		if (_objectText->GetTextNum() < 99)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 98)
		{
			_state = ST_IDLE;
			_saveEvent = false;
			_endTalk = false;
		}
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		stFlags flags = IB->GetFlags();
		flags._savePoint = false;
		IB->SetFlags(flags);
		IB->SetNextPos(170, 800);
		SCENEMANAGER->ChangeScene("green1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		stFlags flags = IB->GetFlags();
		flags._savePoint = false;
		IB->SetFlags(flags);
		IB->SetNextPos(50, 300);
		SCENEMANAGER->ChangeScene("blue1");
	}
}

void blue4::Render()
{
	_back->Render(_backRC->GetMemDC());

	//RectDraw(_backRC->GetMemDC(), _rcSave);
	//RectDraw(_backRC->GetMemDC(), _rc);
	//RectDraw(_backRC->GetMemDC(), _rcDoorB);
	//RectDraw(_backRC->GetMemDC(), _rcDoor);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);
	if (_saveEvent == true || _doorOpenEvent == true || _doorLockEvent == true || _pictureEvent1 == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 20, 370);
	}

	Menu();
	if (_state == ST_IDLE)
	{
		if (IB->GetIbCurrentHp() == 5)
		{
			_redRose5->Render(GetMemDC(), 20, 30);
		}
		if (IB->GetIbCurrentHp() == 4)
		{
			_redRose4->Render(GetMemDC(), 20, 30);
		}
		if (IB->GetIbCurrentHp() == 3)
		{
			_redRose3->Render(GetMemDC(), 20, 30);
		}
		if (IB->GetIbCurrentHp() == 2)
		{
			_redRose2->Render(GetMemDC(), 20, 30);
		}
		if (IB->GetIbCurrentHp() == 1)
		{
			_redRose1->Render(GetMemDC(), 20, 30);
		}
	}
}