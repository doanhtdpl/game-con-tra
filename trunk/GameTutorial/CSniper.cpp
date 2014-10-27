#include "CSniper.h"
#include "CContra.h"
#include <math.h>

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
	this->m_pos = D3DXVECTOR2(1200.0f, 280.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 10;
	this->m_column = 6;
	//
	this->m_isShoot = false;
	this->m_stateCurrent = SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL;
	//Test
	this->m_s = 0;
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

void CSniper::SetFrame()
{
	//Chuyen doi frame
	switch (this->m_stateCurrent)
	{
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_NORMAL:
		{
			this->m_startFrame = 0;
			this->m_endFrame = 5;
			break;
		}
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_UP: case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DOWN:
	case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_UP: case SNIPER_SHOOT_STATE::SN_IS_SHOOTING_DIAGONAL_DOWN:
		{

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