#pragma once
#include "singletonBase.h"

enum IBState
{
	NOMAL, HIT, EVENT
};

enum ITEMIDX
{
	HANKIE,
	REDROSE,
	BLUEKEY,
	ANTPICTURE,
	BLUEROSE,
	TEST
};

struct tagIb
{
	image* img;
	RECT rc;
	POINT bottomCeneter;
	IBState state;
	int maxHp;
	int currentHp;
	int spd;
	int frameX;
	int frameY;
	char saveScene[50];
};

struct tagItem	// 아이템 데이터 구조체
{
	ITEMIDX idx;
	image* itemImage;	// 아이템 이름
};

struct stFlags
{
	bool _start;
	bool _anotherWorld;
	bool _anotherCheck;
	bool _underWorld;
	bool _savePoint;
	bool _redRose;
	bool _blueKey;
	bool _blueDoor;
	bool _antPicture;
	bool _useAntPicture;
	bool _blueRose;
	bool _end;
	int _antPictureEvent;
};

class userManager : public singletonBase<userManager>
{
private:
	tagIb _ib;

	int _nextX;
	int _nextY;

	stFlags _flags;

	image* _itemHankie;
	image* _itemRedRose;
	image* _itemBlueKey;
	image* _itemAntPicture;
	image* _itemBlueRose;
	image* _itemTest;

	typedef map<ITEMIDX, tagItem*> itemList;			// 맵
	typedef map<ITEMIDX, tagItem*>::iterator itemIter;	// 맵 이터레이터
	itemList _item;

	vector<tagItem> _vItem;								// 현재 소지한 아이템 벡터
	vector<tagItem>::iterator _viItem;					// 아이템 벡터 이터레이터

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void ibMove();
	void ibHp();

	void Save();
	void Load();

	void Inventory(HDC hdc);	
	tagItem* userManager::AddItem(ITEMIDX strKey, image* itemImage);
	void AddInvenItem(ITEMIDX strKey);			
	void DeleteInvenItem(ITEMIDX strKey);		
	tagItem* FindItem(ITEMIDX strKey);

	IBState GetIbState() { return _ib.state; }
	void SetIbState(IBState state) { _ib.state = state; } //NOMAL, FALLING, EVENT 3가지중 하나를 설정한다.

	RECT GetIbRect() { return _ib.rc; } //플레이어 렉트 불러오기
	void SetIbRect(int left, int top, int right, int bottom) { _ib.rc.left = left; _ib.rc.top = top; _ib.rc.right = right, _ib.rc.bottom = bottom; } //플레이어 렉트 재설정

	POINT GetIbBottomPoint() { return _ib.bottomCeneter; }	//플레이어 하단 중앙 포인트 불러오기

	int GetIbMaxHp() { return _ib.maxHp; }					//플레이어 맥스 체력 불러오기
	void SetIbMaxHp(int hp) { _ib.maxHp = hp; }

	int GetIbCurrentHp() { return _ib.currentHp; }			//플레이어 현재체력 불러오기
	void SetIbCurrentHp(int hp) { _ib.currentHp = hp; }		//플레이어 현재 체력 설정

	char* GetSaveScene() { return _ib.saveScene; }
	void SetSaveScene(char* sceneName)
	{
		strncpy_s(_ib.saveScene, sceneName, strlen(sceneName));
	}

	int GetNextX() { return _nextX; }
	int GetNextY() { return _nextY; }
	void SetNextPos(int x, int y) { _nextX = x; _nextY = y; }

	stFlags GetFlags() { return _flags; }
	void SetFlags(stFlags stflag) { _flags = stflag; }

	userManager();
	~userManager();
};

