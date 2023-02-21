#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

gameNode* sceneManager::_currentScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::Init()
{
	return S_OK;
}

void sceneManager::Release()
{
	//맵 전체를 돌면서 지우자
	mapSceneIter iter = _mSceneList.begin();

	for ( ; iter != _mSceneList.end(); )
	{
		//네가 가지고 있는 벨류 값이 존재 하니?
		if ( iter->second != NULL )
		{
			if ( iter->second == _currentScene ) iter->second->Release();
			SAFE_DELETE( iter->second );
			iter = _mSceneList.erase( iter );
		}
		else
		{
			++iter;
		}
	}

	_mSceneList.clear();
}

void sceneManager::Update()
{
	if ( _currentScene ) _currentScene->Update();
}

void sceneManager::Render()
{
	if ( _currentScene ) _currentScene->Render();
}

gameNode * sceneManager::AddScene( string sceneName, gameNode * scene )
{
	//넘겨받은 씬이 없으면 리턴
	if ( !scene ) return NULL;

	//_mSceneList[sceneName] = scene;
	_mSceneList.insert( make_pair( sceneName, scene ) );

	return scene;
}

void sceneManager::DeleteScene( string sceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	if ( find == _mSceneList.end() ) return;
	if ( find->second == _currentScene ) return;

	find->second->Release();
	SAFE_DELETE( find->second );
	_mSceneList.erase( find );
}

HRESULT sceneManager::ChangeScene( string sceneName )
{
	//바꾸려고 하는 씬을 찾는다.
	mapSceneIter iter = _mSceneList.find( sceneName );

	//바꾸려고 하는 씬이 존재하지 않으면...
	if ( iter == _mSceneList.end() ) return E_FAIL;

	//여기까지 왔다는 것은 있다는 거!
	if ( iter->second == _currentScene ) return S_OK;

	//새로운 씬 초기화 해주자
	if ( SUCCEEDED( iter->second->Init() ) )
	{
		//기존에 있는 씬을 정리하고 들어가자
		if ( _currentScene ) _currentScene->Release();
		_currentScene = iter->second;

		return S_OK;
	}

	return E_FAIL;
}
