#include "CMenuGame.h"
#include "CInput.h"
#include "CStateGamePlay.h"
#include "CStateManagement.h"

int CMenuGame::m_mapId = 11;

CMenuGame::CMenuGame(void)
{
	this->Init();
}

CMenuGame::CMenuGame(const std::vector<int>& info)
{
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
	this->Init();//
}

void CMenuGame::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 1;
	this->m_idType = 60;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 512.0f;
	this->m_height = 448.0f;
	//Khoi tao cac thong so di chuyen
	this->m_left = false;
	//
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 1.3f;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.40f;
	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
	this->m_startFrame = 0;
	this->m_endFrame = 1;
	//
	this->m_timeDelay = 3.0f;
}

void CMenuGame::Update(float deltaTime)
{
	this->ChangeFrame(deltaTime);
	this->Move(deltaTime);
}

void CMenuGame::Move(float deltaTime)
{
	if (this->m_pos.x > this->m_width/2)
	{
		this->m_pos.x -= 2;
	}
	else
	{
		if (CInput::GetInstance()->GetKeyDown() == DIK_RETURN)
		{
			CStateManagement::GetInstance()->ChangeState(new CStateGamePlay(this->m_mapId));
		}
		else
		if (CInput::GetInstance()->GetKeyDown() == DIK_ESCAPE)
		{
			//Exit game
			std::exit(1);
		}
	}
}

RECT* CMenuGame::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

CMenuGame::~CMenuGame()
{

}