#include "stdafx.h"
#include "museum2F_3.h"


museum2F_3::museum2F_3()
{
}


museum2F_3::~museum2F_3()
{
}

HRESULT museum2F_3::Init()
{
	//SOUNDMANAGER->AddSound("nuno", "sound/nuno.wav", false, false);
	_back = IMAGEMANAGER->AddImage("museum2F_3", "image/map/museum2F_3.bmp", 640, 480, false, false);
	_backPX = IMAGEMANAGER->AddImage("museum2F_3_b", "image/map/museum2F_3_b.bmp", 640, 480, false, false);
	_backRC = IMAGEMANAGER->AddImage("minorbuffer_museum2F_3_b", 640, 480);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 144, 264, 3, 4, true, RGB(32, 160, 0));
	_dialogueW = IMAGEMANAGER->AddImage("dialogueW", "image/dialogue.bmp", 620, 120, false, false);
	_liquid = IMAGEMANAGER->AddImage("liquid", "image/map/liquid.bmp", 20, 25, false, false);
	_liquidText = IMAGEMANAGER->AddImage("liquidText", "image/map/liquidText.bmp", 20, 25, false, false);
	_ibText = IMAGEMANAGER->AddFrameImage("anotherText", "image/map/anotherText.bmp", 190, 30, 6, 1, true, RGB(255, 0, 255));

	_rcLiquid = RectMake(210, 220, 20, 20);

	if (IB->GetFlags()._savePoint == true)
	{
		IB->SetNextPos(320, 250);
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}
	else
	{
		_x = IB->GetNextX();
		_y = IB->GetNextY();
	}

	_objectText = new objectText;
	_endTalk = false;

	_alpha = 255;
	
	_rc = RectMakeCenter(_x, _y, 40, 30);

	_rcAnother = RectMake(300, 220, 30, 20);

	_frameX = 0;
	_frameY = 0;

	_state = ST_IDLE;

	_anotherCheck = false;
	_anotherText = false;
	_liquidEvent = false;
	_liquidTextEvent = false;
	_endTalk = false;
	_textEvent = false;

	_frameXText = 0;
	_count = 0;
	_countLight = 0;


	_inven = new inventory;
	_inven->Init();

	return S_OK;
}

void museum2F_3::Release()
{
}

void museum2F_3::Update()
{
	Move();
	if (IB->GetFlags()._anotherCheck == true)
	{
		_alpha = 150;
	}

	RECT rcTemp;

	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(255, 0, 0))
	{
		IB->SetNextPos(600, 680);
		SCENEMANAGER->ChangeScene("museum2F_1");
	}
	if (GetPixel(_backPX->GetMemDC(), _x, _rc.top) == RGB(0, 0, 255))
	{
		IB->SetNextPos(50, 1050);
		SCENEMANAGER->ChangeScene("museum2F_2");
	}
	if (IntersectRect(&rcTemp, &_rc, &_rcAnother) && KEY->IsOnceKeyDown('Z'))
	{
		_anotherCheck = true;
		//SOUNDMANAGER->Stop("museum");
		stFlags flags = IB->GetFlags();
		flags._anotherWorld = true;
		IB->SetFlags(flags);
		//flags._savePoint = true;
		//IB->SetFlags(flags);
		//IB->SetSaveScene("museum2F_3");
		//IB->Save();
	}
	if (IntersectRect(&rcTemp, &_rc, &_rcLiquid) && KEY->IsOnceKeyDown('Z'))
	{
		if (IB->GetFlags()._anotherCheck == true && IB->GetFlags()._underWorld != true)
		{
			_liquidEvent = true;
		}
		if (IB->GetFlags()._underWorld == true)
		{
			_liquidTextEvent = true;
		}
	}

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
			_anotherCheck = false;
			if (_anotherText == false)
			{
				_anotherText = true;
				_objectText->Init();
				_objectText->SetTextNum(67);
				_state = ST_IDLE;
			}
		}
	}

	if (_liquidEvent == true)
	{
		if (_endTalk == false)
		{
			_objectText->Init();
			_objectText->SetTextNum(68);
			_endTalk = true;
		}

		if (_objectText->GetTextNum() < 69)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 68)
		{
			_state = ST_IDLE;
			_liquidEvent = false;
			_endTalk = false;

			stFlags flags = IB->GetFlags();
			flags._underWorld = true;
			IB->SetFlags(flags);
			_textEvent = true;
		}
	}

	if (_textEvent == true)
	{
		_count++;
		if (_count == 15)
		{
			_frameXText++;
			//if (_frameXText == 0) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 1) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 2) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 3) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 4) SOUNDMANAGER->Play("nuno", 1.f);
			//if (_frameXText == 5) SOUNDMANAGER->Play("nuno", 1.f);
			if (_frameXText > 5) _frameXText == 6;
		}
		if (_count > 15) _count = 0;
	}

	if (_liquidTextEvent == true)
	{
		if (_endTalk == false)
		{
			_objectText->Init();
			_objectText->SetTextNum(69);
			_endTalk = true;
		}

		if (_objectText->GetTextNum() < 70)
		{
			_objectText->Update();
			_state = ST_STOP;
		}

		if (_objectText->GetTextNum() > 69)
		{
			_endTalk = false;
			_state = ST_IDLE;
			_liquidTextEvent = false;
		}
	}

	if (IB->GetFlags()._anotherCheck != true)
	{
		if (_anotherText == true)
		{
			if (_objectText->GetTextNum() < 68)
			{
				_objectText->Update();
				_state = ST_STOP;
			}

			if (_objectText->GetTextNum() > 67)
			{
				_state = ST_IDLE;
				_anotherText = false;
			}
		}
	}

}

