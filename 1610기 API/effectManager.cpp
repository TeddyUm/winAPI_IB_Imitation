#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}

HRESULT effectManager::Init( void )
{
	return S_OK;
}

void effectManager::Release( void )
{
	iterTotalEffect vIter;
	iterEffect mIter;


	//����Ʈ�� ��� �־��� ���͸� �˻�
	vIter = _vTotalEffects.begin();

	for ( ; vIter != _vTotalEffects.end(); ++vIter )
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		mIter = vIter->begin();
		for ( ; mIter != vIter->end();)
		{
			if ( mIter->second.size() != 0 )
			{
				iterEffects vArrIter = mIter->second.begin();
				for ( vArrIter; vArrIter != mIter->second.end();  ) 
				{
					( *vArrIter )->Release();
					delete *vArrIter;
					vArrIter = mIter->second.erase( vArrIter );
				}
			}
			else
			{
				++mIter;
			}
		}
	}

}

void effectManager::Update( void )
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־��� ���͸� �˻�
	for ( vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter )
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for ( mIter = vIter->begin(); mIter != vIter->end(); ++mIter )
		{
			iterEffects vArrIter;
			for ( vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter )
			{
				( *vArrIter )->Update();
			}
		}
	}

}

void effectManager::Render( void )
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־��� ���͸� �˻�
	for ( vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter )
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for ( mIter = vIter->begin(); mIter != vIter->end(); ++mIter )
		{
			iterEffects vArrIter;
			for ( vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter )
			{
				( *vArrIter )->Render();
			}
		}
	}

}

void effectManager::AddEffect( string effectName, const char * imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer )
{
	image* img;
	arrEffects vEffectBuffer;     //����Ʈ ���� ����
	arrEffect mArrEffect;         //Ű ���� ����Ʈ ���� ����� ��

								  //��ϵ� �̹����� �Ŵ����� �̹� ������
	if (IMAGEMANAGER->FindImage( imageName ) )
	{
		img = IMAGEMANAGER->FindImage( imageName );
	}
	//������
	else
	{
		//�̹��� ���
		img = IMAGEMANAGER->AddImage( imageName, imageName, imageWidth, imageHeight, true, RGB( 255, 0, 255 ) );

	}

	//�� ���۰�����ŭ ���Ϳ� �����
	for ( int i = 0; i < buffer; i++ )
	{
		vEffectBuffer.push_back( new effect );
		vEffectBuffer[i]->init( img, effectWidth, effectHeight, fps, elapsedTime );
	}

	//����Ʈ ���۸� �ʿ� �����
	mArrEffect.insert( pair <string, arrEffects>( effectName, vEffectBuffer ) );

	//Ű ���� ���۸� ���� ���� ��Ż���Ϳ� ����ش�
	_vTotalEffects.push_back( mArrEffect );

}

void effectManager::Play( string effectName, int x, int y )
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־��� ���͸� �˻�
	for ( vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter )
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for ( mIter = vIter->begin(); mIter != vIter->end(); ++mIter )
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ
			if ( !( mIter->first == effectName ) ) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� �����Ų��
			iterEffects vArrIter;
			for ( vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter )
			{
				//����Ʈ ��Ʈ����
				//�̸� ����Ʈ�� Ȱ��ȭ �Ǿ������� ������ ��ŸƮ
				if ( ( *vArrIter )->GetIsRunning() ) continue;
				( *vArrIter )->StartEffect( x, y );
				return;
			}
		}
	}

}
