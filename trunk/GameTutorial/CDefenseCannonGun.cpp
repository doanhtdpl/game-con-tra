#include "CDefenseCannonGun.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"
#include "CCollision.h"
#include "CContra.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include "CEnemyEffect.h"
#include "CPoolingObject.h"
#include <vector>

CDefenseCannonGun::CDefenseCannonGun(bool isGunLeft)
{
	this->m_IsGunLeft = isGunLeft;
	this->Init(0, 0);
}

CDefenseCannonGun::CDefenseCannonGun(bool isGunLeft, int xBoss, int yBoss)
{
	this->m_IsGunLeft = isGunLeft;
	this->Init(xBoss, yBoss);
}

CDefenseCannonGun::CDefenseCannonGun(const std::vector<int>& info)
{
	this->Init(0, 0);
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}


void CDefenseCannonGun::Init(int xBoss, int yBoss)
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 17;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 32.0f;
	this->m_height = 12.0f;
	if (this->m_IsGunLeft)
	{
		this->m_pos = D3DXVECTOR2(xBoss - 96.0f, yBoss + 13.0f);
		this->m_timeDelay = 0.25f;
		this->m_elapseTimeChangeFrame = 0.30f;
	}

	else
	{
		this->m_pos = D3DXVECTOR2(xBoss - 50.0f, yBoss + 13.0f);
		this->m_timeDelay = 0.45f;
		this->m_elapseTimeChangeFrame = 0.45f;
	}
	//
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;

	this->m_increase = 1;
	this->m_totalFrame = 4;
	this->m_column = 4;
	//
	this->m_isShoot = true;
	//Test
	this->m_bulletCount = 0;
	this->m_allowShoot = true;
	this->m_HP = 7;
	this->m_stateCurrent = DC_GUN_STATE::DC_GUN_NORMAL;

	// TT test
	this->m_countEffect = 0;
}

void CDefenseCannonGun::Update(float deltaTime)
{
	// Neu alive thi update dan va chuyen frame
	if (this->IsAlive())
	{
		this->SetFrame(this->m_IsGunLeft);
		this->ChangeFrame(deltaTime);
		this->BulletUpdate(deltaTime);
		this->OnCollision(deltaTime, nullptr);
	}
	else
	{
		// Nguoc lai chi update dan thoi.
		this->BulletUpdate(deltaTime);
	}
}

void CDefenseCannonGun::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	std::vector<CGameObject*>::iterator it;
	for (it = this->m_listBullet.begin(); it != this->m_listBullet.end();)
	{
		CGameObject*obj = *it;
		// Cuoi cung, la a xet va cham list đạn cua ụ súng.
		obj->OnCollision(deltaTime, listObjectCollision);
		if(!obj->IsAlive())  //Dang le ra thi cho nay phai duoc chu. nó
		{
			delete *it;
			it = this->m_listBullet.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void CDefenseCannonGun::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	for (std::vector<CBullet*>::iterator it = CPoolingObject::GetInstance()->m_listBulletOfObject.begin(); it != CPoolingObject::GetInstance()->m_listBulletOfObject.end();)
	{
		CGameObject* obj = *it;
		timeCollision = CCollision::GetInstance()->Collision(obj, this, normalX, normalY, moveX, moveY, deltaTime);
		if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
		{
			if (obj->IsAlive())
			{
				this->m_HP--;
				it = CPoolingObject::GetInstance()->m_listBulletOfObject.erase(it);
			}

			if (this->m_HP == 0)
			{
				// Gan trang thai die cho doi tuong
				this->m_stateCurrent = DC_GUN_STATE::DC_GUN_IS_DIE;
			}
		}
		else
		{
			++it;
		}
	}
}

void CDefenseCannonGun::BulletUpdate(float deltaTime)
{
	// Kiem tra, neu Gun alive thi tao dan, nguoc lai chi update ma thoi.
	if (this->IsAlive())
	{
#pragma region THIET LAP TRANG THAI BAN
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
		D3DXVECTOR2 offset;
		offset.x = -22.0f;
		offset.y = 10.0f;
#pragma endregion

#pragma region THIET LAP TOC DO DAN

		if (this->m_isShoot)
		{
			if (m_bulletCount > 4)
			{
				this->m_bulletCount = 0;
				this->m_isShoot = false;
			}
#pragma region THIET LAP GOC BAN

			double angle = 0.0f;
			srand(time(0));
			int temp = rand() % 4;
			switch (temp)
			{
			case 1://Goc pi/6
				angle = PI / 4;
				break;
			case 2: //Goc pi/8
				angle = PI / 20;
				break;
			case 3: //Goc pi/10
				angle = PI / 30;
				break;
			default:
				angle = PI / 80;
				break;
			}
#pragma endregion
			if (this->m_timeDelay >= 0.75f)
			{

				CBullet_DefenseCannon* bullet = new CBullet_DefenseCannon(angle, this->m_pos, offset, !this->m_left);
				m_listBullet.push_back(bullet);
				this->m_timeDelay = 0;
				m_bulletCount++;
			}

			m_timeDelay += deltaTime;
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
void CDefenseCannonGun::SetFrame(bool isGunLeft)
{
	switch (this->m_stateCurrent)
	{
	case DC_GUN_STATE::DC_GUN_NORMAL:
		{
			if (isGunLeft)
			{
				if (this->m_isShoot)
				{
					this->m_startFrame = 0;
					this->m_endFrame = 1;
				}
				else
				{
					this->m_startFrame = 0;
					this->m_endFrame = 0;
				}

			}
			else
			{
				if (this->m_isShoot)
				{
					this->m_startFrame = 2;
					this->m_endFrame = 3;
				}
				else
				{
					this->m_startFrame = 2;
					this->m_endFrame = 2;
				}
			}
			break;
		}
	case DC_GUN_STATE::DC_GUN_IS_DIE:
		{
			if (this->m_countEffect == 0)
			{
				CExplosionEffect* effect = CPoolingObject::GetInstance()->GetExplosionEffect();
				effect->SetAlive(true);
				effect->SetPos(this->m_pos);
				this->m_isALive = false;
				this->m_countEffect ++;
				break;
			}

		}
	}
}

RECT* CDefenseCannonGun::GetBound()
{
	return nullptr;
}

RECT* CDefenseCannonGun::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CDefenseCannonGun::	GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, 0, 0);
}

CDefenseCannonGun::~CDefenseCannonGun()
{

}