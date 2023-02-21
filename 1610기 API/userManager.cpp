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
	//플레이어 정보 초기화
	//SOUNDMANAGER->AddSound("blue", "sound/blue.mp3", true, true);

	_ib.img = IMAGEMANAGER->AddFrameImage("Ib", "image/Ib.bmp", 72, 132, 3, 4, true, RGB(32, 160, 0));
	_ib.rc = RectMakeCenter(CENTERX, CENTERY, _ib.img->GetFrameWidth(), _ib.img->GetFrameHeight() / 3);
	_ib.bottomCeneter.x = (_ib.rc.right + _ib.rc.left) / 2;
	_ib.bottomCeneter.y = (_ib.rc.bottom + _ib.rc.top) / 2;
	_ib.state = NOMAL;
	//만약에 객체를 새로 생성해서 이닛을 해야할경우에 이 값은 그때그때 바뀌게 된다.
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
	file = CreateFile("IB.map",	//생성할 파일 이름.
		GENERIC_WRITE,					//파일을 만들 권한.
		0,								//파일의 공유 모드 입력
		NULL,							//파일의 보안특성
		CREATE_ALWAYS,					//파일을 만들때 취할 행동
		FILE_ATTRIBUTE_NORMAL,			//파일을 만들때 갖게될 특성
		NULL);	//만들어질 파일이 갖게될  특성 및 확장 특성에 대한 정보를 가지고 있는 템플 파일 핸들을 입력?

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

	for (int i = 0; i < _vItem.size(); i++)					// 벡터에 들어가 있는 아이템 이름 출력
	{
		_vItem[i].itemImage->Render(hdc);
	}
}

tagItem* userManager::AddItem(ITEMIDX strKey, image* itemImage)	// 아이템 추가 함수
{
	tagItem* item;					// 변수 지정
	item = new tagItem;
	item->idx = strKey;				// 아이템 인덱스 지정
	item->itemImage = itemImage;

	_item.insert(make_pair(strKey, item));	// 아이템을 맵에 넣는다

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
	itemIter iter = _item.find(strKey);		// 아이템 키값을 이터레이터로 찾음

	if (iter != _item.end())
	{
		return iter->second;				// 찾은 값 반환
	}
	return NULL;
}