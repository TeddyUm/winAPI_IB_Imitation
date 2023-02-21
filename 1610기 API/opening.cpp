#include "stdafx.h"
#include "opening.h"



opening::opening()
{
}


opening::~opening()
{
}

HRESULT opening::Init()
{
	//SOUNDMANAGER->AddSound("opening", "sound/opening.mp3", true, true);
	//SOUNDMANAGER->Play("opening", 1.0f);
	_openingText = new openingText;
	_openingText->Init();
	_openingText->SetTextNum(0);
	_blank = IMAGEMANAGER->AddImage("blank", "image/blank.bmp", 0, 0, 640, 480, false, false);

	return S_OK;
}

void opening::Release()
{

}

void opening::Update()
{

	if (_openingText->GetTextNum() < 5)
	{
		_openingText->Update();
	}
	if (_openingText->GetTextNum() == 5)
	{
		//SOUNDMANAGER->Stop("opening");
		SCENEMANAGER->ChangeScene("museumS");
	}
}

void opening::Render()
{
	_blank->Render(GetMemDC());
	_openingText->Render(GetMemDC(), 180, 200);
}

void opening::SceneChange()
{

}
