#include "stdafx.h"
#include "blue2.h"


blue2::blue2()
{
}


blue2::~blue2()
{
}

HRESULT blue2::Init()
{
	//SOUNDMANAGER->AddSound("door", "sound/doa_akanai.wav", false, false);
	//SOUNDMANAGER->AddSound("itemget", "sound/item_get.wav", false, false);
	_back = IMAGEMANAGER->AddImage("blue2", "image/map/blue2.bmp", 950, 480, false, false);
	_back2 = IMAGEMANAGER->AddImage("blue2_2", "image/map/blue2_2.bmp", 950, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("blue2_b", "image/map/blue2_b.bmp", 950, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_blue2_b", 950, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_bottle = IMAGEMANAGER->AddFrameImage("bottle", "image/map/bottle.bmp", 64, 60, 2, 1, true, RGB(32, 156, 0));
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);
	_ibText = IMAGEMANAGER->AddFrameImage("ibText", "image/map/ibText.bmp", 104, 40, 3, 1, true, RGB(255, 0, 255));

	if (IB->GetFlags()._redRose != true) _rcBottle = RectMake(760, 225, 32, 30);
	else _rcBottle = RectMake(820, 225, 32, 30);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcText = RectMake(200, 150, 200, 200);

	_frameX = 0;
	_frameY = 0;
	_frameXText = 0;
	_count = 0;

	_objectText = new objectText;
	_endTalk = false;
	_move = true;
	_bottleMove = false;
	_textEvent = false;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void blue2::Release()
{
}

void blue2::Update()
{
	RECT _rcTemp;
	_rcBottleB = RectMake(_rcBottle.left - 6, _rcBottle.top - 5, 45, 40);
	if (_move == true) Move();

	if (KEY->IsStayKeyDown(VK_LEFT) && IntersectRect(&_rcTemp, &_rc, &_rcBottle))
	{
		_lStop = true;
		_x += 5;
	}
	if (KEY->IsStayKeyDown(VK_RIGHT) && IntersectRect(&_rcTemp, &_rc, &_rcBottle))
	{
		_rStop = true;
		_x -= 5;
	}
	if (KEY->IsStayKeyDown(VK_UP) && IntersectRect(&_rcTemp, &_rc, &_rcBottle))
	{
		_uStop = true;
		_y += 5;
	}
	if (KEY->IsStayKeyDown(VK_DOWN) && IntersectRect(&_rcTemp, &_rc, &_rcBottle))
	{
		_dStop = true;
		_y -= 5;
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcBottleB))
	{
		if (IB->GetFlags()._redRose != true)
		{
			//SOUNDMANAGER->Play("itemget", 1.f);
			_objectText->Init();
			_objectText->SetTextNum(84);
			stFlags flags = IB->GetFlags();
			flags._redRose = true;
			IB->SetFlags(flags);
			IB->AddInvenItem(REDROSE);
			IB->SetIbCurrentHp(3);
			_redRoseEvent = true;
		}
		if (_redRoseEvent == false)
		{
			_bottleMove = true;
		}
	}
	if (_bottleMove == true)
	{
		if (_rcBottle.left < 820)
		{
			_rcBottle.left += 100 * TIMEMANAGER->GetElapsedTime();
			_rcBottle.right += 100 * TIMEMANAGER->GetElapsedTime();
		}
		else _bottleMove = false;
	}
	if (_redRoseEvent == true)
	{
		if (_objectText->GetTextNum() < 87)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 86)
		{
			_state = ST_IDLE;
			_redRoseEvent = false;
			_endTalk = false;
		}
	}

	if (IB->GetFlags()._blueKey == true && IntersectRect(&_rcTemp, &_rc, &_rcText))
	{
		_count++;
		if (_count == 15)
		{
			_frameXText++;
			//if (_frameXText == 0) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 1) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 2) SOUNDMANAGER->Play("nuno", 1.f);
			if (_frameXText > 2) _frameXText == 3;
		}
		if (_count > 15) _count = 0;
		_textEvent = true;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(590, 300);
		SCENEMANAGER->ChangeScene("blue1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(340, 330);
		SCENEMANAGER->ChangeScene("blue3");
	}
}

void blue2::Render()
{
	if (IB->GetFlags()._blueKey != true)
	{
		_back->Render(_backRC->GetMemDC());
	}
	else
	{
		_back2->Render(_backRC->GetMemDC());
	}

	//RectDraw(_backRC->GetMemDC(), _rcBottle);
	//RectDraw(_backRC->GetMemDC(), _rcBottleB);
	//RectDraw(_backRC->GetMemDC(), _rc);
	//RectDraw(_backRC->GetMemDC(), _rcText);

	if (IB->GetFlags()._redRose != true) _bottle->FrameRender(_backRC->GetMemDC(), _rcBottle.left, _rcBottle.bottom - _bottle->GetFrameHeight(), 0, 0);
	else _bottle->FrameRender(_backRC->GetMemDC(), _rcBottle.left, _rcBottle.bottom - _bottle->GetFrameHeight(), 1, 0);

	if (_frameXText >= 0 && _textEvent == true) _ibText->FrameRender(_backRC->GetMemDC(), 180, 230, 0, 1);
	if (_frameXText >= 1) _ibText->FrameRender(_backRC->GetMemDC(), 200, 260, 1, 1);
	if (_frameXText >= 2) _ibText->FrameRender(_backRC->GetMemDC(), 220, 290, 2, 1);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_redRoseEvent == true)
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