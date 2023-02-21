#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::Init()
{
	gameNode::Init(true);

	SCENEMANAGER->AddScene("mainMenu", new mainMenu);
	SCENEMANAGER->AddScene("museumS", new museumS);
	SCENEMANAGER->AddScene("field", new Field);
	SCENEMANAGER->AddScene("opening", new opening);
	SCENEMANAGER->AddScene("museum1F_1", new museum1F_1);
	SCENEMANAGER->AddScene("museum1F_2", new museum1F_2);
	SCENEMANAGER->AddScene("museum1F_3", new museum1F_3);
	SCENEMANAGER->AddScene("museum2F_1", new museum2F_1);
	SCENEMANAGER->AddScene("museum2F_2", new museum2F_2);
	SCENEMANAGER->AddScene("museum2F_3", new museum2F_3);
	SCENEMANAGER->AddScene("blue1", new blue1);
	SCENEMANAGER->AddScene("blue2", new blue2);
	SCENEMANAGER->AddScene("blue3", new blue3);
	SCENEMANAGER->AddScene("blue4", new blue4);
	SCENEMANAGER->AddScene("green1", new green1);
	SCENEMANAGER->AddScene("green2", new green2);
	SCENEMANAGER->AddScene("green3", new green3);
	SCENEMANAGER->AddScene("ending", new ending);
	SCENEMANAGER->AddScene("gameOver", new gameOver);

	SCENEMANAGER->ChangeScene("mainMenu");

	return S_OK;
}

void gameStudy::Release()
{
	gameNode::Release();
}

void gameStudy::Update()
{
	SCENEMANAGER->Update();

	//SOUNDMANAGER->Update();

	gameNode::Update();
}

void gameStudy::Render( void )
{
	//DC를 입력한 영역만큼 단색으로 칠해준다. 
	PatBlt( GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//======================================================== 여기 사이에서 뭔갈 그리자

	SCENEMANAGER->Render();

#ifdef _DEBUG
	TIMEMANAGER->Render( GetMemDC() );
#endif // DEBUG
	
	//========================================================
	
	//백버퍼에 있는 내용을 hdc 에 그린다
	this->GetBackBuffer()->Render( GetHDC(), 0, 0);
}