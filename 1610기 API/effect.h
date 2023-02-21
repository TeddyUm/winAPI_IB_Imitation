#pragma once
#include "gameNode.h"

//속도를 위해 전방썬언
class animation;

class effect : public gameNode
{
protected:
	int _x;                                    //이펙트 좌표위치(x) 레프트
	int _y;                                    //이펙트 좌표위치(y) 탑

	image* _effectImage;          //이펙트 이미지
	animation* _effectAnimation;//이펙트 애니메이숀
	BOOL _isRunning;               //이펙트 활성화 여부
	float _elapsedTime;                  //이펙트 경과시간

public:
	effect();
	virtual ~effect();

	virtual HRESULT init( image* effectImage, int frameW, int frameH, int fps, float elapsedTime );
	virtual void Release( void );
	virtual void Update( void );
	virtual void Render( void );

	void StartEffect( int x, int y );
	virtual void KillEffect( void );

	BOOL GetIsRunning( void ) { return _isRunning; }

};

