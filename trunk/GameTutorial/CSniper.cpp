#include "CSniper.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"

CSniper::CSniper(void)
{
	this->Init();
}

// Constructor
CSniper::CSniper(int idType, D3DXVECTOR2 pos)
{
	this->m_id = 1;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 52.0f;//56.0f; //78
	this->m_height = 78.0f; //88.0f; //84
	//this->m_pos = D3DXVECTOR2(250.0f, 300.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 6;
	this->m_elapseTimeChangeFrame = 0.2f;


	this->m_increase = 1;
	this->m_totalFrame = 10;
	this->m_column = 6;
	//
	this->m_isShoot = true;
	//Test
	this->m_bulletCount = 0;

	this->m_idState = idType;
	//
	this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_HIDING;
	this->m_timeDelay = 2.0f;
	if (m_idState == 1)
	{
		this->m_currentFrame = 0;
		this->m_timeDelay = 0.25f;
		this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL;
	}
	this->m_pos = pos;
}

CSniper::CSniper(const std::vector<int>& info)
{
	this->Init();//
	if(!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}

// Ham khoi tao cua linh nup
void CSniper::Init()
{
	//Khoi tao cac thong so cua doi tuong
	// TT
	this->m_idState = 2;

	this->m_id = 1;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 52.0f;//56.0f; //78
	this->m_height = 78.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(250.0f, 300.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 6;
	this->m_elapseTimeChangeFrame = 0.2f;

	
	this->m_increase = 1;
	this->m_totalFrame = 10;
	this->m_column = 6;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_HIDING;

	this->m_bulletCount = 0;
	this->m_timeDelay = 2.0f;

	this->m_allowShoot = true;
}

void CSniper::Update(float deltaTime)
{
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->BulletUpdate(deltaTime);
}

void CSniper::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CSniper::BulletUpdate(float deltaTime)
{
#pragma region THIET LAP GOC BAN
	D3DXVECTOR2 posContra = CContra::GetInstance()->GetPos();
	float spaceX = posContra.x - this->m_pos.x; //
	float spaceY = posContra.y - this->m_pos.y;
	double shootAngleNormal = PI / 10; //
	double angle = 0.0f;
	
	if(spaceX > 0)
	{
		this->m_left = true;
	}
	else
	{
		this->m_left = false;
	}

	// check if sniper is normal sniper.
	if (m_idState == 1)
	{
		if(spaceX != 0)
		{
			angle = atan(spaceY / abs(spaceX));
			if(angle < 0)
			{
				//Chuyen sang toa do duong
				angle += 2*PI;
			}
			if(int(angle / shootAngleNormal) != 0 && int(angle / shootAngleNormal) != 10)
				angle = (int(angle / shootAngleNormal) + 1) * shootAngleNormal;
			else
				angle = (int(angle / shootAngleNormal)) * shootAngleNormal;
		}
		else
		{
			if(spaceY > 0)
			{
				angle = PI/2;
			}
			else
			{
				angle = -PI/2;
			}
		}
	}
#pragma endregion

#pragma region THIET LAP TRANG THAI BAN

	// Normal sniper.
	if (m_idState == 1)
	{
		if(this->m_isShoot)
		{
			angle = (angle > 2 * PI) ? angle - 2*PI : angle;
			int space = int(angle / shootAngleNormal);
			switch(space)
			{
			case 0: case 10: case 20:
				{
					this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL;
					break;
				}
			case 1: case 2: case 3: case 4: case 6: case 7: case 8: case 9:
				{
					this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP;
					break;
				}
			case 5:
				{
					this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP;
					break;
				}
			case 11: case 12: case 13: case 14: case 16: case 17: case 18: case 19:
				{
					this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN;
					break;
				}
			case 15:
				{
					this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DOWN;
					break;
				}
			}
		}
	}

	
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	switch(this->m_stateCurrent)
	{
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL:
		{
			if (this->m_left){
				offset.x = this->m_width / 2;
				offset.y = 17.0f;
			}
			else{
				offset.y = 17.0f;
				offset.x = 0;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP:
		{
			if (this->m_left){
				offset.x = 0;
				offset.y = 50.0f;
			}
			else{
				offset.y = 50.0f;
				offset.x = 0;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP:
		{
			if (this->m_left){
				offset.y = 50.0f;
				offset.x = this->m_width / 2;
			}
			else{
				offset.y = 50.0f;
				offset.x = -20.0f;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DOWN:
		{
			if (this->m_left){
				offset.y = 0;
				offset.x = this->m_width / 2;
			}
			else{
				offset.y = 0.0f;
				offset.x = this->m_width / 2;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN:
		{
			if (this->m_left){
				offset.y = -8.0f;
				offset.x = this->m_width / 2;
			}
			else{
				offset.y = -8.0f;
				offset.x = -10.0f;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_HIDING:
		{
			if (this->m_currentFrame == 8)
			{
				offset.y = -9.f;
				offset.x = 0;
				break;
			}
		}
	default:
		{
			break;
		}
	}
#pragma endregion

#pragma region THIET LAP TOC DO DAN

	// Normal sniper.
	if (this->m_idState == 1)
	{
		if(this->m_isShoot)
		{
			if(m_bulletCount > 2)
			{
				this->m_bulletCount = 0;
				this->m_isShoot = false;
			}
			if(this->m_timeDelay >= 0.25f)
			{
				CBullet_N* bullet = new CBullet_N(angle, this->m_pos, offset, !this->m_left);
				m_listBullet.push_back(bullet);
				this->m_timeDelay = 0;
				m_bulletCount ++;
			}
			m_timeDelay += deltaTime;
		}
	} 
	// Hidding sniper.
	else
	{
		if (this->m_currentFrame == this->m_endFrame && this->m_increase >= 0)
		{
			if (m_bulletCount == 0)
			{
				CBullet_N* bullet = new CBullet_N(angle, this->m_pos, offset, !this->m_left);
				m_listBullet.push_back(bullet);
				m_bulletCount ++;
			}
			//
			this->m_increase = 0;// khong chuyen frame
			if (this->m_timeDelay <= 0)
			{
				this->m_timeDelay = 2.0f; // thoi gian delay frame 8
				this->m_increase = -1;
				this->m_bulletCount = 0;
			}
			else
			{
				this->m_timeDelay -= deltaTime;
			}
		}
	}


	//Update trang thai dan
	D3DXVECTOR3 pos;
	for (int i = 0; i < this->m_listBullet.size(); i++)
	{
		this->m_listBullet.at(i)->Update(deltaTime);
		pos.x = this->m_listBullet.at(i)->GetPos().x;
		pos.y = this->m_listBullet.at(i)->GetPos().y;
		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		if(pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
		{
			delete this->m_listBullet.at(i);
			this->m_listBullet.erase(this->m_listBullet.begin() + i);
		}
	}

	if(this->m_listBullet.empty())
	{
		this->m_isShoot = true;
	}
#pragma endregion

}

void CSniper::SetFrame()
{
	//Chuyen doi frame
	switch (this->m_stateCurrent)
	{
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL:
		{
			if(this->m_isShoot)
			{
				this->m_startFrame = 2;
				this->m_endFrame = 3;
			}
			else
			{
				this->m_startFrame = 2;
				this->m_endFrame = 2;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP: case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP: 
		{
			if(this->m_isShoot)
			{
				//this->m_currentFrame = 1;
				this->m_startFrame = 0;
				this->m_endFrame = 1;
			}
			else
			{
				this->m_startFrame = 0;
				this->m_endFrame = 0;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN: case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DOWN:
		{
			if(this->m_isShoot)
			{
				this->m_startFrame = 4;
				this->m_endFrame = 5;
			}
			else
			{
				this->m_startFrame = 4;
				this->m_endFrame = 4;
			}
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_HIDING:
		{
			//if(this->m_isShoot)
			//{
			//	this->m_startFrame = 6;
			//	this->m_endFrame = 8;
			//}
			//else
			//{
				this->m_startFrame = 6;
				this->m_endFrame = 8;
			//}
			if (this->m_currentFrame == 8)
			{
				//this->m_increase = -1;
			}
			if (this->m_currentFrame == 6)
			{
				this->m_increase = 1;
				this->m_elapseTimeChangeFrame = 1.5f;
			}
			else
			{
				this->m_elapseTimeChangeFrame = 0.2f;
			}
			break;
		}
	default:
		break;
	}
}

RECT* CSniper::GetBound()
{
	return nullptr;
}

RECT* CSniper::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CSniper::GetBox()
{
	return Box();
}

CSniper::~CSniper()
{

}