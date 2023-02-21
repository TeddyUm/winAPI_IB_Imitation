#pragma once
#include <string>
#define OBJECTMAX 143

struct tagObjectText
{
	wstring str;
	int idx;
	bool isEnd;
};
class objectText
{
private:
	tagObjectText _objectText[OBJECTMAX];
	int _count;
	int _txtNum;
	float _timeCount; //��Ʈ ��ȯ Ÿ�� ī��Ʈ

public:
	objectText();
	~objectText();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc, int x, int y);
	wstring objectText::GetText(int txtNum);		//���� ī���Ͱ� �� ������ �����̽��� �ؽ�Ʈ�� ��ȯ�ϴ� �Լ�
	void CheckTextEnd();						//�ؽ�Ʈ�� ���̰� ��� MAX�� ��µǾ��°��� Ȯ���Ͽ� _FloweyDT�� isEnd�� true�� �����ϴ� �Լ�
	void SetTextEnd(int txtNum);				//�ؽ�Ʈ�� ������ư 'X'�� ���� �ؽ�Ʈ�� ������ �ε����� �������ִ� �Լ�
	bool GetTextEnd(int txtNum);				//txtNum��ȣ�� �ؽ�Ʈ�� ��� ��µǾ��°��� Ȯ���ϴ� �Լ�
	void SetTextIndex(int txtNum) { _objectText[txtNum].idx = 0; } //�ε����� �ʱ�ȭ �����ִ� �Լ�
	void SetTextNum(int setNum) { _txtNum = setNum; }			//�ؽ�Ʈ�� �ѹ��� ������
	int GetTextNum() { return _txtNum; }
	int GetTextIdx(int txtNum) { return _objectText[txtNum].idx; }
	//�б����� �޾ƿ� ����� GetTextEnd(int txtNum)�� �̿���
	// if������ �ش� ��ȣ�� �ؽ�Ʈ�� ����� �������� (true���� ������)
	// ���ǿ� ���� ������ �ڵ带 �����ָ� �ȴ�.
	// �׸��� SetTextNum(int setNum)�� �̿��Ͽ� �ش� �б������� �� �� ���� �ؽ�Ʈ�� ��ȣ�� �Ѱ��ش�!!!!
};

