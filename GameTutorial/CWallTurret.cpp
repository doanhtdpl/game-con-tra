#include "CWallTurret.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"

CWallTurret::CWallTurret(void)
{
	this->Init();
}
	
CWallTurret::CWallTurret(const std::vector<int>& info)
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

void CWallTurret::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 64.0f;//56.0f; //78
	this->m_height = 64.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(1100.0f, 200.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 42;
	this->m_column = 6;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL;
	//Test
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.25f;
}

void CWallTurret::Update(float deltaTime)
{
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->BulletUpdate(deltaTime);
}

void CWallTurret::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CWallTurret::BulletUpdate(float deltaTime)
{
#pragma region THIET LAP GOC BAN
	D3DXVECTOR2 posContra = CContra::GetInstance()->GetPos();
	float spaceX = posContra.x - this->m_pos.x;
	float spaceY = posContra.y - this->m_pos.y;
	double shootAngleNormal = PI / 6;
	double angle = 0.0f;
	if(spaceX > 0)
	{
		this->m_left = false;
	}
	else
	{
		this->m_left = true;
	}
	if(spaceX != 0)
	{
		angle = atan(spaceY / abs(spaceX));
		if(angle < 0)
		{
			//Chuyen sang toa do duong
			angle += 2*PI;
		}
		if(int(angle / shootAngleNormal) != 3 && int(angle / shootAngleNormal) != 9)
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
		case 0: case 6:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL;
				break;
			}
		case 1: case 4:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X;
				break;
			}
		case 2: case 5:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X;
				break;
			}
		case 3:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP;
				break;
			}
		case 7: case 11: 
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X;
				break;
			}
		case 8: case 10:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X;
				break;
			}
		case 9:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN;
				break;
			}
		}
	}
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	switch(this->m_stateCurrent)
	{
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL:
		{
			offset.x = this->m_width/ 2;
			offset.y = 26.0f;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP:
		{
			offset.x = 0;
			offset.y = 50.0f;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X:
		{
			offset.y = 50.0f;
			offset.x = this->m_width/2;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X:
		{
			offset.y = 50.0f;
			offset.x = this->m_width/2;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN:
		{
			offset.y = 0;
			offset.x = this->m_width/ 2;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X:
		{
			offset.y = -8.0f;
			offset.x = this->m_width/ 2;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X:
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

void CWallTurret::SetFrame()
{
	//Chuyen doi frame
	int currentFrame = this->m_currentFrame;
	switch (this->m_stateCurrent)
	{
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL:
		{
			this->m_startFrame = 12;
			this->m_endFrame = 14;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP:
		{
			this->m_startFrame = 3;
			this->m_endFrame = 5;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X:
		{
			this->m_startFrame = 6;
			this->m_endFrame = 8;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X:
		{
			this->m_startFrame = 9;
			this->m_endFrame = 11;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN:
		{
			this->m_startFrame = 21;
			this->m_endFrame = 23;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X:
		{
			this->m_startFrame = 18;
			this->m_endFrame = 20;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X:
		{
			this->m_startFrame = 15;
			this->m_endFrame = 17;
			break;
		}
	default:
		{
			break;
		}
	}
}

RECT* CWallTurret::GetBound()
{
	return nullptr;
}

RECT* CWallTurret::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CWallTurret::GetBox()
{
	return Box();
}

CWallTurret::~CWallTurret()
{

}