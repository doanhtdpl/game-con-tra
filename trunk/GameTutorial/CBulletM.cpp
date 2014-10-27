#include "CBulletM.h"

/**		
/	Class CBullet:
/		+ Chua set chuyen frame
/
*/
CBullet_M::CBullet_M() : CBullet()
{
	this->m_rotation = 0; //Lay sin cua goc
	this->m_left = false;
	this->m_pos = D3DXVECTOR2(0.0f, 0.0f);
	this->m_offset = D3DXVECTOR2(0.0f, 0.0f);
	this->Init();
}

CBullet_M::CBullet_M(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = false;
	this->m_pos = pos;
	this->m_offset = offset;
	this->Init();
}

CBullet_M::CBullet_M(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = direction;
	this->m_pos = pos;
	this->m_offset = offset;
	this->Init();
}

void CBullet_M::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 1;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 18.0f;
	this->m_height = 18.0f;
	//Khoi tao cac thong so di chuyen
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_canJump = false;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 400.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_pos = D3DXVECTOR2(0.0f,0.0f);
	//Chuyen doi sprite
	this->m_totalFrame= 3;
	this->m_column = 3;
	this->m_elapseTimeChangeFrame = 0.35f;
	this->m_currentTime = 0;
	this->m_increase = 1;
	this->m_currentFrame = 0;
	if(!this->m_left)
	{
		//this->m_vx = this->m_vxDefault;
		//this->m_a = 1000;
		this->m_vx = this->m_vxDefault * cos(this->m_rotation);
		this->m_vy = this->m_vyDefault * sin(this->m_rotation);
	}
	else
	{
		//this->m_vx = -this->m_vxDefault;
		//this->m_a = 1000;
		this->m_vx = -this->m_vxDefault * cos(this->m_rotation);
		this->m_vy = this->m_vyDefault * sin(this->m_rotation);
	}
	
	if(!this->m_left)
	{
		this->m_pos += this->m_offset; //Vi tri cua vien dan
	}
	else
	{
		//Neu la ban len
		if(this->m_rotation == PI/2)
		{
			this->m_pos.x += 20.0f;
		}
		this->m_pos.y += this->m_offset.y;
	}
}

void CBullet_M::MoveUpdate(float deltaTime)
{
#pragma region __SET_TOA_DO_DAN__

	if(m_vx != 0) 
	{
		if(this->m_vx > 0)
		{
			this->m_vx += this->m_a * deltaTime;
		}
		else
		{
			this->m_vx -= this->m_a * deltaTime;
		}
	}
	if(m_vy != 0)
	{
		if(this->m_vy > 0)
		{
			this->m_vy += this->m_a * deltaTime;
		}
		else
		{
			this->m_vy -= this->m_a * deltaTime;
		}
	}
	this->m_pos.x += this->m_vx * deltaTime;
	this->m_pos.y += this->m_vy * deltaTime;


#pragma endregion

}

void CBullet_M::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->ChangeFrame(deltaTime);
}

void CBullet_M::Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision)
{

}

void CBullet_M::ChangeFrame(float deltaTime)
{
	this->m_currentTime += deltaTime;
	if(this->m_currentTime > this->m_elapseTimeChangeFrame)
	{
		this->m_currentFrame += this->m_increase;
		if(this->m_currentFrame > 3 || this->m_currentFrame < 0)
		{
			this->m_currentFrame = 0;
		}
		this->m_currentTime -= this->m_elapseTimeChangeFrame;
	}
}


RECT* CBullet_M::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

RECT* CBullet_M::GetBound()
{
	return nullptr;
}

Box CBullet_M::GetBox()
{
	return Box();
}

CBullet_M::~CBullet_M()
{

}