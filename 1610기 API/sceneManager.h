#pragma once

#include <map>
#include <string>
#include "singletonBase.h"

//���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public :
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//�� �߰�
	gameNode* AddScene( string sceneName, gameNode* scene );

	//�� ����
	void DeleteScene( string sceneName );


	//�� ü����
	HRESULT ChangeScene( string sceneName );
};


