#include "stdafx.h"
#include "userManager.h"


userManager::userManager()
{
}


userManager::~userManager()
{
}

HRESULT userManager::Init()
{
	//�÷��̾� ���� �ʱ�ȭ
	//SOUNDMANAGER->AddSound("blue", "sound/blue.mp3", true, true);

	_ib.img = IMAGEMANAGER->AddFrameImage("Ib", "image/Ib.bmp", 72, 132, 3, 4, true, RGB(32, 160, 0));
	_ib.rc = RectMakeCenter(CENTERX, CENTERY, _ib.img->GetFrameWidth(), _ib.img->GetFrameHeight() / 3);
	_ib.bottomCeneter.x = (_ib.rc.right + _ib.rc.left) / 2;
	_ib.bottomCeneter.y = (_ib.rc.bottom + _ib.rc.top) / 2;
	_ib.state = NOMAL;
	//���࿡ ��ü�� ���� �����ؼ� �̴��� �ؾ��Ұ�쿡 �� ���� �׶��׶� �ٲ�� �ȴ�.
	_ib.maxHp = 5;
	_ib.currentHp = 3;
	_ib.spd = 10;
	_ib.frameX = 0;
	_ib.frameY = 0;

	_nextX = 200;
	_nextY = 400;

	ZeroMemory(&_flags, sizeof(stFlags));

	return S_OK;
}
void userManager::Release()
{

}
void userManager::Update()
{

}
void userManager::Render(HDC hdc)
{
	//RectDraw(hdc, _ib.rc);
	//_ib.img->FrameRender(hdc, _ib.rc.left, _ib.rc.bottom - _ib.img->GetFrameHeight(), _ib.frameX, _ib.frameY);
}

void userManager::ibMove()
{
	if (KEY->IsStayKeyDown(VK_LEFT))
	{
		_ib.rc.left -= _ib.spd;
		_ib.rc.right -= _ib.spd;

		_ib.frameY = 3;
		_ib.frameX++;
		if (_ib.frameX > 3)
		{
			_ib.frameX = 0;
		}
	}
	if (KEY->IsStayKeyDown(VK_RIGHT))
	{
		_ib.frameY = 1;
		_ib.rc.right += _ib.spd;
		_ib.rc.left += _ib.spd;

		_ib.frameX++;
		if (_ib.frameX > 3)
		{
			_ib.frameX = 0;
		}
	}
	if (KEY->IsStayKeyDown(VK_UP))
	{
		_ib.frameY = 0;
		_ib.rc.bottom -= _ib.spd;
		_ib.rc.top -= _ib.spd;

		_ib.frameX++;
		if (_ib.frameX > 3)
		{
			_ib.frameX = 0;
		}
	}
	if (KEY->IsStayKeyDown(VK_DOWN))
	{
		_ib.frameY = 2;
		_ib.rc.top += _ib.spd;
		_ib.rc.bottom += _ib.spd;

		_ib.frameX++;
		if (_ib.frameX > 3)
		{
			_ib.frameX = 0;
		}
	}
}

void userManager::ibHp()
{

}

void userManager::Save()
{
	HANDLE file;
	DWORD write;
	file = CreateFile("IB.map",	//������ ���� �̸�.
		GENERIC_WRITE,					//������ ���� ����.
		0,								//������ ���� ��� �Է�
		NULL,							//������ ����Ư��
		CREATE_ALWAYS,					//������ ���鶧 ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,			//������ ���鶧 ���Ե� Ư��
		NULL);	//������� ������ ���Ե�  Ư�� �� Ȯ�� Ư���� ���� ������ ������ �ִ� ���� ���� �ڵ��� �Է�?

	WriteFile(file, &_ib, sizeof(_ib), &write, NULL);
	WriteFile(file, &_flags, sizeof(_flags), &write, NULL);

	CloseHandle(file);
}

void userManager::Load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("IB.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_ib, sizeof(_ib), &read, NULL);
	ReadFile(file, &_flags, sizeof(_flags), &read, NULL);

	CloseHandle(file);

	//SOUNDMANAGER->Play("blue", 1.f);
}

void userManager::Inventory(HDC hdc)
{
	_itemHankie = IMAGEMANAGER->AddImage("hankie", "image/item/item_01.bmp", 290, 100, 300, 80, false, false);
	_itemRedRose = IMAGEMANAGER->AddImage("redRose", "image/item/item_02.bmp", 290, 180, 300, 80, false, false);
	_itemBlueKey = IMAGEMANAGER->AddImage("blueKey", "image/item/item_03.bmp", 290, 260, 300, 80, false, false);
	_itemAntPicture = IMAGEMANAGER->AddImage("antPicture", "image/item/item_04.bmp", 290, 260, 300, 80, false, false);
	_itemBlueRose = IMAGEMANAGER->AddImage("blueRoseT", "image/item/item_05.bmp", 290, 260, 300, 80, false, false);

	AddItem(HANKIE, _itemHankie);
	AddItem(REDROSE, _itemRedRose);
	AddItem(ANTPICTURE, _itemAntPicture);
	AddItem(BLUEKEY, _itemBlueKey);
	AddItem(BLUEROSE, _itemBlueRose);

	AddInvenItem(HANKIE);
	if (IB->GetFlags()._redRose == true)
	{
		IB->AddInvenItem(REDROSE);
	}
	if (IB->GetFlags()._blueKey == true)
	{
		IB->AddInvenItem(BLUEKEY);
	}
	if (IB->GetFlags()._antPicture == true)
	{
		IB->AddInvenItem(ANTPICTURE);
	}
	if (IB->GetFlags()._blueRose == true)
	{
		IB->AddInvenItem(BLUEROSE);
	}

	for (int i = 0; i < _vItem.size(); i++)					// ���Ϳ� �� �ִ� ������ �̸� ���
	{
		_vItem[i].itemImage->Render(hdc);
	}
}

tagItem* userManager::AddItem(ITEMIDX strKey, image* itemImage)	// ������ �߰� �Լ�
{
	tagItem* item;					// ���� ����
	item = new tagItem;
	item->idx = strKey;				// ������ �ε��� ����
	item->itemImage = itemImage;

	_item.insert(make_pair(strKey, item));	// �������� �ʿ� �ִ´�

	return item;
}

void userManager::AddInvenItem(ITEMIDX strKey)
{
	tagItem* item;
	ZeroMemory(&item, sizeof(tagItem*));
	item = FindItem(strKey);
	_vItem.push_back(*item);
}
void userManager::DeleteInvenItem(ITEMIDX strKey)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); )
	{
		if (_viItem->idx == FindItem(strKey)->idx)
		{
			_viItem = _vItem.erase(_viItem);
			break;
		}
		else
			++_viItem;
	}
}
tagItem* userManager::FindItem(ITEMIDX strKey)
{
	itemIter iter = _item.find(strKey);		// ������ Ű���� ���ͷ����ͷ� ã��

	if (iter != _item.end())
	{
		return iter->second;				// ã�� �� ��ȯ
	}
	return NULL;
}