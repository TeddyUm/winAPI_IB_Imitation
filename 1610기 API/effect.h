#pragma once
#include "gameNode.h"

//�ӵ��� ���� ������
class animation;

class effect : public gameNode
{
protected:
	int _x;                                    //����Ʈ ��ǥ��ġ(x) ����Ʈ
	int _y;                                    //����Ʈ ��ǥ��ġ(y) ž

	image* _effectImage;          //����Ʈ �̹���
	animation* _effectAnimation;//����Ʈ �ִϸ��̼�
	BOOL _isRunning;               //����Ʈ Ȱ��ȭ ����
	float _elapsedTime;                  //����Ʈ ����ð�

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

