#include "stdafx.h"
#include "fontManager.h"

//폰트 매니져 : 반드시 만들것->폰트, 높이, 그림자, 후광
//랜더쉐도우, 렌더 아웃라인, 
//스스로 지정한 폰트 이름 저장할수있는 string변수 , map으로 만들기
// 추가++ 관통선 그을수 있는 함수 따로 만들기
//p.s. settextcolor는 다시 색깔 되돌려주는 코드 있어야함

//addfont : 높이, 너비, 이텔릭, 밑줄, 관통선, 폰트 이름 
//랜더 : 그림자, 외곽선, 

fontManager::fontManager()
{
}


fontManager::~fontManager()
{
}

HRESULT fontManager::Init()
{
	return S_OK;
}

void fontManager::Release()
{
}


void fontManager::AddFont(string strKey, int height, int width, const char* textName)
{
	HFONT font = CreateFont(
		height,						//높이
		width,						//너비
		0,							//전체 기울기
		0,							//글자 하나당 기울기
		FW_NORMAL,					//굵기
		0,							//이텔릭
		0,							//밑줄
		0,							//관통선
		DEFAULT_CHARSET,			//문자 셋팅
		0,							//출력 정확도
		OUT_DEFAULT_PRECIS,			//클리핑 정확도
		CLIP_STROKE_PRECIS,			//문자 퀄리티
		0,							//자간
		textName					//폰트 이름 문자열
	);

	_fList.insert(make_pair(strKey, font));
}

void fontManager::AddFont(string strKey, int height, int width, int weight, const char * textName)
{
	if (weight == 0) weight = FW_NORMAL;

	HFONT font = CreateFont(
		height,						//높이
		width,						//너비
		0,							//전체 기울기
		0,							//글자 하나당 기울기
		weight,						//굵기
		0,							//이텔릭
		0,							//밑줄
		0,							//관통선
		DEFAULT_CHARSET,			//문자 셋팅
		0,							//출력 정확도
		OUT_DEFAULT_PRECIS,			//클리핑 정확도
		CLIP_STROKE_PRECIS,			//문자 퀄리티
		0,							//자간
		textName					//폰트 이름 문자열
	);

	_fList.insert(make_pair(strKey, font));
}

void fontManager::AddFont(string strKey, int height, int width, int weight, bool italic, bool underline, bool strikeline, const char * textName)
{
	if (weight == 0) weight = FW_NORMAL;
	if (weight == 1) weight = FW_BOLD;

	HFONT font = CreateFont(
		height,						//높이
		width,						//너비
		0,							//전체 기울기
		0,							//글자 하나당 기울기
		FW_NORMAL,					//굵기
		italic,						//이텔릭
		underline,					//밑줄
		strikeline,					//관통선
		DEFAULT_CHARSET,			//문자 셋팅
		0,							//출력 정확도
		OUT_DEFAULT_PRECIS,			//클리핑 정확도
		CLIP_STROKE_PRECIS,			//문자 퀄리티
		0,							//자간
		textName					//폰트 이름 문자열
	);

	_fList.insert(make_pair(strKey, font));
}


void fontManager::TextRender(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//벨류값이 존재하지 않으면 리턴
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	TextOutW(hdc, x, y, txt.c_str(), txt.length());

	//다시 원래 오브젝트로 선택
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//벨류값이 존재하지 않으면 리턴
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);
	if (color == 1) color = RGB(255, 255, 255);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	RECT _rc = RectMake(x, y, 600, 300); //텍스트창 사이즈로 맞춰놓으면 됨
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_NOFULLWIDTHCHARBREAK);

	//다시 원래 오브젝트로 선택
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnterCenter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//벨류값이 존재하지 않으면 리턴
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);
	if (color == 1) color = RGB(255, 255, 255);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	RECT _rc = RectMake(x, y, 640, 300); //텍스트창 사이즈로 맞춰놓으면 됨
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_CENTER);

	//다시 원래 오브젝트로 선택
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnterMove(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//벨류값이 존재하지 않으면 리턴
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	int moveX, moveY;
	moveX = RND->GetFromIntTo(-1, 1);
	moveY = RND->GetFromIntTo(-1, 1);

	RECT _rc = RectMake(x + moveX, y + moveY, 500, 300); //텍스트창 사이즈로 맞춰놓으면 됨
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_NOFULLWIDTHCHARBREAK);

	//다시 원래 오브젝트로 선택
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::DeleteFont()
{
	fontListIter iter = _fList.begin();

	for (; iter != _fList.end();)
	{
		if (iter->second != NULL)
		{
			DeleteObject(iter->second);
			iter = _fList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_fList.clear();
}

