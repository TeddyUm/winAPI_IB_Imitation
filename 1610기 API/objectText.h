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
	float _timeCount; //폰트 전환 타임 카운트

public:
	objectText();
	~objectText();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc, int x, int y);
	wstring objectText::GetText(int txtNum);		//일정 카운터가 될 때마다 슬라이스한 텍스트를 반환하는 함수
	void CheckTextEnd();						//텍스트의 길이가 모두 MAX로 출력되었는가를 확인하여 _FloweyDT의 isEnd에 true를 삽입하는 함수
	void SetTextEnd(int txtNum);				//텍스트의 생략버튼 'X'를 위해 텍스트의 마지막 인덱스를 세팅해주는 함수
	bool GetTextEnd(int txtNum);				//txtNum번호의 텍스트가 모두 출력되었는가를 확인하는 함수
	void SetTextIndex(int txtNum) { _objectText[txtNum].idx = 0; } //인덱스를 초기화 시켜주는 함수
	void SetTextNum(int setNum) { _txtNum = setNum; }			//텍스트의 넘버를 세팅함
	int GetTextNum() { return _txtNum; }
	int GetTextIdx(int txtNum) { return _objectText[txtNum].idx; }
	//분기점을 받아올 사람은 GetTextEnd(int txtNum)를 이용해
	// if문으로 해당 번호의 텍스트의 출력이 끝났으면 (true값을 리턴함)
	// 조건에 따라 실행할 코드를 적어주면 된다.
	// 그리고 SetTextNum(int setNum)를 이용하여 해당 분기점으로 들어간 후 나올 텍스트의 번호를 넘겨준다!!!!
};

