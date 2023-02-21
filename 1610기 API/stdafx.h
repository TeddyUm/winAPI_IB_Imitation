// stdafx.h : ���� ��������� ���� ��������� �ʴ� 
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�. 
// 


#pragma once 


//====================================================== 
// ## ������� ���ش� ## 
//====================================================== 


#include "targetver.h" 


#define WIN32_LEAN_AND_MEAN //MFC�� �ƴ� ���� ���α׷��� ��쿡�� 
//WIN32_LEAN_AND_MEAN�� ������ commdlg.h��� 
//�ʿ���� ��������� ��Ŭ��� ���� �ʰ� ���ش�. 

#include <windows.h>    //������ ������� ��Ŭ��� 
#include <stdio.h>      //���Ĵٵ� ����� ��� ��Ŭ���~ (printf, scanf ���..) 
#include <tchar.h>      //�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���~ 
						//MBCS (Multi Byte Character Set) 
						//-> ������ ����Ѵ� ��Ƽ����Ʈ ������ ���ڿ�~ 
						//WBCS (Wide Byte Character Set) 
						//-> ��� ���ڸ� 2����Ʈ�� ó��~~, �����ڵ� ���...

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "sceneManager.h"
#include "database.h"
#include "effectManager.h"
#include "soundManager.h"
#include "fontManager.h"
#include "userManager.h"


using namespace MY_UTIL;

//====================================================== 
// ## �����ι� ���ش� ## 
//====================================================== 
#define WINNAME ( LPTSTR)(TEXT ("Ib")) 
#define WINSTARTX 300 
#define WINSTARTY 20 
#define WINSIZEX 640 
#define WINSIZEY 480 
#define CENTERX (WINSIZEX / 2)
#define CENTERY (WINSIZEY / 2)
#define WINSTYLE WS_CAPTION | WS_SYSMENU 


#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)= NULL; } } 
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);  (p)= NULL; } } 
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)= NULL; } } 
#define SAFE_REL_DEL(p)			{ if(p) { (p)->Release(); delete(p); (p) = NULL;}}

//====================================================== 
// ## �̱��� ��ũ�� ���ش� ## 
//====================================================== 
#define RND randomFunction::GetSingleton()
#define KEY keyManager::GetSingleton()
#define IMAGEMANAGER imageManager::GetSingleton()
#define TIMEMANAGER timeManager::GetSingleton()
#define TXTDATA txtData::GetSingleton()
#define SCENEMANAGER sceneManager::GetSingleton()
#define DATABASE database::GetSingleton()
#define EFFECTMANAGER effectManager::GetSingleton()
#define SOUNDMANAGER soundManager::GetSingleton()
#define FONTMANAGER fontManager::GetSingleton()
#define IB userManager::GetSingleton()

//====================================================== 
// ## �������� ���ش� ## 
//====================================================== 
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern bool _leftButton;
extern bool _rightButton;