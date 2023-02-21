#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

//timeGetTime �Լ� ����ϱ� ���� ���̺귯��
//�����찡 �������� �ð��� �˷���
#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::Init()
{
	if ( QueryPerformanceFrequency( (LARGE_INTEGER*) &_periodFrequency ) )
	{
		_isHardware = true;
		QueryPerformanceCounter( (LARGE_INTEGER*) &_lastTime );

		//�ʴ� �ð��� ��� �� �� �ִ� ���� //�ʴ� �ð� ��� ����
		_timeScale = 1.f / _periodFrequency;

	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();//�и������� ������ 1000ī���� 1��
		_timeScale = 0.001f;
	}

	_frameRate = 0.f;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.f;
	_worldTime = 0.f;

	return S_OK;
}

void timer::Tick( float lockFPS )
{
	//���� Ÿ�̸� �����ϴ�?
	if ( _isHardware )
	{
		//������ ����ũ���� ������ ���
		QueryPerformanceCounter( (LARGE_INTEGER*) &_curTime );
	}
	else
	{
		_curTime = timeGetTime();
	}

	//������ �ð��� ���� �ð��� �����
	_timeElapsed = ( _curTime - _lastTime ) * _timeScale;

	//���� ������ ó��(������ ��Ű��)
	if ( lockFPS > 0.f )
	{
		//���� �������� �ð��� ������ ������ ����
		while( _timeElapsed < (1.f / lockFPS ) )
		{
			if ( _isHardware ) QueryPerformanceCounter( (LARGE_INTEGER*) &_curTime );
			else _curTime = timeGetTime();

			//������ �ð��� ���� �ð��� �����
			_timeElapsed = ( _curTime - _lastTime ) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	//������ �ʱ�ȭ 1�ʸ��� ����
	if ( _FPSTimeElapsed > 1.f )
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.f;
	}
}

unsigned long timer::GetFrameRate( char * str ) const
{
	if ( str != NULL )
	{
		wsprintf( str, "FPS : %d", _frameRate );
	}

	return _frameRate;
}
