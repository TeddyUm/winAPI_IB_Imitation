#include "stdafx.h"
#include "Field.h"


Field::Field()
{
}


Field::~Field()
{
}

HRESULT Field::Init()
{
	//SOUNDMANAGER->AddSound("itemopen", "sound/itemopen.wav", false, true);
	//SOUNDMANAGER->AddSound("itemclose", "sound/itemclose.wav", false, true);
	_ibImg = IMAGEMANAGER->AddFrameImage("ib", "image/ib.bmp", 73, 132, 3, 4, true, RGB(32, 160, 0));
	_redRose1 = IMAGEMANAGER->AddImage("redRose1", "image/red_rose01.bmp", 60, 80, false, false);
	_redRose2 = IMAGEMANAGER->AddImage("redRose2", "image/red_rose02.bmp", 60, 80, false, false);
	_redRose3 = IMAGEMANAGER->AddImage("redRose3", "image/red_rose03.bmp", 60, 80, false, false);
	_redRose4 = IMAGEMANAGER->AddImage("redRose4", "image/red_rose04.bmp", 60, 80, false, false);
	_redRose5 = IMAGEMANAGER->AddImage("redRose5", "image/red_rose05.bmp", 60, 80, false, false);

	_x = 290;
	_y = 290;

	_rc = RectMake(_x, _y, 25, 20);

	_frameX = 0;
	_frameY = 0;
	
	_lStop = false;
	_rStop = false;
	_uStop = false;
	_dStop = false;

	_alpha = 150;

	return S_OK;
}

void Field::Release()
{
}

void Field::Update()
{
	Move();
	Menu();
}

void Field::Render()
{
}

void Field::Move()
{
	if (_state == ST_IDLE)
	{

		if (KEY->IsStayKeyDown(VK_LEFT) && _lStop == false)
		{
			_lStop = false;
			_rStop = false;
			_uStop = false;
			_dStop = false;

			FrameCount();
			_frameY = 3;

			_x -= 200 * TIMEMANAGER->GetElapsedTime();

			for (int i = 0; i < 5; i++)
			{
				if (GetPixel(_backPX->GetMemDC(), _rc.left + i, _y) == RGB(255, 0, 255))
				{
					_x += i;
					_lStop = true;
					//break;
				}
			}
			if (IB->GetFlags()._anotherWorld != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.left + i, _y) == RGB(0, 255, 255))
					{
						_x += i;
						_lStop = true;
						//break;
					}
				}
			}
			if (IB->GetFlags()._underWorld != true && IB->GetFlags()._blueRose != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.left + i, _y) == RGB(255, 255, 0))
					{
						_x += i;
						_lStop = true;
						//break;
					}
				}
			}
		}

		if (KEY->IsStayKeyDown(VK_RIGHT) && _rStop == false)
		{
			_lStop = false;
			_rStop = false;
			_uStop = false;
			_dStop = false;

			FrameCount();
			_frameY = 1;

			_x += 200 * TIMEMANAGER->GetElapsedTime();

			for (int i = 0; i < 5; i++)
			{
				if (GetPixel(_backPX->GetMemDC(), _rc.right - i, _y) == RGB(255, 0, 255))
				{
					_x -= i;
					_rStop = true;
					//break;
				}
			}
			if (IB->GetFlags()._anotherWorld != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.right - i, _y) == RGB(0, 255, 255))
					{
						_x -= i;
						_rStop = true;
						//break;
					}
				}
			}
			if (IB->GetFlags()._underWorld != true && IB->GetFlags()._blueRose != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.left - i, _y) == RGB(255, 255, 0))
					{
						_x -= i;
						_rStop = true;
						//break;
					}
				}
			}
		}

		if (KEY->IsStayKeyDown(VK_UP) && _uStop == false)
		{
			_lStop = false;
			_rStop = false;
			_uStop = false;
			_dStop = false;

			FrameCount();
			_frameY = 0;

			_y -= 200 * TIMEMANAGER->GetElapsedTime();

			for (int i = 0; i < 5; i++)
			{
				if (GetPixel(_backPX->GetMemDC(), _x, _rc.top + i) == RGB(255, 0, 255))
				{
					_y += i;
					_uStop = true;
					//break;
				}
			}
			if (IB->GetFlags()._anotherWorld != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _x, _rc.top + i) == RGB(0, 255, 255))
					{
						_y += i;
						_uStop = true;
						//break;
					}
				}
			}
			if (IB->GetFlags()._underWorld != true && IB->GetFlags()._blueRose != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.left + i, _y) == RGB(255, 255, 0))
					{
						_y += i;
						_uStop = true;
						//break;
					}
				}
			}

		}

		if (KEY->IsStayKeyDown(VK_DOWN) && _dStop == false)
		{
			_lStop = false;
			_rStop = false;
			_uStop = false;
			_dStop = false;

			FrameCount();
			_frameY = 2;

			_y += 200 * TIMEMANAGER->GetElapsedTime();

			for (int i = 0; i < 5; i++)
			{
				if (GetPixel(_backPX->GetMemDC(), _x, _rc.bottom - i) == RGB(255, 0, 255))
				{
					_y -= i;
					_dStop = true;
					//break;
				}
			}
			if (IB->GetFlags()._anotherWorld != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _x, _rc.bottom - i) == RGB(0, 255, 255))
					{
						_y -= i;
						_dStop = true;
						//break;
					}
				}
			}
			if (IB->GetFlags()._underWorld != true && IB->GetFlags()._blueRose != true)
			{
				for (int i = 0; i < 5; i++)
				{
					if (GetPixel(_backPX->GetMemDC(), _rc.left + i, _y) == RGB(255, 255, 0))
					{
						_y -= i;
						_dStop = true;
						//break;
					}
				}
			}
		}

		if (KEY->IsOnceKeyUp(VK_UP) || KEY->IsOnceKeyUp(VK_DOWN) || KEY->IsOnceKeyUp(VK_LEFT) || KEY->IsOnceKeyUp(VK_RIGHT))
			_frameX = 0;
	}

	_rc = RectMakeCenter(_x, _y, 25, 20);
}

void Field::FrameCount()
{
	_count++;

	if (_count % 15 == 0)
	{
		_frameX += 1;

		if (_frameX > 2) _frameX = 0;
	}
}

void Field::Menu()
{
	if (KEY->IsOnceKeyDown('C'))
	{
		if (_state == ST_IDLE)
		{
			//SOUNDMANAGER->Play("itemopen", 1.f);
			_state = ST_MENU;
		}
		else
		{
			//SOUNDMANAGER->Play("itemclose", 1.f);
			_state = ST_IDLE;
		}
	}

	if (_state == ST_MENU) _inven->Render();
}