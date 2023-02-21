#include "stdafx.h"
#include "gameOver.h"


gameOver::gameOver()
{
}


gameOver::~gameOver()
{
}


HRESULT gameOver::Init()
{
	//SOUNDMANAGER->AddSound("gameover", "sound/gameover.mp3", true, true);
	//SOUNDMANAGER->Play("gameover", 1.0f);
	//_blank = IMAGEMANAGER->AddImage("blank", "image/blank.bmp", 0, 0, 640, 480, false, false);
	_ending = IMAGEMANAGER->AddImage("gameover", "image/gameover.bmp", 0, 0, 640, 480, false, false);
	_alpha = 0;

	return S_OK;
}

void gameOver::Release()
{

}

void gameOver::Update()
{
	_alpha+=3;
	if (_alpha > 250) _alpha = 250;

	if (_alpha >= 250 && KEY->IsOnceKeyDown('Z'))
	{
		//SOUNDMANAGER->Stop("gameover");
		SCENEMANAGER->ChangeScene("mainMenu");
	}
}

void gameOver::Render()
{
	_ending->AlphaRender(GetMemDC(), _alpha);
}