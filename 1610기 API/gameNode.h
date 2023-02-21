#pragma once

#include "image.h"

static image* _backBuffer = IMAGEMANAGER->AddImage( "backBuffer", WINSIZEX * 2, WINSIZEY * 2);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT Init();
	virtual HRESULT Init( bool managerInit );
	virtual void Release();
	virtual void Update();
	virtual void Render( void );


	image*	GetBackBuffer() { return _backBuffer; }
	HDC		GetMemDC() { return _backBuffer->GetMemDC(); }
	HDC		GetHDC() { return _hdc; }


	LRESULT MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );
};

