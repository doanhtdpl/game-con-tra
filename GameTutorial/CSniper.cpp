#include "CSniper.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"

CSniper::CSniper(void)
{
	this->Init();
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

void CSniper::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 1;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 52.0f;//56.0f; //78
	this->m_height = 78.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(1250.0f, 100.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 10;
	this->m_column = 6;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL;
	//Test
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.25f;
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

/*
void CSniper::BulletUpdate(float deltaTime)
{
#pragma region XET_GOC_BAN_CUA_SNIPER
	D3DXVECTOR2 pos = CContra::GetInstance()->GetPos();
	float spaceY = pos.y - this->m_pos.y;
	float spaceX = pos.x - this->m_pos.x;
	int direction = 0;
	double angle = 0.0f;
	//Thiet lap goc ban
	if(spaceY != 0)
	{
		int start = 0;
		int end = 0;
		angle = spaceY / spaceX;
		if(spaceX > 0)
		{
			direction = 1;
		}
		else
		{
			direction = -1;
		}
			
		//kiem tra goc la am hay duong
		if(spaceY > 0 && spaceX > 0)
		{
			//Neu la goc  0 < a < 90 
			start = 0;
			end = 5;
		}
		else if(spaceY > 0 && spaceX < 0)
		{
			//Neu 90 < a < 180
			start = 5;
			end = 11;
		}
		else if(spaceY < 0 && spaceX > 0)
		{ 
			//Neu 180 < a < 270
			start = 10;
			end = 16;
		}
		else
		{
			//Neu 270 < a < 360
			start = 15;
			end = 21;
		}
		for(int i = start; i < end; ++i)
		{
			if(angle < direction * atan(i * (PI / 10)))
			{
				angle = (i + direction) * (PI / 10);
			}
		}
	}
	else
	{
		angle = 0;
	}
#pragma endregion
#pragma region XET_TRANG_THAI_CUA_SNIPER

#pragma endregion

	if(this->m_isShoot)
	{
		if((angle <= PI/ 2 && angle >= 2*PI/5 ) || (angle >= PI/2 && angle <= 3*PI/5))
		{
			this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP;
		}
		else if((angle >= PI / 10 && angle < 2*PI/5) || (angle > 3*PI/5 && angle < 9*PI/10))
		{
			this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP;
		}
		else if((angle > 9*PI/10 && angle <11*PI/10) || (angle > 0 && angle < PI / 10) || (angle > 19*PI/10 && angle < 2*PI)  )
		{
			this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL;
		}
		else if((angle > 11*PI/10 && angle < 7*PI/5) || angle > 8*PI/5 && angle < 19*PI/10)
		{
			this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN;
		}
		else
		{
			this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN;
		}
	}
}
*/

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
#pragma endregion

#pragma region THIET LAP TRANG THAI BAN
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
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	switch(this->m_stateCurrent)
	{
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL:
		{
			offset.x = this->m_width/ 2;
			offset.y = 26.0f;
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP:
		{
			offset.x = 0;
			offset.y = 50.0f;
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP:
		{
			offset.y = 50.0f;
			offset.x = this->m_width/2;
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DOWN:
		{
			offset.y = 0;
			offset.x = this->m_width/ 2;
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN:
		{
			offset.y = -8.0f;
			offset.x = this->m_width/ 2;
			break;
		}
	default:
		{
			break;
		}
	}
#pragma endregion

#pragma region THIET LAP TOC DO DAN

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