void museum2F_3::Render()
{
	_back->Render(_backRC->GetMemDC());
	//_backPX->Render(_backRC->GetMemDC());
	if (IB->GetFlags()._anotherWorld != true)
	{
		PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
		_back->AlphaRender(_backRC->GetMemDC(), _alpha);
		//_back->Render(_backRC->GetMemDC());
	}
	else
	{
		PatBlt(_backRC->GetMemDC(), 0, 0, _back->GetWidth(), _back->GetHeight(), BLACKNESS);
		_back->AlphaRender(_backRC->GetMemDC(), _alpha);
	}

	//RectDraw(_backRC->GetMemDC(), _rcAnother);
	//RectDraw(_backRC->GetMemDC(), _rcLiquid);

	if (IB->GetFlags()._anotherCheck == true)
	{
		_liquid->Render(_backRC->GetMemDC(), 210, 191);
	}
	if (IB->GetFlags()._underWorld == true)
	{
		_liquidText->Render(_backRC->GetMemDC(), 210, 191);
	}

	if (_frameXText >= 0 && _textEvent == true) _ibText->FrameRender(_backRC->GetMemDC(), 100, 300, 0, 1);
	if (_frameXText >= 1) _ibText->FrameRender(_backRC->GetMemDC(), 180, 250, 1, 1);
	if (_frameXText >= 2) _ibText->FrameRender(_backRC->GetMemDC(), 240, 350, 2, 1);
	if (_frameXText >= 3) _ibText->FrameRender(_backRC->GetMemDC(), 300, 300, 3, 1);
	if (_frameXText >= 4) _ibText->FrameRender(_backRC->GetMemDC(), 370, 270, 4, 1);
	if (_frameXText >= 5) _ibText->FrameRender(_backRC->GetMemDC(), 480, 350, 5, 1);

	_ibImg->FrameRender(_backRC->GetMemDC(), _rc.left - 12, _rc.bottom - _ibImg->GetFrameHeight(), _frameX, _frameY);
	_backRC->RenderTarget(GetMemDC(), _x, _y, WINSIZEX, WINSIZEY);

	if (_anotherText == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}

	if (_liquidEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}

	if (_liquidTextEvent == true)
	{
		_dialogueW->Render(GetMemDC(), 10, 350);
		_objectText->Render(GetMemDC(), 30, 370);
	}

	Menu();
}