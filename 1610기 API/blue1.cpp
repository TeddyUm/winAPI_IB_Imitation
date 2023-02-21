#include "stdafx.h"
#include "blue1.h"


blue1::blue1()
{
}


blue1::~blue1()
{
}

HRESULT blue1::Init()
{
	//SOUNDMANAGER->AddSound("blue", "sound/blue.mp3", true, true);
	//SOUNDMANAGER->AddSound("garry", "sound/garry.mp3", true, true);
	if (IB->GetFlags()._underWorld == true)
	{
		//SOUNDMANAGER->Play("blue", 1.f);
	}

	_back = IMAGEMANAGER->AddImage("blue1", "image/map/blue1.bmp", 640, 480, false, false);
	_back2 = IMAGEMANAGER->AddImage("blue1_2", "image/map/blue1_2.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("blue1_b", "image/map/blue1_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_blue1_b", 640, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_garryImg = IMAGEMANAGER->AddFrameImage("garry", "image/character/garry.bmp", 192, 264, 4, 4, true, RGB(2, 156, 0));
	_dialogue = IMAGEMANAGER->AddImage("dialogue", "image/dialogue.bmp", 480, 120, false, false);
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_garryP1 = IMAGEMANAGER->AddImage("garryP1", "image/portrait/garryP1.bmp", 120, 115, false, false);
	_garryP2 = IMAGEMANAGER->AddImage("garryP2", "image/portrait/garryP2.bmp", 120, 115, false, false);
	_garryP3 = IMAGEMANAGER->AddImage("garryP3", "image/portrait/garryP3.bmp", 120, 115, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);

	_rcGarry = RectMake(200, 230, 30, 30);
	_rcGarryB = RectMake(_rcGarry.left+5, _rcGarry.top + 5, 20, 20);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_objectText = new objectText;
	_endTalk = false;
	_move = true;
	_garryTalk = false;
	_endTalk = false;
	_endingEvent = false;
	_GarryMove = false;

	_framecount = 0;
	_frameXGarry = 0;
	_frameYGarry = 0;
	_garryDirection = GARRY_SIT;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void blue1::Release()
{
}

void blue1::Update()
{
	RECT rcTemp;
	Move();
	GarryMove();

	if (IntersectRect(&rcTemp, &_rc, &_rcGarry) && KEY->IsOnceKeyDown('Z') && _endTalk == false)
	{
		if (IB->GetFlags()._blueRose != true)
		{
			_objectText->Init();
			_objectText->SetTextNum(74);
			_garryTalk = true;
			_endTalk = true;
		}
		else
		{
			//SOUNDMANAGER->Stop("blue");
			//SOUNDMANAGER->Play("garry", 1.f);
			_objectText->Init();
			_objectText->SetTextNum(76);
			_endingEvent = true;
			_endTalk = true;
			_garryDirection = GARRY_STAND;
		}
	}

	if (_garryTalk == true)
	{
		if (_objectText->GetTextNum() < 76)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 75)
		{
			_state = ST_IDLE;
			_garryTalk = false;
			_endTalk = false;
		}
	}
	if (_endingEvent == true)
	{
		if (_objectText->GetTextNum() < 83)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 82)
		{
			_state = ST_IDLE;
			_endingEvent = false;
			_endTalk = false;
			_GarryMove = true;
		}
	}

	if (_GarryMove == true)
	{
		_state = ST_STOP;
		if (_rcGarry.left < 300)
		{
			_garryDirection = GARRY_RIGHT;
			_rcGarry.left += 100 * TIMEMANAGER->GetElapsedTime();
			_rcGarry.right += 100 * TIMEMANAGER->GetElapsedTime();
		}
		if (_rcGarry.left >= 300 && _rcGarry.top > 70)
		{
			_garryDirection = GARRY_UP;
			_rcGarry.top -= 100 * TIMEMANAGER->GetElapsedTime();
			_rcGarry.bottom -= 100 * TIMEMANAGER->GetElapsedTime();
		}
		if (_rc.left < 300)
		{
			FrameCount();
			_frameY = 1;
			_x += 100 * TIMEMANAGER->GetElapsedTime();
		}
		if (_rc.left >= 300 && _rc.top > 100)
		{
			FrameCount();
			_frameY = 0;
			_y -= 100 * TIMEMANAGER->GetElapsedTime();
		}
		if (_rcGarry.top <= 70)
		{
			//SOUNDMANAGER->Stop("garry");
			SCENEMANAGER->ChangeScene("ending");
		}
	}
	if (KEY->IsStayKeyDown(VK_LEFT) && IntersectRect(&rcTemp, &_rc, &_rcGarryB))
	{
		_lStop = true;
		_x += 5;
	}
	if (KEY->IsStayKeyDown(VK_RIGHT) && IntersectRect(&rcTemp, &_rc, &_rcGarryB))
	{
		_rStop = true;
		_x -= 5;
	}
	if (KEY->IsStayKeyDown(VK_UP) && IntersectRect(&rcTemp, &_rc, &_rcGarryB))
	{
		_uStop = true;
		_y += 5;
	}
	if (KEY->IsStayKeyDown(VK_DOWN) && IntersectRect(&rcTemp, &_rc, &_rcGarryB))
	{
		_dStop = true;
		_y -= 5;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		stFlags flags = IB->GetFlags();
		flags._underWorld = false;
		IB->SetFlags(flags);
		IB->SetNextPos(590, 300);
		SCENEMANAGER->ChangeScene("blue4");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		stFlags flags = IB->GetFlags();
		flags._underWorld = false;
		IB->SetFlags(flags);
		IB->SetNextPos(50, 300);
		SCENEMANAGER->ChangeScene("blue2");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(200, 200, 0))
	{
		IB->SetNextPos(325, 400);
		stFlags flags = IB->GetFlags();
		flags._anotherWorld = true;
		IB->SetFlags(flags);
		SCENEMANAGER->ChangeScene("museum1F_1");
	}
}

