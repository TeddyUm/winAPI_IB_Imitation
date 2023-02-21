#include "stdafx.h"
#include "ending.h"


ending::ending()
{
}


ending::~ending()
{
}


HRESULT ending::Init()
{
	//SOUNDMANAGER->AddSound("ending", "sound/ending.mp3", true, true);
	//SOUNDMANAGER->Play("ending", 1.0f);
	_openingText = new openingText;
	_openingText->Init();
	_openingText->SetTextNum(0);
	_blank = IMAGEMANAGER->AddImage("blank", "image/blank.bmp", 0, 0, 640, 480, false, false);
	_ending = IMAGEMANAGER->AddImage("endingImage", "image/ending.bmp", 0, 0, 640, 480, false, false);
	_alpha = 0;
	_openingText->Init();
	_openingText->SetTextNum(5);

	return S_OK;
}

void ending::Release()
{

}

void ending::Update()
{
	if (_openingText->GetTextNum() < 11)
	{
		_openingText->Update();
	}

	if (_openingText->GetTextNum() > 10)
	{
		_alpha++;
		if (_alpha > 250) _alpha = 250;
	}

	if (_alpha >= 250 && KEY->IsOnceKeyDown('Z'))
	{
		//SOUNDMANAGER->Stop("ending");
		SCENEMANAGER->ChangeScene("mainMenu");
	}
}

void ending::Render()
{
	_blank->Render(GetMemDC());
	_openingText->Render(GetMemDC(), 100, 200);
	if (_openingText->GetTextNum() > 10)
	{
		_ending->AlphaRender(GetMemDC(), _alpha);
	}
}

void ending::SceneChange()
{

}
