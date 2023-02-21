#pragma once
#include <map>
#include <string>
#include "singletonBase.h"

//전방선언
class gameNode;

class fontManager : public singletonBase<fontManager>
{
public:
	typedef map<string, HFONT> fontList;
	typedef map<string, HFONT>::iterator fontListIter;

private:
	fontList _fList;

	int _count;
	int _moveX;
	int _moveY;

public:
	fontManager();
	~fontManager();

	HRESULT Init();
	void Release(); //모든 폰트 삭제

	void AddFont(string strKey, int height, int width, const char* textName);
	void AddFont(string strKey, int height, int width, int weight, const char* textName);
	void AddFont(string strKey, int height, int width, int weight, bool italic, bool underline, bool strikeline, const char* textName);

	void TextRender(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color);
	void TextRenderEnter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color);
	void TextRenderEnterCenter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color);
	void TextRenderEnterMove(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color);

	void DeleteFont();

	//다시 원래 오브젝트로 선택

};

