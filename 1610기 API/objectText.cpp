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
	FONTMANAGER->AddFont("������", 25, 0, "����ü");
	FONTMANAGER->AddFont("����", 20, 0, "����ü");

	// museumS ���
	_objectText[0].str = (L"We arrive.\nEve is first to the art\nmuseum, right?");
	_objectText[1].str = (L"���� ���� �� ��\n'�Ը��׳�'��� �����\n����ȸ �ε�.....");
	_objectText[2].str = (L"�׸� ���� �����̶����.....\n�������� ����ִ� ��ǰ�� �����ϱ�");
	_objectText[3].str = (L"�и� �̺꿡�Ե�\n������Ŷ�� ������");
	_objectText[4].str = (L"�׷� �����Ϸ� ������");
	_objectText[5].str = (L"�׷��� ���߿�\n���÷��� ��������");
	_objectText[6].str = (L"��? �������� ���� �ʹٰ�?\n�̺굵 ��... ��¿ �� ������");
	_objectText[7].str = (L"�˰ڴ�? �̼���������\n������ �־�� �Ѵܴ�");
	_objectText[8].str = (L"�� �̺���\n���� ���� �Ŷ�� ����������");
	_objectText[9].str = (L"�ٸ� ����鿡�� �� ���ļ�\n�ȵȴܴ�");

	_objectText[10].str = (L"�ٸ� ����鿡�� �� ���ļ�\n�ȵȴܴ�");

	_objectText[11].str = (L"�ƺ��� �����ΰ� ��ȭ�ϰ� �ִ�");

	_objectText[12].str = (L"�ű� ���� �ȵ� �̺�");

	_objectText[13].str = (L"�� �� �ǿ�����.....");

	_objectText[14].str = (L"â���� ���.....");

	_objectText[15].str = (L"����� ������ �� ��");

	_objectText[16].str = (L"���÷��� �����ִ�,.");
	_objectText[17].str = (L"�����۹����\n  * 'Z Ű' ----- ��ȭ, ����, ����\n  * 'C Ű' ----- ���� ������ Ȯ��");

	_objectText[18].str = (L"���Թ��� ������ �ʾ�...");

	_objectText[19].str = (L"������� ������ ������ �ʾ�...");

	_objectText[20].str = (L"");

	// museum1F_1 ���
	_objectText[21].str = (L"������� '�Ը��׳�'�� ���Կ�!\n �� �������� '������ �Ը��׳� ��'��\n ??�ϰ� �ֽ��ϴ�");
	_objectText[22].str = (L"�Ը��׳��� ������ �׸� �⹦�ϰ�\n �Ƹ��ٿ� �׸��� ������ ����ּ���\n XX XX XX");
	_objectText[23].str = (L"������� ���� �� ���� ���ڰ� �ִ�...");

	_objectText[24].str = (L"���Ǿ��� ??");
	_objectText[25].str = (L"������� ���� �� ���� ���ڰ� �ִ�...");

	_objectText[26].str = (L"������ ??\n �� ����� ������ �볳ġ �ʴ� �� ���踦\n ??�ϱ� ���� ĵ���� �ȿ� ??�ߴ�");
	_objectText[27].str = (L"������� ���� �� ���� ���ڰ� �ִ�...");

	_objectText[28].str = (L"�� ��ǰ �� �ѹ� ���� �;���!");
	_objectText[29].str = (L"���� å���� ���� �Ͱ���\n ��ô �ٸ�����.. �����Ⱑ �׷�!");

	_objectText[30].str = (L"���� ������ ���Ƽ� ������...");

	_objectText[31].str = (L"�ƹ��� ����...");
	_objectText[32].str = (L"");
	_objectText[33].str = (L"");
	_objectText[34].str = (L"");
	_objectText[35].str = (L"");

	// museum1F_2 ���
	_objectText[36].str = (L"�̾�~ ���� �Ը��׳� ����!\n���� ������ ���̰� �ִ°�....");

	_objectText[37].str = (L"���� ���� �׸�...\n�̷��� ��� �ϸ� �׸� �� ������");
	_objectText[38].str = (L"");
	_objectText[39].str = (L"");
	_objectText[40].str = (L"");
	_objectText[41].str = (L"");
	_objectText[42].str = (L"");

	// museum1F_3 ���
	_objectText[43].str = (L"��ħ�ϴ� ����");

	_objectText[44].str = (L"�̰� ��¦�� ����� ��������\n�� �ٱ�κ��� �η����ų�\n������...");
	_objectText[45].str = (L"���� �׷��� �Ǹ�\n��ü �󸶳� �����ؾ��ϴ°���..\n��;� �������");
	_objectText[46].str = (L"");
	_objectText[47].str = (L"");
	_objectText[48].str = (L"");
	_objectText[49].str = (L"");

	//	museum2F_1 ���
	_objectText[50].str = (L"..........");

	_objectText[51].str = (L"�ٵ� �� ����\n�� ��Ÿ���� ������");

	_objectText[52].str = (L"'������'");
	_objectText[53].str = (L"");
	_objectText[54].str = (L"");
	_objectText[55].str = (L"");

	//	museum2F_2 ���
	_objectText[56].str = (L"�Ƹ��ٿ� ����̳�.\n�ٵ� �̰� �����ι��ΰ�?");
	_objectText[57].str = (L"�Ը��׳��� �״��� �����ι���\n�׸��� �ʾҴ��� ������ ���̾�");
	_objectText[58].str = (L"�׷��� ��¥ ���� �� ����?\n�� ���ڶ����...����ϱ�");

	_objectText[59].str = (L"���� ����");

	_objectText[60].str = (L"");
	_objectText[61].str = (L"");
	_objectText[62].str = (L"");
	_objectText[63].str = (L"");
	_objectText[64].str = (L"");

	//	museum2F_3 ���
	_objectText[65].str = (L"???�� ����");
	_objectText[66].str = (L"������� ���� �� ���� ���ڰ� �ִ�...");

	_objectText[67].str = (L".......?");

	_objectText[68].str = (L"���� �ڿ��� �Ķ� ��ü�� �귯������");

	_objectText[69].str = (L"�Ʒ��� �������� �̺�\n����� ��� �˷��ٰ�");
	_objectText[70].str = (L"");
	_objectText[71].str = (L"");
	_objectText[72].str = (L"");
	_objectText[73].str = (L"");

	//blue1
	_objectText[74].str = (L"������...");
	_objectText[75].str = (L"���ڴ� �������� �ʴ´�.");

	_objectText[76].str = (L"��.. ���Ⱑ �����?");
	_objectText[77].str = (L"�� ������? �� �̸��� �Ը���� ��\n��� �������� �ƴ�?");
	_objectText[78].str = (L"�̼������� �׸��� ���� �־��µ�\n���ڱ� ������ �Ҿ��ܴ�");
	_objectText[79].str = (L"�װ� �� Ǫ�� ��̸� ������\n������ �����");
	_objectText[80].str = (L"���� ����� ������ �ö� ���ڲٳ�");
	_objectText[81].str = (L"�������� ����� �����ٰ�?\n�׷����� �ִ�");
	_objectText[82].str = (L"� �̼������� ���ư����� ����");
	_objectText[83].str = (L"");

	//blue2
	_objectText[84].str = (L"�ɺ��� ��̲��� �����ִ�....");
	_objectText[85].str = (L"�̺�� ��̲��� ������.");
	_objectText[86].str = (L"���� ��̸� �����.");
	_objectText[87].str = (L"");
	_objectText[88].str = (L"");
	_objectText[89].str = (L"");
	_objectText[90].str = (L"");

	//blue3
	_objectText[91].str = (L"�� ��̰� ?? �� �� �״뵵 ?? �ȴ�");
	_objectText[92].str = (L"������� ���� �� ���� ���ڰ� �ִ�");

	_objectText[93].str = (L"���� ������ �ִ�...");
	_objectText[94].str = (L"�Ķ� ���踦 �����");
	_objectText[95].str = (L"");
	_objectText[96].str = (L"");

	//blue4
	_objectText[97].str = (L"�濡 ���ݱ����� ���� ������.");
	_objectText[98].str = (L"��������� ����Ǿ����ϴ�.");

	_objectText[99].str = (L"??? ������ �����");
	_objectText[100].str = (L"������� ���� �� ���� ���ڰ� �ִ�...");
	_objectText[101].str = (L"�Ķ� ���踦 ����Ͽ� ���� ������.");
	_objectText[102].str = (L"���� ����ִ°� ����.");
	_objectText[103].str = (L"");
	_objectText[104].str = (L"");

	//green1
	_objectText[105].str = (L"������� �׸��� �ɷ��ִ�");

	_objectText[106].str = (L"�� �׸��� �ɷ��ִ�");

	_objectText[107].str = (L"���� �׸��� �ɷ��ִ�");

	_objectText[108].str = (L"�Ź� �׸��� �ɷ��ִ�");

	_objectText[109].str = (L"�� ����");
	_objectText[110].str = (L"�� �׸� ���� ����");
	_objectText[111].str = (L"�� �׸� ���� ����");
	_objectText[112].str = (L"�� �׸� ���� ������\n�� �ָ� �־�");

	_objectText[113].str = (L"�׵θ��� ����");

	_objectText[114].str = (L"���� �׸��� �ɷ��ִ�...");
	_objectText[115].str = (L"....?");
	_objectText[116].str = (L"�� �׸��� ������ ��� �� ������ ����");
	_objectText[117].str = (L"���� �׸��� �����");

	_objectText[118].str = (L"�� �װ� �� �׸�");
	_objectText[119].str = (L"���� ���� ����");
	_objectText[120].str = (L"�����");

	_objectText[121].str = (L"�� �׸� ��·��");
	_objectText[122].str = (L"");
	_objectText[123].str = (L"");
	_objectText[124].str = (L"");
	_objectText[125].str = (L"");

	//green2
	_objectText[126].str = (L"���ѷα�");

	_objectText[127].str = (L"��1��");

	_objectText[128].str = (L"��2��");

	_objectText[129].str = (L"������");

	_objectText[130].str = (L"���ʷα�");

	_objectText[131].str = (L"���� �׸��� ƴ ���̿� �÷ȴ�");

	_objectText[132].str = (L"�Ӹ����� ���� �ִ�...");

	_objectText[133].str = (L"���� ������ �ִ�...");
	_objectText[134].str = (L"�Ķ� ��̸� �����");
	_objectText[135].str = (L"��3��");
	_objectText[136].str = (L"");
	_objectText[137].str = (L"");
	_objectText[138].str = (L"");
	_objectText[139].str = (L"");

	//green3
	_objectText[140].str = (L"�ٴ��� �������־� ������ �� ����...");
	_objectText[141].str = (L"���� �׸��� ƴ ���̿� �÷ȴ�");
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

	//���� ��ȭ�� �Ѿ����
	if (KEY->IsOnceKeyDown(VK_RETURN) || KEY->IsStayKeyDown('Z'))
	{
		if (GetTextEnd(_txtNum))
		{
			_txtNum++;

			if (_txtNum > OBJECTMAX - 1) _txtNum = 0;
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

void objectText::Render(HDC hdc, int x, int y)
{
	FONTMANAGER->TextRenderEnter(hdc, x, y, GetText(_txtNum), "������", RGB(255, 255, 255));
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
