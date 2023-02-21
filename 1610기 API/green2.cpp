#include "stdafx.h"
#include "green2.h"


green2::green2()
{
}


green2::~green2()
{
}

HRESULT green2::Init()
{
	//SOUNDMANAGER->AddSound("monster", "sound/monster.wav", false, false);
	//SOUNDMANAGER->AddSound("itemget", "sound/item_get.wav", false, false);

	_back = IMAGEMANAGER->AddImage("green2", "image/map/green2.bmp", 1380, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("green2_b", "image/map/green2_b.bmp", 1380, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_green2_b", 1380, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);
	_blueRose = IMAGEMANAGER->AddImage("blueRose1", "image/map/blue_rose.bmp", 25, 25, true, RGB(255, 255, 255));
	_redDoll = IMAGEMANAGER->AddFrameImage("redDoll", "image/character/redDoll.bmp", 144, 264, 3, 4, true, RGB(32, 156, 0));

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcBlueRose = RectMake(1100, 250, 30, 30);
	_rcRedDoll = RectMake(1200, 250, 40, 30);
	_rcPicture1	= RectMake(65, 200, 40, 30);
	_rcPicture2	= RectMake(195, 200, 40, 30);
	_rcPicture3	= RectMake(325, 200, 40, 30);
	_rcPicture4	= RectMake(455, 200, 40, 30);
	_rcPicture5	= RectMake(580, 200, 40, 30);
	_rcPicture6	= RectMake(1155, 200, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_framecount = 0;
	_frameXDoll = 0;
	_frameYDoll = 3;

	_objectText = new objectText;
	_dollDirection = DOLL_UP;
	_endTalk = false;
	_pictureEvent1 = false;
	_pictureEvent2 = false;
	_pictureEvent3 = false;
	_pictureEvent4 = false;
	_pictureEvent5 = false;
	_pictureEvent6 = false;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void green2::Release()
{
}

void green2::Update()
{
	RECT _rcTemp;

	if (_state == ST_IDLE && KEY->IsOnceKeyDown(VK_DOWN) || KEY->IsOnceKeyDown(VK_UP) || KEY->IsOnceKeyDown(VK_LEFT) || KEY->IsOnceKeyDown(VK_RIGHT))
	{
		_endTalk = false;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture1) && _endTalk == false)
	{
		_pictureEvent1 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(126);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 127)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 126)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture2) && _endTalk == false)
	{
		_pictureEvent2 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(127);
	}

	if (_pictureEvent2 == true)
	{
		if (_objectText->GetTextNum() < 128)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 127)
		{
			_state = ST_IDLE;
			_pictureEvent2 = false;
		}
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture3) && _endTalk == false)
	{
		_pictureEvent3 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(128);
	}

	if (_pictureEvent3 == true)
	{
		if (_objectText->GetTextNum() < 129)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 128)
		{
			_state = ST_IDLE;
			_pictureEvent3 = false;
		}
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture4) && _endTalk == false)
	{
		_pictureEvent4 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(135);
	}

	if (_pictureEvent4 == true)
	{
		if (_objectText->GetTextNum() < 136)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 135)
		{
			_state = ST_IDLE;
			_pictureEvent4 = false;
		}
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture5) && _endTalk == false)
	{
		_pictureEvent5 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(129);
	}

	if (_pictureEvent5 == true)
	{
		if (_objectText->GetTextNum() < 130)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 129)
		{
			_state = ST_IDLE;
			_pictureEvent5 = false;
		}
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcPicture6) && _endTalk == false)
	{
		_pictureEvent6 = true;
		_endTalk = true;
		_objectText->Init();
		_objectText->SetTextNum(130);
	}

	if (_pictureEvent6 == true)
	{
		if (_objectText->GetTextNum() < 131)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 130)
		{
			_state = ST_IDLE;
			_pictureEvent6 = false;
		}
	}

	Move();
	if (IB->GetIbCurrentHp() < 1)
	{
		//SOUNDMANAGER->Stop("blue");
		SCENEMANAGER->ChangeScene("gameOver");
	}

	if (_dollMove == true) DollMove();

	if (KEY->IsStayKeyDown(VK_LEFT) && IntersectRect(&_rcTemp, &_rc, &_rcRedDoll))
	{
		_lStop = true;
		_x += 5;
	}
	if (KEY->IsStayKeyDown(VK_RIGHT) && IntersectRect(&_rcTemp, &_rc, &_rcRedDoll))
	{
		_rStop = true;
		_x -= 5;
	}
	if (KEY->IsStayKeyDown(VK_UP) && IntersectRect(&_rcTemp, &_rc, &_rcRedDoll))
	{
		_uStop = true;
		_y += 5;
	}
	if (KEY->IsStayKeyDown(VK_DOWN) && IntersectRect(&_rcTemp, &_rc, &_rcRedDoll))
	{
		_dStop = true;
		_y -= 5;
	}

	if (_dollMove == true && _rcRedDoll.left > 830)
	{
		_dollDirection = DOLL_LEFT;
		_rcRedDoll.left -= 50 * TIMEMANAGER->GetElapsedTime();
		_rcRedDoll.right -= 50 * TIMEMANAGER->GetElapsedTime();
	}
	if (_dollMove == true && _rcRedDoll.left <= 830)
	{
		_dollDirection = DOLL_UP;
		_rcRedDoll.top -= 50 * TIMEMANAGER->GetElapsedTime();
		_rcRedDoll.bottom -= 50 * TIMEMANAGER->GetElapsedTime();
	}
	if (_dollMove == true && _rcRedDoll.top < 200)
	{
		_dollMove = false;
	}

	if (_dollMove == true && IntersectRect(&_rcTemp, &_rc, &_rcRedDoll))
	{
		//SOUNDMANAGER->Play("hit", 1.f);
		_x -= 30;
		IB->SetIbCurrentHp(IB->GetIbCurrentHp() - 1);
	}


	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcBlueRose) && IB->GetFlags()._blueRose != true)
	{
		//SOUNDMANAGER->Play("itemget", 1.f);
		stFlags flags = IB->GetFlags();
		flags._blueRose = true;
		IB->SetFlags(flags);
		IB->AddInvenItem(BLUEROSE);

		_blueRoseEvent = true;
		_objectText->Init();
		_objectText->SetTextNum(133);
	}

	if (_blueRoseEvent == true)
	{
		if (_objectText->GetTextNum() < 135)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 134)
		{
			_state = ST_IDLE;
			_blueRoseEvent = false;
			_dollMove = true;
			//SOUNDMANAGER->Play("monster", 1.0f);
		}
	}


	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(530, 730);
		SCENEMANAGER->ChangeScene("green1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(170, 170);
		SCENEMANAGER->ChangeScene("green3");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 255, 0))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(435, 170);
		SCENEMANAGER->ChangeScene("green3");
	}
}

