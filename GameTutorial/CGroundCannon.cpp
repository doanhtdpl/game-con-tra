#include "CGroundCannon.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"

CGroundCanon::CGroundCanon(void)
{
	this->Init();
}

CGroundCanon::CGroundCanon(const std::vector<int>& info)
{
	this->Init();//
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}

void CGroundCanon::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 3;
	this->m_idType = 11;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 64.0f;//56.0f; //78
	this->m_height = 64.0f; //88.0f; //84
	this->m_heightMax = 64.0f;
	this->m_pos = D3DXVECTOR2(770.0f, 220.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 9;
	this->m_column = 3;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_NORMAL;
	//Test
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.25f;
}

void CGroundCanon::Update(float deltaTime)
{
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->MoveUp(deltaTime);
}

void CGroundCanon::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CGroundCanon::BulletUpdate(float deltaTime)
{
#pragma region THIET LAP GOC BAN
	D3DXVECTOR2 posContra = CContra::GetInstance()->GetPos();
	float spaceX = posContra.x - this->m_pos.x;
	float spaceY = posContra.y - this->m_pos.y;
	double shootAngleNormal = PI / 6;
	double angle = 0.0f;
	this->m_left = false;
	
	if (spaceX < 0)
	{
		angle = atan(spaceY / abs(spaceX));		
	}
	else
	{
		angle = PI;
	}
#pragma endregion

#pragma region THIET LAP TRANG THAI BAN
	if (this->m_isShoot)
	{
	//	angle = (angle > 2 * PI) ? angle - 2 * PI : angle;
		int space = int(angle / shootAngleNormal);
		switch (space)
		{
		case 0: case 6:
			{
				this->m_stateCurrent = GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_NORMAL;
				break;
			}
		case 1:
			{
				this->m_stateCurrent = GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_X;
				break;
			}
		case 2:
			{
				this->m_stateCurrent = GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_2X;
				break;
			}
		}
	}
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	switch (this->m_stateCurrent)
	{
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_NORMAL:
	{
		offset.x = this->m_width / 2;
		offset.y = 0.0f;
		break;
	}
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_X:
	{
		offset.y = 20.0f;
		offset.x = this->m_width / 2;
		break;
	}
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_2X:
	{
		offset.y = 50.0f;
		offset.x = this->m_width / 2;
		break;
	}
	default:
	{
		break;
	}
	}
#pragma endregion

#pragma region THIET LAP TOC DO DAN

	if (this->m_isShoot && spaceX < 0)
	{
		if (m_bulletCount > 2)
		{
			this->m_bulletCount = 0;
			this->m_isShoot = false;
		}
		if (this->m_timeDelay >= 0.25f)
		{
			CBullet_N* bullet = new CBullet_N(angle, this->m_pos, offset, !this->m_left);
			m_listBullet.push_back(bullet);
			this->m_timeDelay = 0;
			m_bulletCount++;
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
		if (pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
		{
			delete this->m_listBullet.at(i);
			this->m_listBullet.erase(this->m_listBullet.begin() + i);
		}
	}
	if (this->m_listBullet.empty())
	{
		this->m_isShoot = true;
	}
#pragma endregion

}

void CGroundCanon::MoveUp(float deltaTime){

	if (this->m_height != this->m_heightMax){
		this->m_timeDelay += deltaTime;
		if (this->m_timeDelay > 0.1) //0.3 co the thay tuy y cua minh
		{
			this->m_timeDelay = 0;
			this->m_height += 8;
		}
	}
	else
	{
		this->BulletUpdate(deltaTime);
	}

}

void CGroundCanon::SetFrame()
{
	//Chuyen doi frame
	int currentFrame = this->m_currentFrame;
	switch (this->m_stateCurrent)
	{
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_NORMAL:
	{
		this->m_startFrame = 0;
		this->m_endFrame = 2;
		break;
	}
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_X:
	{
		this->m_startFrame = 3;
		this->m_endFrame = 5;
		break;
	}
	case GROUNDCANON_SHOOT_STATE::G_IS_SHOOTING_DIAGONAL_UP_2X:
	{
		this->m_startFrame = 6;
		this->m_endFrame = 8;
		break;
	}
	default:
	{
		break;
	}
	}
}

RECT* CGroundCanon::GetBound()
{
	return nullptr;
}

RECT* CGroundCanon::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CGroundCanon::GetBox()
{
	return Box();
}

CGroundCanon::~CGroundCanon()
{

}