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
	FONTMANAGER->AddFont("������", 25, 0, "����ü");
	FONTMANAGER->AddFont("����", 20, 0, "����ü");

	_openingText[0].str = (L"In the afternoon...\nUnder the cloudy weather");
	_openingText[1].str = (L"�̺�� �̺��� �θ����\n�̼������� ���߽��ϴ�.");
	_openingText[2].str = (L"���� ������ ����? �̺�");
	_openingText[3].str = (L"�׷� �ռ����� ì���?\n�� ���ϳ� �� �� ���̾�");
	_openingText[4].str = (L"�ָӴ� �ӿ� �� �־�η�\n�Ҿ������ �ʰ� ���̾�");

	_openingText[5].str = (L"�̺�� �Ը��� ��� �� �����\n�ɾ� �̼������� ���ߴ�");
	_openingText[6].str = (L"�̼������� ������ �� ���ڱ�\n�̺�� �Ը��� ��������� �Բ�\n������ �Ҿ���");
	_openingText[7].str = (L"�ٽ� ���� ���� �� ������\n��ó�� ��������\n���������� ������\n�θ���� �ٶ󺸰� �־���");
	_openingText[8].str = (L"������ �ѷ����� �ָ�\n����� �Ӹ�ī���� ���ڰ� ������");
	_openingText[9].str = (L"������ ��Ȯ�� ����� ���� ������\n������ �ٽ� �������̶�� Ȯ���� �����");
	_openingText[10].str = (L"�׸��� �׶��� ���ݰ� ���� �� ����\nū���� �Ͼ ���̶�� �͵�...");

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

	//���� ��ȭ�� �Ѿ����
	if (KEY->IsOnceKeyDown(VK_RETURN) || KEY->IsStayKeyDown('Z'))
	{
		if (GetTextEnd(_txtNum))
		{
			_txtNum++;

			if (_txtNum > OPENINGMAX - 1) _txtNum = 0;
			GetText(_txtNum);
			SetTextIndex(_txtNum); //������ �ؽ�Ʈ�ε����� �ʱ�ȭ ��Ű��
		}
	}
	else if (KEY->IsOnceKeyDown('X')) //������ư == �����̽����� ��� ����ϱ�
	{
		SetTextEnd(_txtNum); //�ش� �ؽ��� �ѹ��� �ε����� str.length�� �������ִ� �Լ�
	}

	CheckTextEnd();
}

void openingText::Render(HDC hdc, int x, int y)
{
	//if (_txtNum == 5) FONTMANAGER->TextRenderEnterCenter(hdc, 0, y, GetText(_txtNum), "������", RGB(255, 255, 255));
	//else 
	FONTMANAGER->TextRenderEnter(hdc, x, y, GetText(_txtNum), "������", RGB(255, 255, 255));
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
