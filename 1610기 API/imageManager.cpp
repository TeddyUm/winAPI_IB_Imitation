#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::Init()
{


	return S_OK;
}

void imageManager::Release()
{
	DeleteAll();
}

image * imageManager::AddImage( string strKey, int width, int height )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( width, height ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const DWORD resID, 
	int width, int height, BOOL trans, COLORREF transColor )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( resID, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const char * fileName, 
	float x, float y, int width, int height, BOOL trans, COLORREF transColor )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( fileName, x, y, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddImage( string strKey, const char * fileName, 
	int width, int height, BOOL trans, COLORREF transColor )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( fileName, width, height, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddFrameImage( string strKey, const char * fileName, float x, float y, 
	int width, int height, int frameX, int frameY, bool trans, COLORREF transColor )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( fileName, x, y, width, height, frameX, frameY, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::AddFrameImage( string strKey, const char * fileName, 
	int width, int height, int frameX, int frameY, bool trans, COLORREF transColor )
{
	//������ �̹����� �ִ��� üũ
	image* img = FindImage( strKey );

	//Ű ���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹����� �ҷ�����
	if ( img ) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ����� ó��
	if ( FAILED( img->Init( fileName, width, height, frameX, frameY, trans, transColor ) ) )
	{
		SAFE_DELETE( img );
		return NULL;
	}

	//������ �̹����� �ʿ� �߰�������
	_mImageList.insert( make_pair( strKey, img ) );

	return img;
}

image * imageManager::FindImage( string strKey )
{
	//�ش� Ű�� �ִ��� �˻�
	mapImageIter iter = _mImageList.find( strKey );

	if ( iter != _mImageList.end() )
	{
		return iter->second;
	}

	return NULL;
}

BOOL imageManager::DeleteImage( string strKey )
{
	//�ش� Ű �ϴ� �˻�
	mapImageIter iter = _mImageList.find( strKey );

	//Ű�� ã������
	if ( iter != _mImageList.end() )
	{
		//�̹��� ����
		iter->second->Release();

		//�޸𸮵� ����
		SAFE_DELETE( iter->second );

		//�ʿ� �ִ� �浵 ö������
		_mImageList.erase( iter );

		return true;
	}

	return false;
}

BOOL imageManager::DeleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for ( ; iter != _mImageList.end(); )
	{
		if ( iter->second != NULL )
		{
			iter->second->Release();
			SAFE_DELETE( iter->second );
			iter = _mImageList.erase( iter );//�ݺ������� erase ����� ���� ������ ���X
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return true;
}

void imageManager::Render( string strKey, HDC hdc )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc );
}

void imageManager::Render( string strKey, HDC hdc, int destX, int destY )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc, destX, destY );
}

void imageManager::Render( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight )
{
	image* img = FindImage( strKey );
	if ( img ) img->Render( hdc, destX, destY, sourX, sourY, sourWidth, sourHeight );
}

void imageManager::AlphaRender( string strKey, HDC hdc, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, alpha );
}

void imageManager::AlphaRender( string strKey, HDC hdc, int destX, int destY, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, destX, destY, alpha );
}

void imageManager::AlphaRender( string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha )
{
	image* img = FindImage( strKey );
	if ( img ) img->AlphaRender( hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::FrameRender( string strKey, HDC hdc, int destX, int destY )
{
	image* img = FindImage( strKey );
	if ( img ) img->FrameRender( hdc , destX, destY);
}

void imageManager::FrameRender( string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY )
{
	image* img = FindImage( strKey );
	if ( img ) img->FrameRender( hdc, destX, destY, currentFrameX, currentFrameY );
}

void imageManager::LoopRender( string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY )
{
	image* img = FindImage( strKey );
	if ( img ) img->LoopRender( hdc, drawArea, offsetX, offsetY );
}
