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
	//DC�� �Է��� ������ŭ �ܻ����� ĥ���ش�. 
	PatBlt( GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//======================================================== ���� ���̿��� ���� �׸���

	SCENEMANAGER->Render();

#ifdef _DEBUG
	TIMEMANAGER->Render( GetMemDC() );
#endif // DEBUG
	
	//========================================================
	
	//����ۿ� �ִ� ������ hdc �� �׸���
	this->GetBackBuffer()->Render( GetHDC(), 0, 0);
}