#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

class elements
{
public:
	const char* name;
	float increaseSpeed;
	float maxSpeed;
	float angle;
	int currentHP;
	int maxHP;

	elements() {}
	~elements() {}
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*> mapElement;
	typedef map<string, elements*>::iterator mapElementIter;

private:
	mapElement _mTotalElement;

public:
	database();
	~database();

	HRESULT Init();
	void Release();

	void LoadDatabase( string name );

	elements* GetElementData( string str ) { return _mTotalElement.find( str )->second; }

	void SetElementDataIncreaseSpeed( string str, float increaseSpeed );
	void SetElementDataMaxSpeed( string str, float maxSpeed );
	void SetElementDataAngle( string str, float angle );
	void SetElementDataCurrentHP( string, int );
	void SetElementDataMaxHP( string, int );
};

