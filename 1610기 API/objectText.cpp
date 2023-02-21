#include "stdafx.h"
#include "objectText.h"


objectText::objectText()
{
}


objectText::~objectText()
{
}

HRESULT objectText::Init()
{
	_count = 0;
	_txtNum = 0;
	_timeCount = 0;
	FONTMANAGER->AddFont("오프닝", 25, 0, "바탕체");
	FONTMANAGER->AddFont("시작", 20, 0, "바탕체");

	// museumS 대사
	_objectText[0].str = (L"We arrive.\nEve is first to the art\nmuseum, right?");
	_objectText[1].str = (L"오늘 보러 온 건\n'게르테나'라는 사람의\n전람회 인데.....");
	_objectText[2].str = (L"그림 말고도 조각이라던지.....\n여러가지 재미있는 작품이 있으니까");
	_objectText[3].str = (L"분명 이브에게도\n재밌을거라고 생각해");
	_objectText[4].str = (L"그럼 접수하러 가볼까");
	_objectText[5].str = (L"그렇지 나중에\n팜플렛도 가져가요");
	_objectText[6].str = (L"응? 먼저가서 보고 싶다고?\n이브도 참... 어쩔 수 없구나");
	_objectText[7].str = (L"알겠니? 미술관에서는\n조용히 있어야 한단다");
	_objectText[8].str = (L"뭐 이브라면\n걱정 없을 거라고 생각하지만");
	_objectText[9].str = (L"다른 사람들에게 폐를 끼쳐선\n안된단다");

	_objectText[10].str = (L"다른 사람들에게 폐를 끼쳐선\n안된단다");

	_objectText[11].str = (L"아빠는 접수인과 대화하고 있다");

	_objectText[12].str = (L"거긴 들어가면 안돼 이브");

	_objectText[13].str = (L"한 대 피워볼까.....");

	_objectText[14].str = (L"창밖은 밝다.....");

	_objectText[15].str = (L"맘대로 나가면 안 돼");

	_objectText[16].str = (L"팜플렛이 놓여있다,.");
	_objectText[17].str = (L"■조작방법■\n  * 'Z 키' ----- 대화, 조사, 결정\n  * 'C 키' ----- 소지 아이템 확인");

	_objectText[18].str = (L"출입문이 열리지 않아...");

	_objectText[19].str = (L"잠겨있지 않은데 열리지 않아...");

	_objectText[20].str = (L"");

	// museum1F_1 대사
	_objectText[21].str = (L"어서오세요 '게르테나'의 세게에!\n 이 관에서는 '와이즈 게르테나 전'을\n ??하고 있습니다");
	_objectText[22].str = (L"게르테나가 생전에 그린 기묘하고\n 아름다운 그림을 마음껏 즐겨주세요\n XX XX XX");
	_objectText[23].str = (L"어려워서 읽을 수 없는 글자가 있다...");

	_objectText[24].str = (L"악의없는 ??");
	_objectText[25].str = (L"어려워서 읽을 수 없는 글자가 있다...");

	_objectText[26].str = (L"심해의 ??\n 그 사람의 접근을 용납치 않는 그 세계를\n ??하기 위해 캔버스 안에 ??했다");
	_objectText[27].str = (L"어려워서 읽을 수 없는 글자가 있다...");

	_objectText[28].str = (L"이 작품 꼭 한번 보고 싶었어!");
	_objectText[29].str = (L"역시 책에서 보는 것과는\n 무척 다르구나.. 분위기가 그래!");

	_objectText[30].str = (L"뭔가 빠질거 같아서 무서워...");

	_objectText[31].str = (L"아무도 없어...");
	_objectText[32].str = (L"");
	_objectText[33].str = (L"");
	_objectText[34].str = (L"");
	_objectText[35].str = (L"");

	// museum1F_2 대사
	_objectText[36].str = (L"이야~ 과연 게르테나 선생!\n보면 볼수록 깊이가 있는걸....");

	_objectText[37].str = (L"정말 멋진 그림...\n이런건 어떻게 하면 그릴 수 있을까");
	_objectText[38].str = (L"");
	_objectText[39].str = (L"");
	_objectText[40].str = (L"");
	_objectText[41].str = (L"");
	_objectText[42].str = (L"");

	// museum1F_3 대사
	_objectText[43].str = (L"기침하는 남자");

	_objectText[44].str = (L"이거 살짝만 충격이 가해져도\n저 줄기부분이 부러지거나\n않을까...");
	_objectText[45].str = (L"만약 그렇게 되면\n대체 얼마나 변상해야하는거지..\n우와아 무서운걸");
	_objectText[46].str = (L"");
	_objectText[47].str = (L"");
	_objectText[48].str = (L"");
	_objectText[49].str = (L"");

	//	museum2F_1 대사
	_objectText[50].str = (L"..........");

	_objectText[51].str = (L"근데 이 석상\n꽤 스타일이 좋은걸");

	_objectText[52].str = (L"'무개성'");
	_objectText[53].str = (L"");
	_objectText[54].str = (L"");
	_objectText[55].str = (L"");

	//	museum2F_2 대사
	_objectText[56].str = (L"아름다운 사람이네.\n근데 이거 실존인물인가?");
	_objectText[57].str = (L"게르테나는 그다지 실존인물을\n그리지 않았던것 같은데 말이야");
	_objectText[58].str = (L"그래도 진짜 있을 것 같지?\n이 여자라던가...대단하군");

	_objectText[59].str = (L"쓰디쓴 과실");

	_objectText[60].str = (L"");
	_objectText[61].str = (L"");
	_objectText[62].str = (L"");
	_objectText[63].str = (L"");
	_objectText[64].str = (L"");

	//	museum2F_3 대사
	_objectText[65].str = (L"???의 세계");
	_objectText[66].str = (L"어려워서 읽을 수 없는 글자가 있다...");

	_objectText[67].str = (L".......?");

	_objectText[68].str = (L"액자 뒤에서 파란 액체가 흘러내린다");

	_objectText[69].str = (L"아래로 내려오련 이브\n비밀의 장소 알려줄게");
	_objectText[70].str = (L"");
	_objectText[71].str = (L"");
	_objectText[72].str = (L"");
	_objectText[73].str = (L"");

	//blue1
	_objectText[74].str = (L"으으으...");
	_objectText[75].str = (L"남자는 움직이지 않는다.");

	_objectText[76].str = (L"으.. 여기가 어디지?");
	_objectText[77].str = (L"넌 누구니? 내 이름은 게리라고 해\n어떻게 된일인지 아니?");
	_objectText[78].str = (L"미술관에서 그림을 보고 있었는데\n갑자기 정신을 잃었단다");
	_objectText[79].str = (L"네가 준 푸른 장미를 받으니\n정신이 들었어");
	_objectText[80].str = (L"옆에 계단이 있으니 올라가 보자꾸나");
	_objectText[81].str = (L"좀전까지 계단이 없었다고?\n그럴리가 있니");
	_objectText[82].str = (L"어서 미술관으로 돌아가도록 하자");
	_objectText[83].str = (L"");

	//blue2
	_objectText[84].str = (L"꽃병에 장미꽃이 꽃혀있다....");
	_objectText[85].str = (L"이브는 장미꽃을 꺾었다.");
	_objectText[86].str = (L"붉은 장미를 얻었다.");
	_objectText[87].str = (L"");
	_objectText[88].str = (L"");
	_objectText[89].str = (L"");
	_objectText[90].str = (L"");

	//blue3
	_objectText[91].str = (L"그 장미가 ?? 할 때 그대도 ?? 된다");
	_objectText[92].str = (L"어려워서 읽을 수 없는 글자가 있다");

	_objectText[93].str = (L"뭔가 떨어져 있다...");
	_objectText[94].str = (L"파란 열쇠를 얻었다");
	_objectText[95].str = (L"");
	_objectText[96].str = (L"");

	//blue4
	_objectText[97].str = (L"펜에 지금까지의 일을 적었다.");
	_objectText[98].str = (L"진행사항이 저장되었습니다.");

	_objectText[99].str = (L"??? 문양의 물고기");
	_objectText[100].str = (L"어려워서 읽을 수 없는 글자가 있다...");
	_objectText[101].str = (L"파란 열쇠를 사용하여 문을 열었다.");
	_objectText[102].str = (L"문이 잠겨있는것 같다.");
	_objectText[103].str = (L"");
	_objectText[104].str = (L"");

	//green1
	_objectText[105].str = (L"무당벌레 그림이 걸려있다");

	_objectText[106].str = (L"벌 그림이 걸려있다");

	_objectText[107].str = (L"나비 그림이 걸려있다");

	_objectText[108].str = (L"거미 그림이 걸려있다");

	_objectText[109].str = (L"나 개미");
	_objectText[110].str = (L"나 그림 무지 좋아");
	_objectText[111].str = (L"내 그림 무지 멋져");
	_objectText[112].str = (L"내 그림 보고 싶은데\n좀 멀리 있어");

	_objectText[113].str = (L"테두리를 주의");

	_objectText[114].str = (L"개미 그림이 걸려있다...");
	_objectText[115].str = (L"....?");
	_objectText[116].str = (L"이 그림은 벽에서 떼어낼 수 있을것 같다");
	_objectText[117].str = (L"개미 그림을 얻었다");

	_objectText[118].str = (L"아 그거 내 그림");
	_objectText[119].str = (L"역시 무지 멋져");
	_objectText[120].str = (L"헤벌레");

	_objectText[121].str = (L"내 그림 어쨌어");
	_objectText[122].str = (L"");
	_objectText[123].str = (L"");
	_objectText[124].str = (L"");
	_objectText[125].str = (L"");

	//green2
	_objectText[126].str = (L"프롤로그");

	_objectText[127].str = (L"제1장");

	_objectText[128].str = (L"제2장");

	_objectText[129].str = (L"최종장");

	_objectText[130].str = (L"에필로그");

	_objectText[131].str = (L"개미 그림을 틈 사이에 올렸다");

	_objectText[132].str = (L"머리없는 상이 있다...");

	_objectText[133].str = (L"뭔가 떨어져 있다...");
	_objectText[134].str = (L"파란 장미를 얻었다");
	_objectText[135].str = (L"제3장");
	_objectText[136].str = (L"");
	_objectText[137].str = (L"");
	_objectText[138].str = (L"");
	_objectText[139].str = (L"");

	//green3
	_objectText[140].str = (L"바닥이 갈라져있어 지나갈 수 없어...");
	_objectText[141].str = (L"개미 그림을 틈 사이에 올렸다");
	_objectText[142].str = (L"");

	for (int i = 0; i < OBJECTMAX; i++)
	{
		_objectText[i].idx = 0;
		_objectText[i].isEnd = false;
	}
	return S_OK;
}

