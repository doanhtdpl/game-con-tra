#include "CPoolingObject.h"
#include "CDrawObject.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CLoadGameObject.h"

CPoolingObject::CPoolingObject()
{

}


void CPoolingObject::CreateEnemyEffect(int size)
{
	if (this->m_enemyEffect.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CEnemyEffect* effectTemp;
			effectTemp = new CEnemyEffect();
			this->m_enemyEffect.push_back(effectTemp);
		}
	}

}

void CPoolingObject::CreateBulletItem(int size)
{
	if (this->m_listBulletItem.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CBulletItem* bulletItem;
			bulletItem = new CBulletItem();
			this->m_listBulletItem.push_back(bulletItem);
		}
	}
}

void CPoolingObject::CreateExplosionEffect(int size)
{
	if (this->m_explosionEffect.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CExplosionEffect* effectTemp;
			effectTemp = new CExplosionEffect();
			this->m_explosionEffect.push_back(effectTemp);
		}
	}
}


CBulletItem* CPoolingObject::GetBulletItem()
{
	for (std::vector<CBulletItem*>::iterator it = this->m_listBulletItem.begin();
		it != this->m_listBulletItem.end();
		++it)
	{
		CBulletItem* obj = *it;
		if (!obj->IsAlive())
		{
			return obj;
			break;
		}
	}
}

CEnemyEffect* CPoolingObject::GetEnemyEffect()
{
	for (std::vector<CEnemyEffect*>::iterator it = this->m_enemyEffect.begin();
		it != this->m_enemyEffect.end();
		++it)
	{
		CEnemyEffect* obj = *it;
		if (!obj->IsAlive())
		{
			return obj;
			break;
		}
	}
}

CExplosionEffect* CPoolingObject::GetExplosionEffect()
{
	for (std::vector<CExplosionEffect*>::iterator it = this->m_explosionEffect.begin();
		it != this->m_explosionEffect.end();
		++it)
	{
		CExplosionEffect* obj = *it;
		if (!obj->IsAlive())
		{
			return obj;
			break;
		}
	}
}

void CPoolingObject::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	// Update enemyEffect
	for (std::vector<CEnemyEffect*>::iterator it = this->m_enemyEffect.begin();
		it != this->m_enemyEffect.end();
		++it)
	{
		CEnemyEffect* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime);
		}

	}

	// Update explosionEffect

	for (std::vector<CExplosionEffect*>::iterator it = this->m_explosionEffect.begin();
		it != this->m_explosionEffect.end();
		++it)
	{
		CExplosionEffect* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime);
		}

	}

	//Update bullet
	for (std::vector<CBullet*>::iterator it = this->m_listBulletOfObject.begin();
		it != this->m_listBulletOfObject.end();)
	{
		CBullet* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime);
			//obj->Update(deltaTime, listObjectCollision);
			D3DXVECTOR3 pos;
			pos.x = obj->GetPos().x;
			pos.y = obj->GetPos().y;
			pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
			if(pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
			{
				delete obj;
				it = this->m_listBulletOfObject.erase(it);
			}
			else
			{
				++it;
			}
		}

	}

	//Update BulletItem
	for (std::vector<CBulletItem*>::iterator it = this->m_listBulletItem.begin();
		it != this->m_listBulletItem.end();
		++it)
	{
		CBulletItem* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}
}

void CPoolingObject::Draw()
{
	// Draw enemyEffect 
	for (std::vector<CEnemyEffect*>::iterator it = this->m_enemyEffect.begin();
		it != this->m_enemyEffect.end();
		++it)
	{
		CEnemyEffect* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}
	}

	// Draw explosionEffect
	for (std::vector<CExplosionEffect*>::iterator it = this->m_explosionEffect.begin();
		it != this->m_explosionEffect.end();
		++it)
	{
		CExplosionEffect* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}
	}


	////Draw bullet
	for (std::vector<CBullet*>::iterator it = this->m_listBulletOfObject.begin();
		it != this->m_listBulletOfObject.end();
		++it)
	{
		CBullet* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//
	////Draw bullet
	for (std::vector<CBulletItem*>::iterator it = this->m_listBulletItem.begin();
		it != this->m_listBulletItem.end();
		++it)
	{
		CBulletItem* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

}

