#include "CMenuGame.h"
#include "CInput.h"
#include "CStateGamePlay.h"
#include "CStateManagement.h"
#include "CDrawObject.h"
#include "CLoadBackGround.h"
#include "CLoadGameObject.h"

int CMenuGame::m_mapId = 12;

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
	this->m_timeDelay = 2.0f;
	//
	this->m_itemChoose = new CChooseItem();
	//
	this->m_isMoveComplete = false;
	this->m_isChoosePlay = false;
	this->m_isCanShowScoreScense = false;
}

void CMenuGame::Update(float deltaTime)
{
	//this->ChangeFrame(deltaTime);
	this->Move(deltaTime);	
	if (this->m_isChoosePlay)
	{
		if (this->m_timeDelay <= 0 && !this->m_isCanShowScoreScense)
		{
			this->m_isCanShowScoreScense = true;
			this->m_timeDelay = 2.0f;
			//
			this->m_startFrame = 2;
			this->m_currentFrame = 2;
			this->m_endFrame = 2;
		}
		else
		if (!this->m_isCanShowScoreScense)
			this->m_timeDelay -= deltaTime;
		//Update cho man hinh Score ban dau
		if (this->m_isCanShowScoreScense)
		{
			this->m_scoreScense->Update(deltaTime);
			if (this->m_timeDelay <= 0)
			{
				this->m_timeDelay = 2.0f;
				CStateManagement::GetInstance()->ChangeState(new CStateGamePlay(this->m_mapId));
				delete this->m_scoreScense;//co the bo
				this->m_isCanShowScoreScense = false;//node co the bo
			}
			this->m_timeDelay -= deltaTime;
		}
			
	}
}

void CMenuGame::Move(float deltaTime)
{
	if (this->m_pos.x > this->m_width/2)
	{
		this->m_pos.x -= 2;
	}
	else
	{
		this->m_isMoveComplete = true;
		//
		if (!this->m_isChoosePlay){
			if (CInput::GetInstance()->IsKeyDown(DIK_RETURN))
			{
				if (this->m_itemChoose->m_SelectedId == 0)
				{
					CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
					CLoadGameObject::GetInstance()->LoadReSourceFromFile();
					//
					this->m_isChoosePlay = true;
					//Tao moi man hinh score
					this->m_scoreScense = new CScoreScense(false);
				}
				//CStateManagement::GetInstance()->ChangeState(new CStateGamePlay(this->m_mapId));
			}
			else
			if (CInput::GetInstance()->IsKeyDown(DIK_ESCAPE))
			{
				//Exit game
				std::exit(1);
			}
			else
			if (CInput::GetInstance()->IsKeyDown(DIK_UP))
			{
				this->m_itemChoose->m_SelectedId--;
				if (this->m_itemChoose->m_SelectedId < 0)
				{
					this->m_itemChoose->m_SelectedId = 0;
				}

			}
			else
			if (CInput::GetInstance()->IsKeyDown(DIK_DOWN))
			{
				this->m_itemChoose->m_SelectedId++;
				if (this->m_itemChoose->m_SelectedId > 0)
				{
					this->m_itemChoose->m_SelectedId = 1;
				}
			}
			else
			if (CInput::GetInstance()->IsKeyDown(DIK_F1))
			{
				this->m_startFrame = 1;
				this->m_currentFrame = 1;
				this->m_endFrame = 1;
			}
		}
	}
}

void CMenuGame::Draw()
{
	CDrawObject::GetInstance()->Draw(this);
	////
	///Ve 
	if (!this->m_isCanShowScoreScense)
	{
		D3DXVECTOR2 pos;
		if (this->m_itemChoose->m_SelectedId == 0)
			pos = D3DXVECTOR2(this->GetPos().x - 165, this->GetPos().y - 85);
		else
			pos = D3DXVECTOR2(this->GetPos().x - 165, this->GetPos().y - 115);
		this->m_itemChoose->SetPos(pos);
		CDrawObject::GetInstance()->Draw(this->m_itemChoose);
	}
	else
	if (this->m_isChoosePlay)
	{
		this->m_scoreScense->SetPos(this->m_pos);
		this->m_scoreScense->InitScore(0);
		this->m_scoreScense->InitHightScore(20000);
		if (!this->m_scoreScense->IsScenseGameOver())//neu la man hinh diem thi hien thi
		{
			this->m_scoreScense->InitNameStage(CMenuGame::m_mapId);
			this->m_scoreScense->InitCountAlive(CContra::GetInstance()->m_countAlive);
			this->m_scoreScense->InitStageNumber(CMenuGame::m_mapId);
		}
		this->m_scoreScense->Draw();
	}
}

RECT* CMenuGame::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

CMenuGame::~CMenuGame()
{

}