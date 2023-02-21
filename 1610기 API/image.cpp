#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")


image::image()
	: _imageInfo( NULL )
	, _fileName( NULL )
	, _trans( FALSE )
	, _transColor( RGB( 0, 0, 0 ) )
	, _blendImage(NULL)
{
}


image::~image()
{
}

//�� ��Ʈ�� �̹��� �����
HRESULT image::Init( int width, int height )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;//�����ڿ��� �ʱ�ȭ �������� ��������� �ٽ� �� ��
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) CreateCompatibleBitmap( hdc, width, height );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();



	_fileName = NULL;

	//���� �÷� ����
	_trans = FALSE;
	_transColor = RGB( 0, 0, 0 );

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

//���ҽ��κ��� �о�´�
HRESULT image::Init( const DWORD resID, int width, int height,
	BOOL trans /*= FALSE*/, COLORREF transColor /*= FALSE*/ )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();

	_fileName = NULL;

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;


	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

//�̹��� ����(���Ϸ� �о��)
HRESULT image::Init( const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();
	
	//���� ���� �ؾ� ��. fileName �Ű������� const�� ����.
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();

	//���� ���� �ؾ� ��. fileName �Ű������� const�� ����.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, float x, float y, int width, int height, 
	int frameX, int frameY, bool trans, COLORREF transColor )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->boundingBox = BoundingBox();

	//���� ���� �ؾ� ��. fileName �Ű������� const�� ����.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, int width, int height, 
	int frameX, int frameY, bool trans, COLORREF transColor )
{
	//�ʱ�ȭ�� �ٽ� �Ǵ� ���� ����
	if ( _imageInfo != NULL ) Release();

	//DC ��� ����
	HDC hdc = GetDC( _hWnd );

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->boundingBox = BoundingBox();

	//���� ���� �ؾ� ��. fileName �Ű������� const�� ����.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �Ӽ���
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� DC ����
	ReleaseDC( _hWnd, hdc );

	//���ҽ� ������ ���н� ó��
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

void image::InitAlpha()
{
	HDC hdc = GetDC( _hWnd );

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC( hdc );
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap( hdc, _imageInfo->width, _imageInfo->height );
	_blendImage->hOBit = (HBITMAP) SelectObject( _blendImage->hMemDC, _blendImage->hBit );
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC( _hWnd, hdc );
}

//����
void image::Release()
{
	if ( _imageInfo )
	{
		//�̹��� ����
		SelectObject( _imageInfo->hMemDC, _imageInfo->hOBit );
		DeleteObject( _imageInfo->hBit );
		DeleteDC( _imageInfo->hMemDC );

		//�����͵� ����
		SAFE_DELETE( _imageInfo );
		SAFE_DELETE( _fileName );

		//���� �÷� �ʱ�ȭ
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if ( _blendImage )
	{
		//�̹��� ����
		SelectObject( _blendImage->hMemDC, _blendImage->hOBit );
		DeleteObject( _blendImage->hBit );
		DeleteDC( _blendImage->hMemDC );

		SAFE_DELETE( _blendImage );
	}
}

//���� Ű�� ���� == Ư�� ���� �׸��� ���� ��
void image::SetTransColor( BOOL trans, COLORREF transColor )
{
	_trans = trans;
	_transColor = transColor;
}

void image::RenderTarget( HDC hdc, int drawCenterX, int drawCenterY, int drawW, int drawH, int totalW, int totalH )
{
	int drawX = drawCenterX - drawW / 2;
	int drawY = drawCenterY - drawH / 2;

	if ( drawX < 0 ) drawX = 0;
	else if ( drawX > totalW - drawW ) drawX = totalW - drawW;

	if ( drawY < 0 ) drawY = 0;
	else if ( drawY > totalH - drawH ) drawY = totalH - drawH;

	if ( _trans )
	{
		GdiTransparentBlt( hdc, 0, 0, drawW, drawH,
			this->_imageInfo->hMemDC, drawX, drawY, drawW, drawH, _transColor );
	}
	else
	{
		BitBlt( hdc, 0, 0, drawW, drawH,
			this->_imageInfo->hMemDC, drawX, drawY, SRCCOPY );
	}

}

void image::RenderTarget( HDC hdc, int drawCenterX, int drawCenterY, int drawW, int drawH )
{

	int drawX = drawCenterX - drawW / 2;
	int drawY = drawCenterY - drawH / 2;

	if ( drawX < 0 ) drawX = 0;
	else if ( drawX > this->_imageInfo->width - drawW ) drawX = this->_imageInfo->width - drawW;

	if ( drawY < 0 ) drawY = 0;
	else if ( drawY > this->_imageInfo->height - drawH ) drawY = this->_imageInfo->height - drawH;

	if ( _trans )
	{
		GdiTransparentBlt( hdc, 0, 0, drawW, drawH,
			this->_imageInfo->hMemDC, drawX, drawY, drawW, drawH, _transColor );
	}
	else
	{
		BitBlt( hdc, 0, 0, drawW, drawH,
			this->_imageInfo->hMemDC, drawX, drawY, SRCCOPY );
	}
}

void image::Render( HDC hdc )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor );
	}
	else
	{
		BitBlt( hdc, (int) _imageInfo->x, (int) _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

//����
void image::Render( HDC hdc, int destX, int destY )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, //���� �� DC
			destX,				//���� �� ��ġ X
			destY,				//���� �� ��ġ Y
			_imageInfo->width,	//���� �� ���� ������
			_imageInfo->height,	//���� �� ���� ������
			_imageInfo->hMemDC,	//���� �� �̹��� DC
			0, 0,				//���� �������� X, Y
			_imageInfo->width,	//���� �� width
			_imageInfo->height,	//���� �� height
			_transColor );		//���ܽ�ų ����
	}
	else
	{
		//BitBlt �� DC ���� ��� ���� ���ִ� �༮
		BitBlt(hdc,					//���� �� DC
			destX,					//���� �� ��ġ X
			destY,					//���� �� ��ġ Y
			_imageInfo->width,		//���� �� ���� ������
			_imageInfo->height,		//���� �� ���� ������
			_imageInfo->hMemDC,		//���� �� �̹��� DC
			0, 0,					//���� �������� X, Y
			SRCCOPY );				//���� �Ӽ� ����
	}
}

