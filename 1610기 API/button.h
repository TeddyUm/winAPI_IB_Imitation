#pragma once

#include "gameNode.h"

typedef void( *CALLBACK_FUNCTION )( void );

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	CALLBACK_FUNCTION _callbackFunction;

	BUTTONDIRECTION _direction;

	int _x, _y;
	RECT _rc;

	image* _image;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;


public:
	button();
	~button();

	virtual HRESULT Init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint );

	virtual HRESULT Init( const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction );

	void Release( void ) override;

	void Update( void ) override;
	void Render( void ) override;
	
};