void green2::Render()
{
	_back->Render(_backRC->GetMemDC());

	//RectDraw(_backRC->GetMemDC(), _rcBlueRose);
	//RectDraw(_backRC->GetMemDC(), _rcRedDoll);
	if (IB->GetFlags()._blueRose != true)
	{
		_blueRose->Render(_backRC->GetMemDC(), _rcBlueRose.left, _rcBlueRose.top);
	}
	_redDoll->FrameRender(_backRC->GetMemDC(), _rcRedDoll.left, _rcRedDoll.bottom - _redDoll->GetFrameHeight(), _frameXDoll, _frameYDoll);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_blueRoseEvent == true || _pictureEvent1 == true || _pictureEvent2 == true || 
		_pictureEvent3 == true || _pictureEvent4 == true || _pictureEvent5 == true || _pictureEvent6 == true)
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

void green2::DollMove()
{
	switch (_dollDirection)
	{
	case DOLL_DOWN:
		_frameYDoll = 2;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXDoll++;
			if (_frameXDoll > 3) _frameXDoll = 0;
		}
		break;
	case DOLL_UP:
		_frameYDoll = 0;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXDoll++;
			if (_frameXDoll > 3) _frameXDoll = 0;
		}
		break;
	case DOLL_LEFT:
		_frameYDoll = 3;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXDoll++;
			if (_frameXDoll > 3) _frameXDoll = 0;
		}
		break;
	case DOLL_RIGHT:
		_frameYDoll = 1;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXDoll++;
			if (_frameXDoll > 3) _frameXDoll = 0;
		}
		break;
	}
}