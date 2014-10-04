#include "CContra.h"

CContra::CContra()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 78.0f;
	this->m_height = 84.0f;
	this->m_pos = D3DXVECTOR2(0.0f, 400.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = 0;
	this->m_canJump = true;
	this->m_jumpMax = 150.0f;
	this->m_vxDefault = 30.0f;
	this->m_vyDefault = 50.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.2f;
	this->m_increase = 1;
	this->m_totalFrame = 28;
	this->m_column = 11;
}

CContra::~CContra()
{

}

void CContra::MoveUpdate(float deltaTime)
{
	if(this->m_pos.x > __SCREEN_WIDTH)
	{
		this->m_pos.x = 0;
	}

	if (this->m_pos.x < this->m_width / 2)
		this->m_pos.x = this->m_width / 2;

	if (this->m_isMoveLeft)
	{
		if (this->m_vx < 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}

	if (this->m_isMoveRight)
	{
		if (this->m_vx > 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}

}

void CContra::ChangeFrame(float deltaTime)
{
	this->m_currentTime += deltaTime;
	if(this->m_currentTime > this->m_elapseTimeChangeFrame)
	{
		this->m_currentFrame += this->m_increase;
		if(this->m_currentFrame > 4)
		{
			this->m_currentFrame = 0;
		}
		this->m_currentTime -= this->m_elapseTimeChangeFrame;
	}
}

void CContra::Update(float deltaTime)
{
	this->ChangeFrame(deltaTime);
	this->MoveUpdate(deltaTime);
}

void CContra::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

RECT* CContra::GetRectRS()
{
	return this->UpdateRectResource(m_height, m_width);
}

RECT CContra::GetRect()
{
	return RECT();
}