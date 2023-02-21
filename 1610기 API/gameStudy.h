#pragma once

#include "gameNode.h"
#include "mainMenu.h"
#include "museumS.h"
#include "opening.h"
#include "museum1F_1.h"
#include "museum1F_2.h"
#include "museum1F_3.h"
#include "museum2F_1.h"
#include "museum2F_2.h"
#include "museum2F_3.h"
#include "blue1.h"
#include "blue2.h"
#include "blue3.h"
#include "blue4.h"
#include "green1.h"
#include "green2.h"
#include "green3.h"
#include "ending.h"
#include "gameOver.h"

class gameStudy : public gameNode
{
private:

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render( void );

};
