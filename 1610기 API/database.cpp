#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::Init()
{
	LoadDatabase( "database.txt" );

	return S_OK;
}

void database::Release()
{
	mapElementIter find = _mTotalElement.begin();

	for ( ; find != _mTotalElement.end(); find++ )
	{
		SAFE_DELETE( find->second );
	}

	_mTotalElement.clear();
}

void database::LoadDatabase( string name )
{
	//데이터를 읽어온다
	arrElements vTemp;

	vTemp = TXTDATA->TxtLoad( name.c_str() );

	string str;
	int count = 0;

	for ( unsigned int i = 0; i < vTemp.size(); i++ )
	{
		if ( vTemp[i] == "|" )
		{
			elements* em = new elements;
			str = vTemp[i + 1];
			_mTotalElement.insert( pair<string, elements*>( vTemp[i + 1], em ) );
			if ( i != 0 ) count += 7;
			continue;
		}

		mapElementIter mIter = _mTotalElement.find( str );
		if ( i == count + 1 ) mIter->second->name = vTemp[i].c_str();
		else if ( i == count + 2 ) mIter->second->increaseSpeed = (float) atof( vTemp[i].c_str() );
		else if ( i == count + 3 ) mIter->second->maxSpeed = (float) atof( vTemp[i].c_str() );
		else if ( i == count + 4 ) mIter->second->angle = (float) atof( vTemp[i].c_str() );
		else if ( i == count + 5 ) mIter->second->currentHP = atoi( vTemp[i].c_str() );
		else if ( i == count + 6 ) mIter->second->maxHP = atoi( vTemp[i].c_str() );
	}

	vTemp.clear();
}

void database::SetElementDataIncreaseSpeed( string str, float increaseSpeed )
{
	mapElementIter mIter = _mTotalElement.find( str );

	if ( mIter != _mTotalElement.end() ) 
		mIter->second->increaseSpeed = increaseSpeed;
}

void database::SetElementDataMaxSpeed( string str, float maxSpeed )
{
	mapElementIter mIter = _mTotalElement.find( str );

	if ( mIter != _mTotalElement.end() ) 
		mIter->second->maxSpeed = maxSpeed;
}

void database::SetElementDataAngle( string str, float angle )
{
	mapElementIter mIter = _mTotalElement.find( str );

	if ( mIter != _mTotalElement.end() ) 
		mIter->second->angle = angle;
}

void database::SetElementDataCurrentHP( string str, int currentHP)
{
	mapElementIter mIter = _mTotalElement.find( str );

	if ( mIter != _mTotalElement.end() )
		mIter->second->currentHP = currentHP;
}

void database::SetElementDataMaxHP( string str, int maxHP)
{
	mapElementIter mIter = _mTotalElement.find( str );

	if ( mIter != _mTotalElement.end() )
		mIter->second->maxHP = maxHP;
}
