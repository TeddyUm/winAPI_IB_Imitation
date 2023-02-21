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
	//���࿡ �̹����� ������ ����
	if ( !effectImage ) return E_FAIL;

	//Ȱ��ȭ ���� �ʱ�ȭ
	_isRunning = false;


	//����Ʈ �̹��� ���� ����
	_effectImage = effectImage;

	//����Ʈ ��� �ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ ��������
	if ( !_effectAnimation ) _effectAnimation = new animation;

	//�ִϸ��̼� ���� ����
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
	//Ȱ��ȭ ���� �ʾ����� �������ָ� �ȵ�
	if ( !_isRunning ) return;
	_effectAnimation->FrameUpdate( _elapsedTime );

	//����Ʈ �ִϸ��̼��� ����Ǹ� kill���ش�
	if ( !_effectAnimation->IsPlay() ) KillEffect();

}

void effect::Render( void )
{
	//���� ���� ������ �׷����� �ʴ´�
	if ( !_isRunning ) return;

	//Effect �ִϸ��̼� �׷���
	_effectImage->AniRender( GetMemDC(), _x, _y, _effectAnimation );

}


void effect::StartEffect( int x, int y )
{
	//����Ʈ ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������� ����
	if ( !_effectImage || !_effectAnimation ) return;

	//x, y��ǥ�� ����Ʈ ž�̹Ƿ� �߾���ǥ�� �ٲ���
	_x = x - ( _effectAnimation->GetFrameWidth() / 2 );
	_y = y - ( _effectAnimation->GetFrameHeight() / 2 );

	_isRunning = true;
	_effectAnimation->Start();

}

void effect::KillEffect( void )
{
	_isRunning = false;
}
