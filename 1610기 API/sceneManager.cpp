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
	//�� ��ü�� ���鼭 ������
	mapSceneIter iter = _mSceneList.begin();

	for ( ; iter != _mSceneList.end(); )
	{
		//�װ� ������ �ִ� ���� ���� ���� �ϴ�?
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
	//�Ѱܹ��� ���� ������ ����
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
	//�ٲٷ��� �ϴ� ���� ã�´�.
	mapSceneIter iter = _mSceneList.find( sceneName );

	//�ٲٷ��� �ϴ� ���� �������� ������...
	if ( iter == _mSceneList.end() ) return E_FAIL;

	//������� �Դٴ� ���� �ִٴ� ��!
	if ( iter->second == _currentScene ) return S_OK;

	//���ο� �� �ʱ�ȭ ������
	if ( SUCCEEDED( iter->second->Init() ) )
	{
		//������ �ִ� ���� �����ϰ� ����
		if ( _currentScene ) _currentScene->Release();
		_currentScene = iter->second;

		return S_OK;
	}

	return E_FAIL;
}
