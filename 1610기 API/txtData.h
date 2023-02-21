#pragma once

#include "singletonBase.h"
#include <string>
#include <vector>

class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT Init();
	void Release();
	
	//���̺�
	void TxtSave( const char* saveFileName, std::vector<std::string> vStr );
	char* VectorArrayCombine( std::vector<std::string> vArray );

	//�ε�
	std::vector<std::string> TxtLoad( const char* loadFileName );
	std::vector<std::string> CharArraySeparation( char charArray[] );

};

