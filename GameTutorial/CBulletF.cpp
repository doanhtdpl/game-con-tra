#include "CBulletF.h"
#include <math.h>
#include "CGlobal.h"
#include "CContra.h"

CBullet_F::CBullet_F()
{
	//Khoi tao cac thong so cua doi tuong
	//
	this->m_angle = 0;

	this->m_id = 0;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 10.0f;//56.0f; //78
	this->m_height = 10.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(55.0f, 300.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_canJump = false;
	this->m_jumpMax = 40.0f;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 400.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_pos = this->m_posStart;
	//this->m_rotation = 0;
	this->InitPosition();
}

CBullet_F::CBullet_F(double rotation)
{
	//Khoi tao cac thong so cua doi tuong
	//
	this->m_angle = 0;

	this->m_id = 0;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 10.0f;//56.0f; //78
	this->m_height = 10.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(55.0f, 300.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_canJump = false;
	this->m_jumpMax = 40.0f;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 100.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_pos = this->m_posStart;

	this->m_rotation = rotation;
	this->InitPosition();
	//Giu vi tri ban dau
}

void CBullet_F::InitPosition()
{
	//Vi tri cua dau dan
	this->m_pos = CContra::GetInstance()->GetPos();
	//Huong cua vien dan cung huong voi contra
	this->m_left = CContra::GetInstance()->GetDirection(); 
	//if(!this->m_left)
	//{
	//	this->m_vx = this->m_vxDefault;
	//	this->m_a = 50;
	//}
	//else
	//{
	//	this->m_vx = -this->m_vxDefault;
	//	this->m_a = -50;
	//}
	//Thiet lap huong ban cua dau dan
	this->m_shootState = CContra::GetInstance()->GetShootState();
	//Thiet lap vi tri cua dau dan .../pos = posContra + Offset 
	//Neu con tra o tren bo
	if(!CContra::GetInstance()->GetLocation())
	{
		switch(CContra::GetInstance()->GetStateCurrent())
		{
		case ON_GROUND::IS_LYING:
			{
				this->m_offset.x = 19.0f;
				this->m_offset.y = -20.0f;
				break;
			}
		case ON_GROUND::IS_FALL: case ON_GROUND::IS_JOGGING : case ON_GROUND::IS_SHOOTING_NORMAL: case ON_GROUND::IS_STANDING:
			{
				this->m_offset.x = 32.0f;
				this->m_offset.y = 8.0f;
				break;
			}
		case ON_GROUND::IS_SHOOTING_UP:
			{
				this->m_offset.x = -4.0f;
				this->m_offset.y = 50.0f;
				break;
			}
		case ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN:
			{
				this->m_offset.x = 14.5f;
				this->m_offset.y = -10.0f;
				break;
			}
		case ON_GROUND::IS_SHOOTING_DIAGONAL_UP:
			{
				this->m_offset.x = 14.5f;
				this->m_offset.y = 25.0f;
				break;
			}
		case ON_GROUND::IS_JUMPING:
			{
				this->m_offset.x = 14.5f;
				this->m_offset.y = 20.0f;
				break;
			}
		}
		if(!this->m_left)
		{
			this->m_pos += this->m_offset; //Vi tri cua vien dan
		}
		else
		{
			this->m_pos.x -= (this->m_offset.x + CContra::GetInstance()->GetWidth()/4); //Vi tri cua vien dan
			this->m_pos.y += this->m_offset.y;
		}
		this->m_posStart = this->m_pos;
		this->m_center.x = this->m_pos.x + 10;
		this->m_center.y = this->m_pos.y;
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

	//
	this->m_angle -= 0.45f;
	this->m_pos.x = 30 * (cos(this->m_angle - PI)) + this->m_center.x;
	this->m_pos.y = (30 * (sin(this->m_angle - PI)) + this->m_center.y);

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
	this->m_center.x += this->m_vx * deltaTime;
	this->m_center.y += this->m_vy * deltaTime;
	//this->m_pos.x += this->m_vx * deltaTime;
	//this->m_pos.y += this->m_vy * deltaTime;

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

RECT* CBullet_F::GetRectRS()
{
	return nullptr;
}

RECT CBullet_F::GetRect()
{
	return RECT();
}

CBullet_F::~CBullet_F()
{

}