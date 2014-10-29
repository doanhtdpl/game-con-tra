#include "CBulletN.h"

/**		
/	Class CBullet:
/		+ Chua set chuyen frame
/
*/
CBullet_N::CBullet_N() : CBullet()
{
	this->m_rotation = 0; //Lay sin cua goc
	this->m_left = false;
	this->m_pos = D3DXVECTOR2(0.0f, 0.0f);
	this->m_offset = D3DXVECTOR2(0.0f, 0.0f);
	this->Init();
}

CBullet_N::CBullet_N(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = false;
	this->m_pos = pos;
	this->m_offset = offset;
	this->Init();
}

CBullet_N::CBullet_N(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = direction;
	this->m_pos = pos;
	this->m_offset = offset;
	this->Init();
}

void CBullet_N::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = false;
	this->m_width = 18.0f;//56.0f; //78
	this->m_height = 18.0f; //88.0f; //84
	//Khoi tao cac thong so di chuyen
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_canJump = false;
	this->m_vxDefault = 200.0f;
	this->m_vyDefault = 200.0f;
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
		this->m_pos.x -= this->m_offset.x;
		if(this->m_rotation == PI/2)
		{
			this->m_pos.x += 20.0f;
		}
		this->m_pos.y += this->m_offset.y;
	}
}

void CBullet_N::MoveUpdate(float deltaTime)
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

void CBullet_N::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
}

void CBullet_N::Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision)
{

}

RECT* CBullet_N::GetRectRS()
{
	return nullptr;
}

RECT* CBullet_N::GetBound()
{
	return nullptr;
}

Box CBullet_N::GetBox()
{
	return Box();
}

CBullet_N::~CBullet_N()
{

}