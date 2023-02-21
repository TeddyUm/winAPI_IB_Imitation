#include "stdafx.h"
#include "openingText.h"


openingText::openingText()
{
}


openingText::~openingText()
{
}

HRESULT openingText::Init()
{
	_count = 0;
	_txtNum = 0;
	_timeCount = 0;
	FONTMANAGER->AddFont("오프닝", 25, 0, "바탕체");
	FONTMANAGER->AddFont("시작", 20, 0, "바탕체");

	_openingText[0].str = (L"In the afternoon...\nUnder the cloudy weather");
	_openingText[1].str = (L"이브와 이브의 부모님은\n미술관으로 향했습니다.");
	_openingText[2].str = (L"잊은 물건은 없니? 이브");
	_openingText[3].str = (L"그래 손수건은 챙겼니?\n그 생일날 준 거 말이야");
	_openingText[4].str = (L"주머니 속에 잘 넣어두렴\n잃어버리지 않게 말이야");

	_openingText[5].str = (L"이브와 게리는 길고 긴 계단을\n걸어 미술관으로 향했다");
	_openingText[6].str = (L"미술관으로 나왔을 때 갑자기\n이브와 게리는 어지러움과 함께\n정신을 잃었다");
	_openingText[7].str = (L"다시 눈을 떴을 땐 모든것이\n꿈처럼 느껴졌고\n걱정스러운 눈으로\n부모님이 바라보고 있었다");
	_openingText[8].str = (L"주위를 둘러보자 멀리\n보라색 머리카락의 남자가 보였다");
	_openingText[9].str = (L"누군지 정확히 기억은 나진 않지만\n언젠가 다시 만날것이라는 확신이 들었다");
	_openingText[10].str = (L"그리고 그때는 지금과 비교할 수 없는\n큰일이 일어날 것이라는 것도...");

	_openingText[11].str = (L" ");
	for (int i = 0; i < OPENINGMAX; i++)
	{
		_openingText[i].idx = 0;
		_openingText[i].isEnd = false;
	}
	return S_OK;
}

void openingText::Release()
{
}

void openingText::Update()
{
	_count++;
	if (_count == 5)
	{
		_count = 0;
		_openingText[_txtNum].idx++;
	}

	//다음 대화로 넘어가도록
	if (KEY->IsOnceKeyDown(VK_RETURN) || KEY->IsStayKeyDown('Z'))
	{
		if (GetTextEnd(_txtNum))
		{
			_txtNum++;

			if (_txtNum > OPENINGMAX - 1) _txtNum = 0;
			GetText(_txtNum);
			SetTextIndex(_txtNum); //지나간 텍스트인덱스는 초기화 시키기
		}
	}
	else if (KEY->IsOnceKeyDown('X')) //생략버튼 == 슬라이스없이 모두 출력하기
	{
		SetTextEnd(_txtNum); //해당 텍스의 넘버의 인덱스를 str.length로 변경해주는 함수
	}

	CheckTextEnd();
}

void openingText::Render(HDC hdc, int x, int y)
{
	//if (_txtNum == 5) FONTMANAGER->TextRenderEnterCenter(hdc, 0, y, GetText(_txtNum), "오프닝", RGB(255, 255, 255));
	//else 
	FONTMANAGER->TextRenderEnter(hdc, x, y, GetText(_txtNum), "오프닝", RGB(255, 255, 255));
}

wstring openingText::GetText(int txtNum)
{
	wstring _str;
	_txtNum = txtNum;
	_str = _openingText[txtNum].str.substr(0, _openingText[_txtNum].idx);
	return _str;
}

void openingText::CheckTextEnd()
{
	if (_openingText[_txtNum].idx == _openingText[_txtNum].str.length())
	{
		_openingText[_txtNum].isEnd = true;
	}
	for (int i = 0; i < OPENINGMAX; i++)
	{
		if (i != _txtNum)
		{
			_openingText[i].isEnd = false;
		}
	}
}

void openingText::SetTextEnd(int txtNum)
{
	_openingText[txtNum].idx = _openingText[txtNum].str.length();
	_openingText[_txtNum].isEnd = true;
}

bool openingText::GetTextEnd(int txtNum)
{
	return _openingText[txtNum].isEnd;
}