void objectText::Release()
{
}

void objectText::Update()
{
	_count++;
	if (_count == 2)
	{
		_count = 0;
		_objectText[_txtNum].idx++;
	}

	//다음 대화로 넘어가도록
	if (KEY->IsOnceKeyDown(VK_RETURN) || KEY->IsStayKeyDown('Z'))
	{
		if (GetTextEnd(_txtNum))
		{
			_txtNum++;

			if (_txtNum > OBJECTMAX - 1) _txtNum = 0;
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

void objectText::Render(HDC hdc, int x, int y)
{
	FONTMANAGER->TextRenderEnter(hdc, x, y, GetText(_txtNum), "오프닝", RGB(255, 255, 255));
}

wstring objectText::GetText(int txtNum)
{
	wstring _str;
	_txtNum = txtNum;
	_str = _objectText[txtNum].str.substr(0, _objectText[_txtNum].idx);
	return _str;
}

void objectText::CheckTextEnd()
{
	if (_objectText[_txtNum].idx == _objectText[_txtNum].str.length())
	{
		_objectText[_txtNum].isEnd = true;
	}
	for (int i = 0; i < OBJECTMAX; i++)
	{
		if (i != _txtNum)
		{
			_objectText[i].isEnd = false;
		}
	}
}

void objectText::SetTextEnd(int txtNum)
{
	_objectText[txtNum].idx = _objectText[txtNum].str.length();
	_objectText[_txtNum].isEnd = true;
}

bool objectText::GetTextEnd(int txtNum)
{
	return _objectText[txtNum].isEnd;
}
