#include "CBulletF.h"
#include <math.h>
#include "CGlobal.h"
#include "CContra.h"

CBullet_F::CBullet_F()
{
	this->m_rotation = 0; //Lay sin cua goc
	this->m_left = false;
	this->m_center = D3DXVECTOR2(0.0f, 0.0f);
	this->m_offset = D3DXVECTOR2(0.0f, 0.0f);
	this->Init();
}

CBullet_F::CBullet_F(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = false;
	this->m_center = pos;
	this->m_offset = offset;
	this->Init();
	//Giu vi tri ban dau
}

CBullet_F::CBullet_F(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction)
{
	this->m_rotation = rotation; //Lay sin cua goc
	this->m_left = direction;
	this->m_center = pos;
	this->m_offset = offset;
	this->Init();
	//Giu vi tri ban dau
}

void CBullet_F::Init()
{
	//Khoi tao cac thong so cua doi tuong
	//
	this->m_angle = 0;
	this->m_id = 1;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 10.0f;//56.0f; //78
	this->m_height = 10.0f; //88.0f; //84
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_canJump = false;
	this->m_vxDefault = 200.0f;
	this->m_vyDefault = 200.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;

	//Thiet lap vi tri cua dau dan .../pos = posContra + Offset 
	//Neu con tra o tren bo
	if(!this->m_left)
	{
		this->m_center += this->m_offset; //Vi tri cua vien dan
		this->m_center.x += 15.0f;
	}
	else
	{
		//Neu la ban len
		if(this->m_rotation == PI/2)
		{
			this->m_center.x += 35.0f;
		}
		this->m_center.y += this->m_offset.y;
	}
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
}

void CBullet_F::MoveUpdate(float deltaTime)
{
#pragma region __XET_TRANG_THAI_DAN__
	
	//this->m_vx = (this->m_vxDefault * cos(this->m_angle + PI + 1) + this->m_angle * 12);
	//this->m_vy = (this->m_vyDefault * sin(this->m_angle + PI));
	//this->m_pos.x += this->m_vx * deltaTime;
	//this->m_pos.y += this->m_vy * deltaTime;

	//Dung ban tra sin-cos
	this->m_angle -= 0.45f;
	this->m_pos.x = 30 * (cos(this->m_angle - PI)) + this->m_center.x;
	this->m_pos.y = (30 * (sin(this->m_angle - PI)) + this->m_center.y);

	//if(m_vx != 0) 
	//{
	//	if(this->m_vx > 0)
	//	{
	//		this->m_vx += this->m_a * deltaTime;
	//	}
	//	else
	//	{
	//		this->m_vx -= this->m_a * deltaTime;
	//	}
	//}
	//if(m_vy != 0)
	//{
	//	if(this->m_vy > 0)
	//	{
	//		this->m_vy += this->m_a * deltaTime;
	//	}
	//	else
	//	{
	//		this->m_vy -= this->m_a * deltaTime;
	//	}
	//}
	this->m_center.x += this->m_vx * deltaTime;
	this->m_center.y += this->m_vy * deltaTime;

	//this->m_angle += 0.01;

#pragma endregion
}
void CBullet_F::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
}

void CBullet_F::Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision)
{

}

void CBullet_F::OnCollision(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

RECT* CBullet_F::GetRectRS()
{
	RECT* rs = new RECT();
	rs->left = 0;
	rs->right = this->m_width;
	rs->top = 0;
	rs->bottom = this->m_height;
	return rs;
}

RECT* CBullet_F::GetBound()
{
	return nullptr;
}

Box CBullet_F::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}

CBullet_F::~CBullet_F()
{

}