void image::Render( HDC hdc, int destX, int destY, int sourWidth, int sourHeight )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _transColor );
	}
	else
	{
		BitBlt( hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

void image::Render( HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight )
{
	if ( _trans )
	{
		GdiTransparentBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor );
	}
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY );
	}
}

void image::AlphaRender( HDC hdc, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();

	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//����ؾ� �� Dc�� �׷����ִ� ������ blend�� �׷��ش�
		BitBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY );

		//����ؾ� �� �̹����� blend�� �׷��ش�
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor );

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend( hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
}

void image::AlphaRender( HDC hdc, int destX, int destY, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//����ؾ� �� Dc�� �׷����ִ� ������ blend�� �׷��ش�
		BitBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY );

		//����ؾ� �� �̹����� blend�� �׷��ش�
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor );

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend( hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
}

void image::AlphaRender( HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//����ؾ� �� Dc�� �׷����ִ� ������ blend�� �׷��ش�
		BitBlt( _blendImage->hMemDC, 0, 0, width, height,
			hdc, destX, destY, SRCCOPY );

		//����ؾ� �� �̹����� blend�� �׷��ش�
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, width, height,
			_imageInfo->hMemDC, sourX, sourY,
			width, height, _transColor );

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend( hdc, destX, destY, width, height,
			_blendImage->hMemDC, 0, 0, width, height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, destX, destY, width, height,
			_imageInfo->hMemDC, 0, 0, width, height, _blendFunc );
	}
}

void image::FrameRender( HDC hdc, int destX, int destY )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY, 
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,	
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight, 
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_transColor );	
	}
	else
	{
		//BitBlt �� DC ���� ��� ���� ���ִ� �༮
		BitBlt( hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,	
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY );
	}
}

void image::FrameRender( HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY )
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if ( currentFrameX > _imageInfo->maxFrameX ) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if ( currentFrameY > _imageInfo->maxFrameY ) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_transColor );
	}
	else
	{
		//BitBlt �� DC ���� ��� ���� ���ִ� �༮
		BitBlt( hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY );
	}

}

void image::LoopRender( HDC hdc, const LPRECT drawArea, int offsetX, int offsetY )
{
	//offset ���� ������ ��쿡 ����
	if ( offsetX < 0 ) offsetX = _imageInfo->width + ( offsetX % _imageInfo->width );
	if ( offsetY < 0 ) offsetY = _imageInfo->height + ( offsetY % _imageInfo->height );

	//�׷����� �ҽ� ���� ������ ���� ������
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ���� DC
	RECT rcDest;

	//�׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for ( int y = 0; y < drawAreaH; y += sourHeight )
	{
		//�ҽ� ������ ���� ���
		rcSour.top = ( y + offsetY ) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ�� ������ �̹����� ������ ��)
		if ( y + sourHeight > drawAreaH )
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷�����
			rcSour.bottom -= ( y + sourHeight ) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for ( int x = 0; x < drawAreaW; x += sourWidth )
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = ( x + offsetX ) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if ( x + sourWidth > drawAreaW )
			{
				//�Ѿ ��ŭ right ���� �������� ó��
				rcSour.right -= ( x + sourWidth ) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷����� (�κ� ��� �Լ�)
			Render( hdc, rcDest.left, rcDest.top, 
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top );
		}
	}
}

void image::AniRender( HDC hdc, int destX, int destY, animation * ani )
{
	Render( hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight() );
}

