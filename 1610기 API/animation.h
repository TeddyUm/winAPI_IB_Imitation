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

	BOOL _loop;					//���� ����
	float _frameUpdateSec;		//������ ������Ʈ ��
	float _elapsedSec;			//������ ���� ��

	DWORD _nowPlayIdx;			//���� �÷��� �ε���
	BOOL _play;					//���� �÷��� ����

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

	//�÷��� ���� Ȯ��
	inline BOOL IsPlay() { return _play; }

	//������ ��ġ�� ��´�
	inline POINT GetFramePos() { return _frameList[_playList[_nowPlayIdx]]; }

	//������ ���� ũ�⸦ ��´�.
	inline int GetFrameWidth() { return _frameWidth; }

	//������ ���� ũ�⸦ ��´�
	inline int GetFrameHeight() { return _frameHeight; }
};

