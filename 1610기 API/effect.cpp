#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect() : _effectImage( NULL ), _effectAnimation( NULL ),
_isRunning( false ), _x( 0 ), _y( 0 )
{
}


effect::~effect()
{
}

HRESULT effect::init( image * effectImage, int frameW, int frameH, int fps, float elapsedTime )
{
	//만약에 이미지가 없으면 리턴
	if ( !effectImage ) return E_FAIL;

	//활성화 여부 초기화
	_isRunning = false;


	//이펙트 이미지 정보 대입
	_effectImage = effectImage;

	//이펙트 경과 시간
	_elapsedTime = elapsedTime;

	//이미지 애니메이숀 객체가 없으면 생성해줌
	if ( !_effectAnimation ) _effectAnimation = new animation;

	//애니메이션 정보 셋팅
	_effectAnimation->Init( _effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH );
	_effectAnimation->SetDefPlayFrame( false, false );
	_effectAnimation->SetFPS( fps );
	_effectAnimation->Stop();


	return S_OK;

}

void effect::Release( void )
{
	SAFE_DELETE( _effectAnimation );
}

void effect::Update( void )
{
	//활성화 되지 않았으면 실행해주면 안됨
	if ( !_isRunning ) return;
	_effectAnimation->FrameUpdate( _elapsedTime );

	//이펙트 애니메이숀이 종료되면 kill해준다
	if ( !_effectAnimation->IsPlay() ) KillEffect();

}

void effect::Render( void )
{
	//실행 되지 않으면 그려주지 않는다
	if ( !_isRunning ) return;

	//Effect 애니메이숀 그려줌
	_effectImage->AniRender( GetMemDC(), _x, _y, _effectAnimation );

}


void effect::StartEffect( int x, int y )
{
	//이펙트 정보가 초기화 되어있지 않다면 실행되지 않음
	if ( !_effectImage || !_effectAnimation ) return;

	//x, y좌표가 레프트 탑이므로 중앙좌표로 바꿔줌
	_x = x - ( _effectAnimation->GetFrameWidth() / 2 );
	_y = y - ( _effectAnimation->GetFrameHeight() / 2 );

	_isRunning = true;
	_effectAnimation->Start();

}

void effect::KillEffect( void )
{
	_isRunning = false;
}
