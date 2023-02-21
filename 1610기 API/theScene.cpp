#include "stdafx.h"
#include "theScene.h"


theScene::theScene()
{
}


theScene::~theScene()
{
}

HRESULT theScene::Init()
{
	IMAGEMANAGER->AddImage("title", "image/title.bmp", 640, 480, false, false);
	SOUNDMANAGER->AddSound("music", "sound/muppet.mp3", false, false);

	_freq = 44100.0f;

	SOUNDMANAGER->Play("music", 0.5f);

	return S_OK;
}

void theScene::Release()
{
}

void theScene::Update()
{
	if (KEY->IsOnceKeyDown(VK_UP))
	{
		_freq = SOUNDMANAGER->GetFrequency("music") + 100.f;
		SOUNDMANAGER->SetFrequency("music", _freq);
	}

	if (KEY->IsOnceKeyDown(VK_DOWN))
	{
		_freq = SOUNDMANAGER->GetFrequency("music") - 100.f;
		SOUNDMANAGER->SetFrequency("music", _freq);
	}
}

void theScene::Render()
{
	IMAGEMANAGER->Render("title", GetMemDC());
}
