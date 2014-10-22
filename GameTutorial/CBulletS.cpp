#include "CBulletS.h"
#include <math.h>
#include "CGlobal.h"
#include "CContra.h"

/**		
/	Class CBullet_S:
/		+ Chua set chuyen frame
/
*/
CBullet_S::CBullet_S()
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
	this->InitPosition();
	
}

CBullet_S::CBullet_S(double rotation)
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
	this->InitPosition();
	//
	this->m_rotation = rotation;
	this->m_bullet_1 = new CBullet(rotation);
	this->m_bullet_2 = new CBullet(rotation + PI/24);
	this->m_bullet_3 = new CBullet(rotation + PI/12);
	this->m_bullet_4 = new CBullet(rotation - PI/24);
	this->m_bullet_5 = new CBullet(rotation - PI/12);
	//this->m_bullet_4 = new CBullet(rotation > 0 ? rotation - PI/12 : -rotation - PI/12);
	//this->m_bullet_5 = new CBullet(rotation > 0 ? rotation - PI/6 : -rotation - PI/6);
}

void CBullet_S::InitPosition()
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

void CBullet_S::MoveUpdate(float deltaTime)
{
#pragma region __XET_TRANG_THAI_DAN__
	
	this->m_bullet_1->MoveUpdate(deltaTime);
	this->m_bullet_2->MoveUpdate(deltaTime);
	this->m_bullet_3->MoveUpdate(deltaTime);
	this->m_bullet_4->MoveUpdate(deltaTime);
	this->m_bullet_5->MoveUpdate(deltaTime);

#pragma endregion
}
void CBullet_S::Update(float deltaTime)
{
	//this->MoveUpdate(deltaTime);
}

void CBullet_S::Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision)
{

}

RECT* CBullet_S::GetRectRS()
{
	return nullptr;
}

RECT CBullet_S::GetRect()
{
	return RECT();
}

CBullet_S::~CBullet_S()
{

}