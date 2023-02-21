#include "stdafx.h"
#include "green1.h"


green1::green1()
{
}


green1::~green1()
{
}

HRESULT green1::Init()
{
	//SOUNDMANAGER->AddSound("monster", "sound/monster.wav", false, false);
	//SOUNDMANAGER->AddSound("itemget", "sound/item_get.wav", false, false);
	//SOUNDMANAGER->AddSound("hit", "sound/hit.wav", false, false);

	_back = IMAGEMANAGER->AddImage("green1", "image/map/green1.bmp", 640, 930, false, false);
	_backPX = IMAGEMANAGER->AddImage("green1_b", "image/map/green1_b.bmp", 640, 930, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_green1_b", 640, 930);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);
	_antPicture = IMAGEMANAGER->AddFrameImage("antPicture1", "image/map/antPicture.bmp", 98, 52, 3, 1, false, false);
	_hand1 = IMAGEMANAGER->AddFrameImage("hand1", "image/map/hand1.bmp", 146, 58, 3, 1, true, RGB(32, 156, 0));
	_hand2 = IMAGEMANAGER->AddFrameImage("hand2", "image/map/hand2.bmp", 146, 58, 3, 1, true, RGB(32, 156, 0));

	_rcAnt = RectMake(415, 715, 30, 30);
	_rcAntPicture = RectMake(250, 150, 30, 30);
	_rcBanner = RectMake(122, 670, 30, 30);
	_rcHand1 = RectMake(155, 500, 45, 30);
	_rcHand2 = RectMake(75, 350, 45, 30);
	_rcPicture = RectMake(120, 670, 40, 30);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_currentFrame = 0;
	_countHand = 0;
	_objectText = new objectText;
	_endTalk = false;
	_antEvent = false;
	_antPictureEvent = false;
	_hand1Event = false;
	_hand2Event = false;
	_bannerEvent = false;
	_pictureEvent1 = false;
	_sound = 0;
	_sound2 = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void green1::Release()
{
}

void green1::Update()
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
		_objectText->SetTextNum(113);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 114)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 113)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	Move();
	if (IB->GetIbCurrentHp() < 1)
	{
		//SOUNDMANAGER->Stop("blue");
		SCENEMANAGER->ChangeScene("gameOver");
	}

	if (_hand1Event == true)
	{
		_sound++;
		//if (_sound == 1) SOUNDMANAGER->Play("monster", 1.f);
		if (_sound > 2) _sound = 2;
	}
	if (_hand2Event == true)
	{
		_sound2++;
		//if (_sound2 == 1) SOUNDMANAGER->Play("monster", 1.f);
		if (_sound2 > 2) _sound2 = 2;
	}

	if (_y < 550)
	{
		_hand1Event = true;
	}
	if (_y < 400)
	{
		_hand2Event = true;
	}

	if (_hand1Event == true)
	{
		_countHand++;
		if (_countHand == 10) _currentFrame++;
		if (_countHand == 20) _currentFrame++;
		if (_countHand == 30) _currentFrame++;
		if (_currentFrame > 2)
		{
			_countHand = 0;
			_currentFrame = 0;
		}
	}

	if (_hand1Event == true && IntersectRect(&_rcTemp, &_rc, &_rcHand1))
	{
		//SOUNDMANAGER->Play("hit", 1.f);
		_x -= 45; 
		IB->SetIbCurrentHp(IB->GetIbCurrentHp() - 1);
	}
	if (_hand2Event == true && IntersectRect(&_rcTemp, &_rc, &_rcHand2))
	{
		//SOUNDMANAGER->Play("hit", 1.f);
		_x += 45;
		IB->SetIbCurrentHp(IB->GetIbCurrentHp() - 1);
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcBanner) && _endTalk == false)
	{
		_objectText->Init();
		_bannerEvent = true;
		_endTalk = true;
		_objectText->SetTextNum(113);
	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcAnt) && _endTalk == false)
	{
		_objectText->Init();
		_antEvent = true;
		_endTalk = true;
		if (IB->GetFlags()._antPicture != true && IB->GetFlags()._useAntPicture != true) _objectText->SetTextNum(109);
		if (IB->GetFlags()._antPicture == true && IB->GetFlags()._useAntPicture != true) _objectText->SetTextNum(118);
		if (IB->GetFlags()._antPicture != true && IB->GetFlags()._useAntPicture == true) _objectText->SetTextNum(121);

	}
	if (KEY->IsStayKeyDown('Z') && IntersectRect(&_rcTemp, &_rc, &_rcAntPicture) && _endTalk == false && IB->GetFlags()._antPicture != true)
	{
		_objectText->Init();
		_objectText->SetTextNum(114);
		_antPictureEvent = true;
		_endTalk = true;
	}

	if (_bannerEvent == true)
	{
		if (_objectText->GetTextNum() < 114)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 113)
		{
			_state = ST_IDLE;
			_bannerEvent = false;
		}
	}
	if (_antEvent == true && IB->GetFlags()._antPicture != true && IB->GetFlags()._useAntPicture != true)
	{
		if (_objectText->GetTextNum() < 113)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 112)
		{
			_state = ST_IDLE;
			_antEvent = false;
		}
	}
	if (_antEvent == true && IB->GetFlags()._antPicture == true && IB->GetFlags()._useAntPicture != true)
	{
		if (_objectText->GetTextNum() < 121)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 120)
		{
			_state = ST_IDLE;
			_antEvent = false;
		}
	}
	if (_antEvent == true && IB->GetFlags()._antPicture != true && IB->GetFlags()._useAntPicture == true)
	{
		if (_objectText->GetTextNum() < 122)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 121)
		{
			_state = ST_IDLE;
			_antEvent = false;
		}
	}
	if (_antPictureEvent == true)
	{
		if (_objectText->GetTextNum() < 118)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 117)
		{
			//SOUNDMANAGER->Play("itemget", 1.f);
			stFlags flags = IB->GetFlags();
			flags._antPicture = true;
			IB->SetFlags(flags);
			IB->AddInvenItem(ANTPICTURE);
			_state = ST_IDLE;
			_antPictureEvent = false;
		}
	}

	if (KEY->IsStayKeyDown(VK_RIGHT) || KEY->IsStayKeyDown(VK_LEFT) || KEY->IsStayKeyDown(VK_UP) || KEY->IsStayKeyDown(VK_DOWN))
	{
		if (!IntersectRect(&_rcTemp, &_rc, &_rcAnt) && !IntersectRect(&_rcTemp, &_rc, &_rcAntPicture) && !IntersectRect(&_rcTemp, &_rc, &_rcBanner)) _endTalk = false;
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(50, 250);
		SCENEMANAGER->ChangeScene("green2");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 255, 0))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(240, 290);
		SCENEMANAGER->ChangeScene("blue4");
	}
}

void green1::Render()
{
	_back->Render(_backRC->GetMemDC());

	if (IB->GetFlags()._antPicture != true)	_antPicture->FrameRender(_backRC->GetMemDC(), 250, 100, 0, 0);
	//RectDraw(_backRC->GetMemDC(), _rcAnt);
	//RectDraw(_backRC->GetMemDC(), _rcAntPicture);
	//RectDraw(_backRC->GetMemDC(), _rcBanner);
	//RectDraw(_backRC->GetMemDC(), _rcHand1);
	//RectDraw(_backRC->GetMemDC(), _rcHand2);
	//RectDraw(_backRC->GetMemDC(), _rc);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	if (_hand1Event == true) _hand1->FrameRender(_backRC->GetMemDC(), _rcHand1.left, _rcHand1.bottom - _hand1->GetFrameHeight(), _currentFrame, 0);
	if (_hand2Event == true) _hand2->FrameRender(_backRC->GetMemDC(), _rcHand2.left, _rcHand2.bottom - _hand2->GetFrameHeight(), _currentFrame, 0);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_antEvent == true || _antPictureEvent == true || _bannerEvent == true || _pictureEvent1 == true)
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