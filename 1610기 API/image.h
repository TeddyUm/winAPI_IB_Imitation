#pragma once

#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ��κ��� ����
		LOAD_FILE,			//���Ϸκ��� ����
		LOAD_EMPTY,			//�� ����
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		BYTE loadType;

		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		RECT boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0.f;
			y = 0.f;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;

			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			boundingBox = RectMake();
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	//������ ���ÿ� ����̴ϼȶ������ �ʱ�ȭ ���ִ� ������
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�̹��� ��� �̸�

	BOOL			_trans;			//���� ����̳�?
	COLORREF		_transColor;	//���� ����

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	//�� ��Ʈ�� �̹��� �����
	HRESULT Init( int width, int height );

	//���ҽ��κ��� �о�´�
	HRESULT Init( const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE );

	//�̹��� ����(���Ϸ� �о��)
	HRESULT Init( const char* fileName, int width, int height,
		BOOL trans, COLORREF transColor );

	HRESULT Init( const char* fileName, float x, float y, int width, int height,
		BOOL trans, COLORREF transColor );

	HRESULT Init( const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor);

	HRESULT Init( const char* fileName, int width, int height, 
		int frameX, int frameY, bool trans, COLORREF transColor);

	void InitAlpha();

	//����
	void Release();

	//���� Ű�� ���� == Ư�� ���� �׸��� ���� ��
	void SetTransColor( BOOL trans, COLORREF transColor );

	//ī�޶� ���� (Ÿ�� ����)
	void RenderTarget( HDC hdc, int drawCenterX, int drawCenterY, int drawW, int drawH, int totalW, int totalH);
	void RenderTarget( HDC hdc, int drawCenterX, int drawCenterY, int drawW, int drawH );

	//�׳� ����
	void Render( HDC hdc );
	void Render( HDC hdc, int destX, int destY );
	void Render( HDC hdc, int sourX, int sourY, int width, int height );
	void Render( HDC hdc, int destX, int destY, int sourX, int sourY, 
		int width, int height);

	//���� ����
	void AlphaRender( HDC hdc, BYTE alpha );
	void AlphaRender( HDC hdc, int destX, int destY, BYTE alpha );
	void AlphaRender( HDC hdc, int destX, int destY, int sourX, int sourY,
		int width, int height, BYTE alpha );

	//������ ����
	void FrameRender( HDC hdc, int destX, int destY );
	void FrameRender( HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY );

	void LoopRender( HDC hdc, const LPRECT drawArea, int offsetX, int offsetY );

	//�ִϷ���
	void AniRender( HDC hdc, int destX, int destY, animation* ani );


	//DC ������
	inline HDC GetMemDC() { return _imageInfo->hMemDC; }

	//��ǥ X
	inline void SetX( float x ) { _imageInfo->x = x; }
	inline float GetX() { return _imageInfo->x; }

	//��ǥ Y
	inline void SetY( float y ) { _imageInfo->y = y; }
	inline float GetY() { return _imageInfo->y; }

	//��ǥ ����
	inline void SetCenter( float x, float y )
	{
		_imageInfo->x = x - ( _imageInfo->width / 2 );
		_imageInfo->y = y - ( _imageInfo->height / 2 );
	}

	//���� X
	inline float GetCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + ( _imageInfo->width / 2 ) :
			_imageInfo->x + ( _imageInfo->frameWidth / 2 );
	}

	//���� Y
	inline float GetCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + ( _imageInfo->height / 2 ) :
			_imageInfo->y + ( _imageInfo->frameHeight / 2 );
	}

	//���� �ػ�
	inline int GetWidth() { return _imageInfo->width; }

	//���� �ػ�
	inline int GetHeight() { return _imageInfo->height; }

	//�ٿ�� �ڽ�
	inline RECT BoundingBox()
	{
		RECT rc = { 
			(int)_imageInfo->x, 
			(int)_imageInfo->y,
			(int) _imageInfo->x + _imageInfo->frameWidth,
			(int) _imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//������
	inline void SetFrameX( int frameX )
	{
		_imageInfo->currentFrameX = frameX;

		if ( frameX > _imageInfo->maxFrameX )
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY( int frameY )
	{
		_imageInfo->currentFrameY = frameY;

		if ( frameY > _imageInfo->maxFrameY )
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline int GetFrameY() { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }
};

