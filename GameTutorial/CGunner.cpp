#include "CGunner.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"
#include "CCollision.h"
#include "CPoolingObject.h"

CGunner::CGunner(void)
{
	this->Init();
}

CGunner::CGunner(const std::vector<int>& info)
{
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
	this->Init();//
}

// Ham khoi tao cua linh nup
void CGunner::Init()
{
	//Khoi tao cac thong so cua doi tuong
	// TT
	this->m_id = 6;
	this->m_idType = 11;
	this->m_idImage = 6;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 66.0f;
	this->m_height = 64.0f;
	this->m_left = false;
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.650f;

	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = GUNNER_STATE::GN_IS_NORMAL;
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.40f;
	this->m_waitForShoot = 0.7f;

	this->m_allowShoot = true;
	this->m_HP = 5;
}

void CGunner::Update(float deltaTime)
{
	if (this->IsAlive())
	{
		this->SetFrame(deltaTime);
		this->ChangeFrame(deltaTime);
		this->BulletUpdate(deltaTime);
		this->OnCollision(deltaTime, nullptr);
	}
	else
	{
		this->BulletUpdate(deltaTime);
	}

}

void CGunner::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	if (this->IsAlive())
	{
		this->SetFrame(deltaTime);
		this->ChangeFrame(deltaTime);
		this->BulletUpdate(deltaTime);
		this->OnCollision(deltaTime, listObjectCollision);
	}
	else
	{
		this->BulletUpdate(deltaTime);
	}
}

void CGunner::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
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
				this->m_stateCurrent = GUNNER_STATE::GN_IS_DIE;
			}
		}
		else
		{
			++it;
		}
	}
}

void CGunner::BulletUpdate(float deltaTime)
{
#pragma region THIET LAP GOC BAN
	//Ban 1 goc thang
#pragma endregion

#pragma region THIET LAP TRANG THAI BAN

#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	offset.x = -this->m_width / 2;
	offset.y = this->m_height / 2 - 12.0f;
#pragma endregion

#pragma region THIET LAP TOC DO DAN

	if (this->m_currentFrame == 1)
	{
		if (m_bulletCount == 0)
		{
			CBullet_M* bullet = new CBullet_M(0, this->m_pos, offset, !this->m_left);
			bullet->m_isContra = false;
			m_listBullet.push_back(bullet);
			m_bulletCount++;
		}
		//
		if (this->m_waitForShoot <= 0)
		{
			this->m_waitForShoot = 0.70f; // thoi gian delay frame 8
			this->m_bulletCount = 0;
		}
		else
		{
			this->m_waitForShoot -= deltaTime;
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

void CGunner::SetFrame(float deltaTime)
{
	//Chuyen doi frame
	switch (this->m_stateCurrent)
	{
	case GUNNER_STATE::GN_IS_NORMAL:
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
									   break;
	}
	case GUNNER_STATE::GN_IS_DIE:
	{
									CExplosionEffect* effect = CPoolingObject::GetInstance()->GetExplosionEffect();
									effect->SetAlive(true);
									effect->SetPos(this->m_pos);
									this->m_isALive = false;
									break;
	}
	default:
		break;
	}
}


RECT* CGunner::GetBound()
{
	return nullptr;
}

RECT* CGunner::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CGunner::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width - 20, this->m_height, 0, 0);
}

CGunner::~CGunner()
{

}