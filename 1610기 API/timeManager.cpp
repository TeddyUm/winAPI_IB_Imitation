#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager() : _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::Init()
{
	_timer = new timer;
	_timer->Init();

	return S_OK;
}

void timeManager::Release()
{
	SAFE_DELETE( _timer );
}

void timeManager::Update( float lock )
{
	if ( _timer != NULL )
	{
		_timer->Tick( lock );
	}
}

void timeManager::Render( HDC hdc )
{
	char str[256];
	string strFrame;

	//���� ����� ( TRANSPARENT : ����, OPAQUE : ������(����Ʈ) )
	SetBkMode( hdc, TRANSPARENT );

	//���� ����
	SetTextColor( hdc, RGB( 200, 200, 200 ) );

#ifdef _DEBUG
	{
		if ( _timer != NULL )
		{
			//������ �������
			//sprintf_s( str, "framePerSec : %d", _timer->GetFrameRate() );
			//TextOut( hdc, 0, 0, str, strlen( str ) );

			////����Ÿ�� �������
			//sprintf_s( str, "WorldTime : %f", _timer->GetWorldTime() );
			//TextOut( hdc, 0, 20, str, strlen( str ) );

			////���� Tick �������
			//sprintf_s( str, "elapsedTime : %f", _timer->GetElapsedTime() );
			//TextOut( hdc, 0, 40, str, strlen( str ) );
		}
	}
#else
	{
		if ( _timer != NULL )
		{
			////������ �������
			//sprintf_s( str, "framePerSec : %d", _timer->GetFrameRate() );
			//TextOut( hdc, 0, 0, str, strlen( str ) );
		}
	}

#endif

}
