#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::Init()
{
	return S_OK;
}

void txtData::Release()
{
}

void txtData::TxtSave( const char * saveFileName, std::vector<std::string> vStr )
{
	HANDLE file;

	char str[128];
	DWORD write;

	//strcpy ��� strncpy���� ������ �� ������ ����Ʈ ���� �Ѿ�� �Ǹ� ����â�� ����ش�.
	strncpy_s( str, 128, VectorArrayCombine(vStr), 126 );

	file = CreateFile( saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	WriteFile( file, str, 128, &write, NULL );

	CloseHandle( file );
}

char * txtData::VectorArrayCombine( std::vector<std::string> vArray )
{
	char str[128];

	ZeroMemory( str, sizeof( str ) );

	for ( int i = 0; i < vArray.size(); i++ )
	{
		strncat_s( str, 128, vArray[i].c_str(), 126 );
		if ( i + 1 < vArray.size() ) strcat_s( str, "," );
	}

	return str;
}

std::vector<std::string> txtData::TxtLoad( const char * loadFileName )
{
	HANDLE file;
	char str[128];
	DWORD read;

	ZeroMemory( str, sizeof( str ) );

	file = CreateFile( loadFileName, GENERIC_READ, 0, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	ReadFile( file, str, 128, &read, NULL );
	CloseHandle( file );

	return CharArraySeparation( str );
}

std::vector<std::string> txtData::CharArraySeparation( char charArray[] )
{
	vector<string> vArray;

	char* context;
	char* separator = ",";
	char* token;

	token = strtok_s( charArray, separator, &context );
	vArray.push_back( token );

	while ( NULL != ( token = strtok_s( NULL, separator, &context ) ) )
	{
		vArray.push_back( token );
	}

	return vArray;
}
