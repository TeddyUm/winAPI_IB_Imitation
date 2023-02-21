#include "stdafx.h"
#include "green3.h"


green3::green3()
{
}


green3::~green3()
{
}

HRESULT green3::Init()
{
	//SOUNDMANAGER->AddSound("paper", "sound/paper.wav", false, false);

	_back = IMAGEMANAGER->AddImage("green3", "image/map/green3.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("green3_b", "image/map/green3_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_green3_b", 640, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);
	_antPicture = IMAGEMANAGER->AddFrameImage("antPicture1", "image/map/antPicture.bmp", 98, 52, 3, 1, false, false);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcAntPicture = RectMake(285, 135, 40, 60);

	_frameX = 0;
	_frameY = 0;

	_objectText = new objectText;
	_endTalk = false;
	_antPictureEvent = false;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void green3::Release()
{
}

void green3::Update()
{
	RECT _rcTemp;
	Move();
	_rcAntPictureB = RectMake(_rcAntPicture.left - 10, _rcAntPicture.top - 10 , 60, 80);

	if (IB->GetFlags()._antPictureEvent != 1 && IB->GetFlags()._antPictureEvent != 2)
	{
		if (KEY->IsStayKeyDown(VK_LEFT) && IntersectRect(&_rcTemp, &_rc, &_rcAntPicture))
		{
			_lStop = true;
			_x += 5;
		}
		if (KEY->IsStayKeyDown(VK_RIGHT) && IntersectRect(&_rcTemp, &_rc, &_rcAntPicture))
		{
			_rStop = true;
			_x -= 5;
		}
		if (KEY->IsStayKeyDown(VK_UP) && IntersectRect(&_rcTemp, &_rc, &_rcAntPicture))
		{
			_uStop = true;
			_y += 5;
		}
		if (KEY->IsStayKeyDown(VK_DOWN) && IntersectRect(&_rcTemp, &_rc, &_rcAntPicture))
		{
			_dStop = true;
			_y -= 5;
		}
	}

	if (_antPictureEvent == true)
	{
		if (_objectText->GetTextNum() < 142)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 141)
		{
			_state = ST_IDLE;
			_antPictureEvent = false;
		}
	}

	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcAntPictureB) && IB->GetFlags()._antPictureEvent == 0 && IB->GetFlags()._antPicture == true)
	{
		stFlags flags = IB->GetFlags();
		flags._antPictureEvent = 1;
		flags._antPicture = false;
		flags._useAntPicture = true;
		IB->SetFlags(flags);
		IB->DeleteInvenItem(ANTPICTURE);

		_antPictureEvent = true;
		_objectText->Init();
		_objectText->SetTextNum(141);
	}

	if (IB->GetFlags()._antPictureEvent == 1 && _rc.left > _rcAntPicture.right)
	{
		//SOUNDMANAGER->Play("paper", 1.f);
		stFlags flags = IB->GetFlags();
		flags._antPictureEvent = 2;
		IB->SetFlags(flags);
	}

	if (IB->GetFlags()._antPictureEvent == 2 && _rc.right < _rcAntPicture.left && IB->GetFlags()._blueRose == true)
	{
		//SOUNDMANAGER->Play("paper", 1.f);
		stFlags flags = IB->GetFlags();
		flags._antPictureEvent = 3;
		IB->SetFlags(flags);
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(725, 230);
		SCENEMANAGER->ChangeScene("green2");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(855, 230);
		SCENEMANAGER->ChangeScene("green2");
	}
}

void green3::Render()
{
	_back->Render(_backRC->GetMemDC());
	//RectDraw(_backRC->GetMemDC(), _rcAntPictureB);
	//RectDraw(_backRC->GetMemDC(), _rcAntPicture);
	if (IB->GetFlags()._antPictureEvent == 1)
	{
		_antPicture->FrameRender(_backRC->GetMemDC(), _rcAntPicture.left + 3, _rcAntPicture.top + 3, 0, 0);
	}
	if (IB->GetFlags()._antPictureEvent == 2)
	{
		_antPicture->FrameRender(_backRC->GetMemDC(), _rcAntPicture.left + 3, _rcAntPicture.top + 3, 1, 0);
	}
	if (IB->GetFlags()._antPictureEvent == 3)
	{
		_antPicture->FrameRender(_backRC->GetMemDC(), _rcAntPicture.left + 3, _rcAntPicture.top + 3, 2, 0);
	}
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_antPictureEvent == true)
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