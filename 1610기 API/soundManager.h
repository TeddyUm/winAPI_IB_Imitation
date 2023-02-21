//#pragma once
//#include "singletonBase.h"
//
//#include <map>
//#include <string>
//
////fmod.hpp �߰�
//#include "inc/fmod.hpp"
//
////lib ��ũ
//#pragma comment (lib, "lib/fmodex_vc.lib")
//
////�������� ä�� ���� ����(����)
//#define EXTRA_SOUND_CHANNEL 10
//#define SOUNDBUFFER 1000
//
////�� ���� ����
//#define TOTAL_SOUND_CHANNEL SOUNDBUFFER + EXTRA_SOUND_CHANNEL
//
//using namespace FMOD;
//
//class soundManager : public singletonBase <soundManager>
//{
//private:
//	typedef map<string, Sound**> arrSounds;
//	typedef map<string, Sound**>::iterator arrSoundsIter;
//	typedef map<string, Channel**> arrChannels;
//	typedef map<string, Channel**>::iterator arrChannelIter;
//
//private:
//	System* _system;
//	Sound** _sound;
//
//	Channel** _channel;
//
//	arrSounds _mTotalSounds;
//
//
//public:
//	HRESULT Init(void);
//	void Release(void);
//
//	//���� �߰�
//	void AddSound(string keyName, string soundName, bool background = false, bool loop = false);
//
//	//���
//	void Play(string keyName, float volume);
//
//	//����
//	void Stop(string keyName);
//
//	//����
//	void Pause(string keyName);
//
//	//�ٽ� ���
//	void Resume(string keyName);
//
//	//�����ִ�?
//	bool IsPauseSound(string keyName);
//
//	//������̴�?
//	bool IsPlaySound(string keyName);
//
//	//Fmod �ý����� ����
//	void Update(void);
//
//	float GetFrequency(string keyName);
//	void SetFrequency(string keyName, float freq);
//
//	soundManager();
//	~soundManager();
//};