void blue1::Render()
{
	if (IB->GetFlags()._underWorld == true)
	{
		_back->Render(_backRC->GetMemDC());
	}
	if (IB->GetFlags()._underWorld == false)
	{
		_back2->Render(_backRC->GetMemDC());
	}
	if (IB->GetFlags()._blueRose == true)
	{
		_back->Render(_backRC->GetMemDC());
	}
	//RectDraw(_backRC->GetMemDC(), _rcGarry);
	//RectDraw(_backRC->GetMemDC(), _rcGarryB);
	//RectDraw(_backRC->GetMemDC(), _rc);

	_garryImg->FrameRender(_backRC->GetMemDC(), _rcGarry.left - 6, _rcGarry.bottom - _garryImg->GetFrameHeight(), _frameXGarry, _frameYGarry);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_garryTalk == true)
	{
		_garryP3->Render(GetMemDC(), 20, 350);
		_dialogue->Render(GetMemDC(), 150, 350);
		_objectText->Render(GetMemDC(), 170, 370);
	}
	if (_endingEvent == true)
	{
		_garryP1->Render(GetMemDC(), 20, 350);
		_dialogue->Render(GetMemDC(), 150, 350);
		_objectText->Render(GetMemDC(), 170, 370);
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

void blue1::GarryMove()
{
	switch (_garryDirection)
	{
	case GARRY_DOWN:
		_frameYGarry = 2;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXGarry++;
			if (_frameXGarry > 2) _frameXGarry = 0;
		}
		break;
	case GARRY_UP:
		_frameYGarry = 0;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXGarry++;
			if (_frameXGarry > 2) _frameXGarry = 0;
		}
		break;
	case GARRY_LEFT:
		_frameYGarry = 3;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXGarry++;
			if (_frameXGarry > 2) _frameXGarry = 0;
		}
		break;
	case GARRY_RIGHT:
		_frameYGarry = 1;
		_framecount++;
		if (_framecount % 12 == 0)
		{
			_frameXGarry++;
			if (_frameXGarry > 2) _frameXGarry = 0;
		}
		break;
	case GARRY_SIT:
		_frameYGarry = 0;
		_frameXGarry = 3;
		break;
	case GARRY_STAND:
		_frameYGarry = 1;
		_frameXGarry = 3;
		break;
	}
}