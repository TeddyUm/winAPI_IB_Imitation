#pragma once

#include <vector>

class animation
{
public:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	int _frameNum;

	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;					//루프 여부
	float _frameUpdateSec;		//프레임 업데이트 초
	float _elapsedSec;			//프레임 지난 초

	DWORD _nowPlayIdx;			//현재 플레이 인덱스
	BOOL _play;					//현재 플레이 여부

public:
	animation();
	~animation();

	HRESULT Init( int totalW, int totalH, int frameW, int frameH );

	void SetDefPlayFrame( BOOL reverse = FALSE, BOOL loop = FALSE );

	void SetPlayFrame( int * playArr, int arrLen, BOOL loop = FALSE );
	void SetPlayFrame( int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE );

	void SetFPS( int framePerSec );

	void FrameUpdate( float elapsedTime );

	void Start();
	void Stop();
	void Pause();
	void Resume();

	//플레이 여부 확인
	inline BOOL IsPlay() { return _play; }

	//프레임 위치를 얻는다
	inline POINT GetFramePos() { return _frameList[_playList[_nowPlayIdx]]; }

	//프레임 가로 크기를 얻는다.
	inline int GetFrameWidth() { return _frameWidth; }

	//프레임 세로 크기를 얻는다
	inline int GetFrameHeight() { return _frameHeight; }
};

