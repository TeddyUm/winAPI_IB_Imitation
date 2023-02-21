#include "stdafx.h"
#include "animation.h"


animation::animation()
	: _frameNum(0)
	, _frameWidth(0)
	, _frameHeight(0)
	, _loop(FALSE)
	, _frameUpdateSec(0)
	, _elapsedSec(0)
	, _nowPlayIdx(0)
	, _play(FALSE)
{
}


animation::~animation()
{
}

HRESULT animation::Init( int totalW, int totalH, int frameW, int frameH )
{
	//���� ������ ��
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//���� ������ ��
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//�� ������ �� ���
	_frameNum = _frameNumWidth * _frameNumHeight;

	//������ ��ġ ����Ʈ ����
	_frameList.clear();
	for ( int i = 0; i < _frameNumHeight; i++ )
	{
		for ( int j = 0; j < _frameNumWidth; j++ )
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ġ ����Ʈ�� �߰�
			_frameList.push_back( framePos );
		}
	}

	//�⺻ ���������� ����
	SetDefPlayFrame();

	return S_OK;
}

void animation::SetDefPlayFrame( BOOL reverse, BOOL loop )
{
	//�������� ����
	_loop = loop;

	//�÷��� ����Ʈ �ʱ�ȭ
	_playList.clear();

	//�ٽ� �ǵ��ƿ��� �ִϸ��̼��̶��...
	if ( reverse )
	{
		//���� �ִϸ��̼��̸�....
		if ( _loop )
		{
			//�� �� ������
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}

			//�� �� ������
			for ( int i = _frameNum - 2; i > 0; i-- )
			{
				_playList.push_back( i );
			}
		}
		else
		{
			//���� ������
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}

			//�� �� ������
			for ( int i = _frameNum - 2; i >= 0; i-- )
			{
				_playList.push_back( i );
			}
		}
	}
	else
	{
		//�� �� ����
		for ( int i = 0; i < _frameNum; i++ )
		{
			_playList.push_back( i );
		}
	}
}

void animation::SetPlayFrame( int * playArr, int arrLen, BOOL loop )
{
	//���� ���� ����
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_playList.clear();

	//�����ϰ� ���������� ����
	for ( int i = 0; i < arrLen; i++ )
	{
		_playList.push_back( playArr[i] );
	}
}

void animation::SetPlayFrame( int start, int end, BOOL reverse, BOOL loop )
{
	//���� ���� ����
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_playList.clear();

	if ( start == end )
	{
		//���������Ӱ� ���������� �������
		_playList.clear();
		Stop();                  //�ִϸ��̼� ������ �� �ʿ䰡 ����.
		return;
	}


	//���� �������� ���� ������ ���� ū���
	if ( start > end )
	{
		//�ٽ� �ǵ��� ���� �ִϸ��̼��̶��...
		if ( reverse )
		{
			//���� �ִϸ��̼��̸�...
			if ( _loop )
			{
				for ( int i = start; i >= end; i-- )
				{
					_playList.push_back( i );
				}

				for ( int i = end + 1; i < start; i++ )
				{
					_playList.push_back( i );
				}

			}
			//���� �ִϸ��̼��� �ƴϸ�..
			else
			{
				for ( int i = start; i >= end; i-- )
				{
					_playList.push_back( i );
				}

				for ( int i = end + 1; i <= start; i++ )
				{
					_playList.push_back( i );
				}
			}
		}
		else
		{
			for ( int i = start; i >= end; i-- )
			{
				_playList.push_back( i );
			}
		}
	}

	//nStart < nEnd
	else
	{
		//�ٽ� �ǵ��� ���� �ִϸ��̼��̶��...
		if ( reverse )
		{
			//���� �ִϸ��̼��̸�...
			if ( _loop )
			{
				for ( int i = start; i <= end; i++ )
				{
					_playList.push_back( i );
				}

				for ( int i = end - 1; i > start; i-- )
				{
					_playList.push_back( i );
				}
			}
			//���� �ִϸ��̼��� �ƴϸ�..
			else
			{
				for ( int i = start; i <= end; i++ )
				{
					_playList.push_back( i );
				}

				for ( int i = end - 1; i >= start; i-- )
				{
					_playList.push_back( i );
				}
			}
		}
		else
		{
			for ( int i = start; i <= end; i++ )
			{
				_playList.push_back( i );
			}
		}
	}


}

void animation::SetFPS( int framePerSec )
{
	_frameUpdateSec = 1.f / framePerSec;
}

void animation::FrameUpdate( float elapsedTime )
{
	if ( !_play ) return;

	_elapsedSec += elapsedTime;

	//������ ������Ʈ �ð��� �Ǿ��ٸ�...
	if ( _elapsedSec >= _frameUpdateSec )
	{
		_elapsedSec -= _frameUpdateSec;
		_nowPlayIdx++;

		if ( _nowPlayIdx == _playList.size() )
		{
			//���� �÷��̶��...
			if ( _loop )
			{
				_nowPlayIdx = 0;
			}
			//�ƴ϶��...
			else
			{
				_nowPlayIdx--;
				_play = FALSE;
			}
		}
	}
}

void animation::Start()
{
	_play = TRUE;
	_nowPlayIdx = 0;
}

void animation::Stop()
{
	_play = FALSE;
	_nowPlayIdx = 0;
}

void animation::Pause()
{
	_play = FALSE;
}

void animation::Resume()
{
	_play = TRUE;
}
