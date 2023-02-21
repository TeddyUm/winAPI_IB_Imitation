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
	//가로 프레임 수
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();
	for ( int i = 0; i < _frameNumHeight; i++ )
	{
		for ( int j = 0; j < _frameNumWidth; j++ )
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 리스트에 추가
			_frameList.push_back( framePos );
		}
	}

	//기본 프레임으로 셋팅
	SetDefPlayFrame();

	return S_OK;
}

void animation::SetDefPlayFrame( BOOL reverse, BOOL loop )
{
	//루프여부 대입
	_loop = loop;

	//플레이 리스트 초기화
	_playList.clear();

	//다시 되돌아오는 애니메이션이라면...
	if ( reverse )
	{
		//루프 애니메이션이면....
		if ( _loop )
		{
			//갈 때 프레임
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}

			//올 때 프레임
			for ( int i = _frameNum - 2; i > 0; i-- )
			{
				_playList.push_back( i );
			}
		}
		else
		{
			//갈때 프레임
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}

			//올 때 프레임
			for ( int i = _frameNum - 2; i >= 0; i-- )
			{
				_playList.push_back( i );
			}
		}
	}
	else
	{
		//갈 때 저장
		for ( int i = 0; i < _frameNum; i++ )
		{
			_playList.push_back( i );
		}
	}
}

void animation::SetPlayFrame( int * playArr, int arrLen, BOOL loop )
{
	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정직하게 프레임으로 셋팅
	for ( int i = 0; i < arrLen; i++ )
	{
		_playList.push_back( playArr[i] );
	}
}

void animation::SetPlayFrame( int start, int end, BOOL reverse, BOOL loop )
{
	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if ( start == end )
	{
		//시작프레임과 끝프레임이 같은경우
		_playList.clear();
		Stop();                  //애니메이션 실행이 될 필요가 없다.
		return;
	}


	//시작 프레임이 종료 프레임 보다 큰경우
	if ( start > end )
	{
		//다시 되돌아 오는 애니메이션이라면...
		if ( reverse )
		{
			//루프 애니메이션이면...
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
			//루프 애니메이션이 아니면..
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
		//다시 되돌아 오는 애니메이션이라면...
		if ( reverse )
		{
			//루프 애니메이션이면...
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
			//루프 애니메이션이 아니면..
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

	//프레임 업데이트 시간이 되었다면...
	if ( _elapsedSec >= _frameUpdateSec )
	{
		_elapsedSec -= _frameUpdateSec;
		_nowPlayIdx++;

		if ( _nowPlayIdx == _playList.size() )
		{
			//루프 플레이라면...
			if ( _loop )
			{
				_nowPlayIdx = 0;
			}
			//아니라면...
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
