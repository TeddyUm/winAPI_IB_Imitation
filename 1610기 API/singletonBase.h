#pragma once

template<typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	//����0. static ������ Ư¡
	//����1. Ŭ������ static ��� ������ Ư¡
	//����2. Ŭ������ static ��� �Լ��� Ư¡

	singletonBase( void ) {}
	~singletonBase( void ) {}

public:
	static T* GetSingleton( void );
	void ReleaseSingleton( void );

};

//�̱��� �ʱ�ȭ
template<typename T>
T* singletonBase<T>::singleton = 0;

//�̱��� �� ��������
template<typename T>
T* singletonBase<T>::GetSingleton()
{
	if ( singleton ) return singleton;
	else return singleton = new T;
}

//�̱��� �޸� ����
template<typename T>
void singletonBase<T>::ReleaseSingleton()
{
	if ( singleton )
	{
		delete singleton;
		singleton = 0;
	}
}