#pragma once

#include <map>
#include <string>
#include "singletonBase.h"

//전방선언
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

	//씬 추가
	gameNode* AddScene( string sceneName, gameNode* scene );

	//씬 삭제
	void DeleteScene( string sceneName );


	//씬 체인지
	HRESULT ChangeScene( string sceneName );
};


