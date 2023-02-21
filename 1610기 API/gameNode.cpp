#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::Init()
{
	_hdc = GetDC( _hWnd );
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::Init( bool managerInit )
{
	_hdc = GetDC( _hWnd );
	_managerInit = managerInit;

	if ( _managerInit )
	{
		//SetTimer( _hWnd, 1, 10, NULL );

		KEY->Init();
		IMAGEMANAGER->Init();
		TIMEMANAGER->Init();
		TXTDATA->Init();
		SCENEMANAGER->Init();
		DATABASE->Init();
		EFFECTMANAGER->Init();
		//SOUNDMANAGER->Init();
	}

	return S_OK;
}

void gameNode::Release()
{
	if ( _managerInit )
	{
		KillTimer( _hWnd, 1 );

		//싱글톤 해제
		KEY->Release();
		KEY->ReleaseSingleton();
		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();
		TIMEMANAGER->Release();
		TIMEMANAGER->ReleaseSingleton();
		TXTDATA->Release();
		TXTDATA->ReleaseSingleton();
		SCENEMANAGER->Release();
		SCENEMANAGER->ReleaseSingleton();
		DATABASE->Release();
		DATABASE->ReleaseSingleton();
		EFFECTMANAGER->Release();
		EFFECTMANAGER->ReleaseSingleton();
		//SOUNDMANAGER->Release();
		//SOUNDMANAGER->ReleaseSingleton();
	}

	ReleaseDC( _hWnd, _hdc );
}

void gameNode::Update()
{
	InvalidateRect( _hWnd, NULL, false );
}

void gameNode::Render(void)
{

}


LRESULT gameNode::MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch ( iMessage )
	{
	case WM_LBUTTONDOWN:
		_leftButton = true;
		break;

	case WM_LBUTTONUP:
		_leftButton = false;
		break;

	case WM_RBUTTONDOWN:
		_rightButton = true;
		break;

	case WM_RBUTTONUP:
		_rightButton = false;
		break;

	case WM_MOUSEMOVE:
	{
		_ptMouse.x = LOWORD( lParam );
		_ptMouse.y = HIWORD( lParam );
	}
	break;

	case WM_KEYDOWN:
		switch ( wParam )
		{
		case VK_ESCAPE:
			SendMessage( hWnd, WM_DESTROY, NULL, NULL );
			break;
		}
		break;

	case WM_DESTROY: //API 에서의 소멸자 역할
		PostQuitMessage( 0 );
		return 0;
	}


	//윈도우 프로시져에서 처리되지 않은 나머지 메시지를 처리해준다 
	return ( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
}
