#include "stdafx.h"
#include "blue3.h"


blue3::blue3()
{
}


blue3::~blue3()
{
}

HRESULT blue3::Init()
{
	//SOUNDMANAGER->AddSound("itemget", "sound/item_get.wav", false, false);

	_back = IMAGEMANAGER->AddImage("blue3", "image/map/blue3.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("blue3_b", "image/map/blue3_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_blue3_b", 640, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_smileFace = IMAGEMANAGER->AddFrameImage("smileFace", "image/map/smileFace.bmp", 280, 112, 3, 1, true, RGB(255, 0, 255));
	_blueKey = IMAGEMANAGER->AddImage("blueKey2", "image/map/blueKey.bmp", 32, 28, true, RGB(255, 0, 255));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);

	_x = IB->GetNextX();
	_y = IB->GetNextY();

	_rc = RectMakeCenter(_x, _y, 40, 30);
	_rcKey = RectMake(320, 270, 30, 30);
	_rcPicture = RectMake(325, 220, 40, 30);

	_frameX = 0;
	_frameY = 0;

	_objectText = new objectText;
	_endTalk = false;
	_faceEvent = false;
	_pictureEvent1 = false;
	_countFace = 0;
	_currentFrame = 0;

	_state = ST_IDLE;

	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void blue3::Release()
{
}

void blue3::Update()
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
		_objectText->SetTextNum(91);
	}

	if (_pictureEvent1 == true)
	{
		if (_objectText->GetTextNum() < 93)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 92)
		{
			_state = ST_IDLE;
			_pictureEvent1 = false;
		}
	}

	Move();

	if (IB->GetFlags()._blueKey == true)
	{
		if (_countFace < 30) _countFace++;

		if (_countFace == 10) _currentFrame = 1;
		else if (_countFace > 20) _currentFrame = 2;
	}

	if (IntersectRect(&_rcTemp, &_rc, &_rcKey)&& IB->GetFlags()._blueKey != true && KEY->IsOnceKeyDown('Z'))
	{
		//SOUNDMANAGER->Play("itemget", 1.f);
		_blueKeyEvent = true;
		stFlags flags = IB->GetFlags();
		flags._blueKey = true;
		IB->SetFlags(flags);
		IB->AddInvenItem(BLUEKEY);

		_objectText->Init();
		_objectText->SetTextNum(93);
	}

	if (_blueKeyEvent == true)
	{
		if (_objectText->GetTextNum() < 95)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 94)
		{
			_state = ST_IDLE;
			_blueKeyEvent = false;
			_endTalk = false;
		}
	}

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		//SOUNDMANAGER->Play("door", 1.f);
		IB->SetNextPos(770, 250);
		SCENEMANAGER->ChangeScene("blue2");
	}
}

void blue3::Render()
{
	_back->Render(_backRC->GetMemDC());
	
	_smileFace->FrameRender(_backRC->GetMemDC(), 290, 95, _currentFrame, 0);
	if (IB->GetFlags()._blueKey != true) _blueKey->Render(_backRC->GetMemDC(), _rcKey.left, _rcKey.top);
	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);
	if (_blueKeyEvent == true || _pictureEvent1 == true)
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