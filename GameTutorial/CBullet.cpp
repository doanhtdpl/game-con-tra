#include "CBullet.h"
#include <math.h>
#include "CGlobal.h"
#include "CContra.h"

/**		
/	Class CBullet:
/		+ Chua set chuyen frame
/
*/
CBullet::CBullet() : CDynamicObject()
{
	//Khoi tao cac thong so cua doi tuong
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
	this->InitPosotion();
	
}

void CBullet::InitPosotion()
{
	//Vi tri cua dau dan
	this->m_pos = CContra::GetInstance()->GetPos();
	//Huong cua vien dan cung huong voi contra
	this->m_left = CContra::GetInstance()->m_left; 
	if(!this->m_left)
	{
		this->m_vx = this->m_vxDefault;
		this->m_a = 1000;
	}
	else
	{
		this->m_vx = -this->m_vxDefault;
		this->m_a = -1000;
	}
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
				this->m_offset.x = 14.5f;
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
			this->m_pos.x -= (this->m_offset.x + CContra::GetInstance()->m_width/4); //Vi tri cua vien dan
			this->m_pos.y += this->m_offset.y;
		}
	}
}

void CBullet::MoveUpdate(float deltaTime)
{
#pragma region __XET_TRANG_THAI_DAN__
	float rotation = 0;
	//this->m_posStart.y = CContra::GetInstance()->GetPos().y + 10;
		switch (this->m_shootState)
		{
		case SHOOT::IS_NORMAL:
			{
				rotation = 1; //Goc ban bang 0
				break;
			}
		case SHOOT::IS_UP:
			{
				rotation = 0; //Goc ban bang 90
				break;
			}
		case SHOOT::IS_DOWN:
			{
				rotation = -1;
				break;
			}
		case SHOOT::IS_DIAGONAL_UP:
			{ 
				rotation = sqrt(2) /2; //Goc ban bang 45
				break;
			}
		case SHOOT::IS_DIAGONAL_DOWN:
			{
				//this->m_a = -700;
				//this->m_vy = -400.0f;
				rotation = -sqrt(2) /2; // //Goc ban bang -45
				break;
			}
		default:
			{
				rotation = 0;
				break;
			}
		}
#pragma endregion

#pragma region __SET_TOA_DO_DAN__

	//if(rotation > -2)
	//{
	//	this->m_vy += this->m_a * deltaTime;
	//	this->m_pos.y += (rotation) * this->m_vy * deltaTime;
	//	this->m_pos.x += this->m_vy * deltaTime;
	//		//(std::sqrt(1 - rotation*rotation)/rotation)*(this->m_pos.y - this->m_posStart.y) ;
	//}
	//else if(rotation == -3)
	//{
	//	this->m_vx += this->m_a * deltaTime;
	//	this->m_pos.x += this->m_vx * deltaTime;
	//}
	//else if(rotation == -2)
	//{
	//	this->m_vy += this->m_a * deltaTime;
	//	this->m_pos.y += this->m_vy * deltaTime;
	//}
	float posXOld = this->m_pos.x;
	this->m_vx += this->m_a * deltaTime;
	if(!this->m_left)
	{
		if(rotation > 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
			this->m_pos.y += (1 - rotation*rotation)/(rotation*rotation) * (this->m_pos.x - posXOld);
		}
		else if(rotation < 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
			this->m_pos.y -= (1 - rotation*rotation)/(rotation*rotation) * (this->m_pos.x - posXOld);
		}
		else
		{
			this->m_pos.y += this->m_vy * deltaTime;
		}
	}
	else
	{
		if(rotation > 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
			this->m_pos.y -= (1 - rotation*rotation)/(rotation*rotation) * (this->m_pos.x - posXOld);
		}
		else if(rotation < 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
			this->m_pos.y += (1 - rotation*rotation)/(rotation*rotation) * (this->m_pos.x - posXOld);
		}
		else
		{
			this->m_pos.y += this->m_vy * deltaTime;
		}
	}

#pragma endregion

	//if(CContra::GetInstance()->m_left)
	//{
	//	this->m_isMoveLeft = true;
	//	this->m_isMoveRight = false;
	//}
	//else
	//{
	//	this->m_isMoveLeft = false;
	//	this->m_isMoveRight = true;
	//}

	//if(this->m_isMoveLeft)
	//{
	//	if(this->m_vx < 0)
	//	{
	//		this->m_pos.x += this->m_vx * deltaTime;
	//	}
	//}
	//else if(this->m_isMoveRight)
	//{
	//	if(this->m_vx > 0)
	//	{
	//		this->m_pos.x += this->m_vx * deltaTime;
	//	}
	//}
}
void CBullet::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
}

void CBullet::Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision)
{

}

RECT* CBullet::GetRectRS()
{
	return nullptr;
}

RECT CBullet::GetRect()
{
	return RECT();
}

CBullet::~CBullet()
{

}