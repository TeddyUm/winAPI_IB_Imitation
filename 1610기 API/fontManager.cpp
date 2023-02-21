#include "stdafx.h"
#include "fontManager.h"

//��Ʈ �Ŵ��� : �ݵ�� �����->��Ʈ, ����, �׸���, �ı�
//����������, ���� �ƿ�����, 
//������ ������ ��Ʈ �̸� �����Ҽ��ִ� string���� , map���� �����
// �߰�++ ���뼱 ������ �ִ� �Լ� ���� �����
//p.s. settextcolor�� �ٽ� ���� �ǵ����ִ� �ڵ� �־����

//addfont : ����, �ʺ�, ���ڸ�, ����, ���뼱, ��Ʈ �̸� 
//���� : �׸���, �ܰ���, 

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
		height,						//����
		width,						//�ʺ�
		0,							//��ü ����
		0,							//���� �ϳ��� ����
		FW_NORMAL,					//����
		0,							//���ڸ�
		0,							//����
		0,							//���뼱
		DEFAULT_CHARSET,			//���� ����
		0,							//��� ��Ȯ��
		OUT_DEFAULT_PRECIS,			//Ŭ���� ��Ȯ��
		CLIP_STROKE_PRECIS,			//���� ����Ƽ
		0,							//�ڰ�
		textName					//��Ʈ �̸� ���ڿ�
	);

	_fList.insert(make_pair(strKey, font));
}

void fontManager::AddFont(string strKey, int height, int width, int weight, const char * textName)
{
	if (weight == 0) weight = FW_NORMAL;

	HFONT font = CreateFont(
		height,						//����
		width,						//�ʺ�
		0,							//��ü ����
		0,							//���� �ϳ��� ����
		weight,						//����
		0,							//���ڸ�
		0,							//����
		0,							//���뼱
		DEFAULT_CHARSET,			//���� ����
		0,							//��� ��Ȯ��
		OUT_DEFAULT_PRECIS,			//Ŭ���� ��Ȯ��
		CLIP_STROKE_PRECIS,			//���� ����Ƽ
		0,							//�ڰ�
		textName					//��Ʈ �̸� ���ڿ�
	);

	_fList.insert(make_pair(strKey, font));
}

void fontManager::AddFont(string strKey, int height, int width, int weight, bool italic, bool underline, bool strikeline, const char * textName)
{
	if (weight == 0) weight = FW_NORMAL;
	if (weight == 1) weight = FW_BOLD;

	HFONT font = CreateFont(
		height,						//����
		width,						//�ʺ�
		0,							//��ü ����
		0,							//���� �ϳ��� ����
		FW_NORMAL,					//����
		italic,						//���ڸ�
		underline,					//����
		strikeline,					//���뼱
		DEFAULT_CHARSET,			//���� ����
		0,							//��� ��Ȯ��
		OUT_DEFAULT_PRECIS,			//Ŭ���� ��Ȯ��
		CLIP_STROKE_PRECIS,			//���� ����Ƽ
		0,							//�ڰ�
		textName					//��Ʈ �̸� ���ڿ�
	);

	_fList.insert(make_pair(strKey, font));
}


void fontManager::TextRender(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//�������� �������� ������ ����
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	TextOutW(hdc, x, y, txt.c_str(), txt.length());

	//�ٽ� ���� ������Ʈ�� ����
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//�������� �������� ������ ����
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);
	if (color == 1) color = RGB(255, 255, 255);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	RECT _rc = RectMake(x, y, 600, 300); //�ؽ�Ʈâ ������� ��������� ��
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_NOFULLWIDTHCHARBREAK);

	//�ٽ� ���� ������Ʈ�� ����
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnterCenter(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//�������� �������� ������ ����
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);
	if (color == 1) color = RGB(255, 255, 255);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	RECT _rc = RectMake(x, y, 640, 300); //�ؽ�Ʈâ ������� ��������� ��
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_CENTER);

	//�ٽ� ���� ������Ʈ�� ����
	(HFONT)SelectObject(hdc, oldFont);
}

void fontManager::TextRenderEnterMove(HDC hdc, int x, int y, wstring txt, string fontKey, COLORREF color)
{
	fontListIter iter = _fList.find(fontKey);

	//�������� �������� ������ ����
	if (iter->second == NULL) return;
	if (color == NULL) color = RGB(0, 0, 0);

	HFONT oldFont;
	oldFont = (HFONT)SelectObject(hdc, iter->second);
	SetTextColor(hdc, color);

	int moveX, moveY;
	moveX = RND->GetFromIntTo(-1, 1);
	moveY = RND->GetFromIntTo(-1, 1);

	RECT _rc = RectMake(x + moveX, y + moveY, 500, 300); //�ؽ�Ʈâ ������� ��������� ��
	DrawTextW(hdc, txt.c_str(), txt.length(), &_rc, DT_NOFULLWIDTHCHARBREAK);

	//�ٽ� ���� ������Ʈ�� ����
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

