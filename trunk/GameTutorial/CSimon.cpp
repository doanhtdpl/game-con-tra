#include "CSimon.h"
#include "CCamera.h"
#include "CInput.h"

CSimon::CSimon()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 56;//60.0f; //78
	this->m_height = 88;//66.0f; //84
	this->m_pos = D3DXVECTOR2(0.0f, 280.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = 0;
	this->m_canJump = true;
	this->m_jumpMax = 150.0f;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 50.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_left = false;
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 18;
	this->m_elapseTimeChangeFrame = 0.23f;
	this->m_increase = 1;
	this->m_totalFrame = 32;
	this->m_column = 6;
	this->m_endFrame = 20;
	this->m_startFrame = 18;
}

CSimon::~CSimon()
{

}

void CSimon::MoveUpdate(float deltaTime)
{
	//if (this->m_pos.x < this->m_width / 2)
	//	this->m_pos.x = this->m_width / 2;
	//Update camera
	this->m_width = 56;
	this->m_height = 88;
	this->m_column = 6;
	if((this->m_isMoveLeft || this->m_isMoveRight))
	{
		if(this->m_pos.x > 400)
		{
			if(this->m_vx * deltaTime - int(this->m_vx * deltaTime) > 0.6)
				CCamera::GetInstance()->Update(int(this->m_vx * deltaTime) + 1, 0);
			else
				CCamera::GetInstance()->Update(int(this->m_vx * deltaTime), 0);
		}
		this->m_startFrame = 18;
		this->m_endFrame = 20;
	}

	if((CInput::GetInstance()->GetKeyDown() == DIK_LEFT || CInput::GetInstance()->IsKeyDown(DIK_LEFT)) && CInput::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_left = true;
		this->m_isMoveRight = false;
		this->m_isMoveLeft = true;
		this->m_vx = -this->m_vxDefault;
		this->m_increase = 1;
		if (this->m_vx < 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}else if((CInput::GetInstance()->GetKeyDown() == DIK_RIGHT || CInput::GetInstance()->IsKeyDown(DIK_RIGHT)))
	{
		this->m_left = false;
		this->m_isMoveLeft = false;
		this->m_isMoveRight = true;
		this->m_vx = this->m_vxDefault;
		this->m_increase = 1;
		if (this->m_vx > 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}else if((CInput::GetInstance()->GetKeyDown() == DIK_DOWN || CInput::GetInstance()->IsKeyDown(DIK_DOWN)))
	{
		this->m_width = 112;
		this->m_height = 44;
		this->m_column = 3;
		this->m_increase = 1;
		this->m_startFrame = 16;
		this->m_endFrame = 16;
	}else
	{
		this->m_startFrame = 18;
		this->m_endFrame = 18;
		this->m_increase = 0;
		this->m_isMoveLeft = false;
		this->m_isMoveRight = false;
		this->m_vx = 0;
	}
}

void CSimon::ChangeFrame(float deltaTime)
{
	this->m_currentTime += deltaTime;
	if(this->m_currentTime > this->m_elapseTimeChangeFrame)
	{
		this->m_currentFrame += this->m_increase;
		if(this->m_currentFrame > this->m_endFrame || this->m_currentFrame < this->m_startFrame)
		{
			this->m_currentFrame = this->m_startFrame;
		}
		this->m_currentTime -= this->m_elapseTimeChangeFrame;
	}
}

void CSimon::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->ChangeFrame(deltaTime);
}

void CSimon::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

RECT* CSimon::GetRectRS()
{
	return this->UpdateRectResource(m_height, m_width);
}

RECT CSimon::GetRect()
{
	return RECT();
}