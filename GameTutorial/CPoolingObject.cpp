#include "CPoolingObject.h"
#include "CDrawObject.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CLoadGameObject.h"
#include "CContra.h"

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

void CPoolingObject::CreateSoliderObject(int size)
{
	if (this->m_listSolider.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CSoldier* soldier;
			soldier = new CSoldier();
			this->m_listSolider.push_back(soldier);
		}
	}
}

void CPoolingObject::CreateSoliderShootObject(int size)
{
	if (this->m_listSoliderShoot.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CSoldierShoot* soldierShoot;
			soldierShoot = new CSoldierShoot();
			this->m_listSoliderShoot.push_back(soldierShoot);
		}
	}
}

void CPoolingObject::CreateBigStone(int size)
{
	if (this->m_listBigStone.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CBigStone* bigStone;
			bigStone = new CBigStone();
			this->m_listBigStone.push_back(bigStone);
		}
	}
}
void CPoolingObject::CreateWeapon(int size)
{
	if (this->m_listWeapon.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CWeapon* weapon;
			weapon = new CWeapon();
			this->m_listWeapon.push_back(weapon);
		}
	}
}

void CPoolingObject::CreateCapsuleBoss(int size)
{
	if (this->m_listCapsuleBoss.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CCapsuleBoss* capsule;
			capsule = new CCapsuleBoss();
			this->m_listCapsuleBoss.push_back(capsule);
		}
	}
}

void CPoolingObject::CreateBulletLaze(int size)
{
	if (this->m_listBulletLaze.empty())
	{
		for (int i = 0; i < size; i++)
		{
			CBulletLaze* laze;
			laze = new CBulletLaze();
			this->m_listBulletLaze.push_back(laze);
		}
	}
}

CSoldier* CPoolingObject::GetSoliderObject()
{
	CSoldier* obj = nullptr;
	CSoldier* objCheck = nullptr;
	int count = 0;
	for (std::vector<CSoldier*>::iterator it = this->m_listSolider.begin();
		it != this->m_listSolider.end();
		++it)
	{
		objCheck = *it;
		if (obj == nullptr)
		{
			obj = *it;
			if (!obj->IsAlive())
			{
				obj->Init();
			}
			else
			{
				obj = nullptr;
			}
		}
		if (objCheck->IsAlive())
		{
			count ++;
		}
	}

	// kiem tra so luong soldier toi da tren man hinh
	if (count < 4)
	{
		count = 0;
		return obj;
	}
	else
		return nullptr;
}

CSoldierShoot* CPoolingObject::GetSoliderShootObject()
{
	CSoldierShoot* obj = nullptr;
	CSoldierShoot* objCheck = nullptr;
	int count = 0;
	for (std::vector<CSoldierShoot*>::iterator it = this->m_listSoliderShoot.begin();
		it != this->m_listSoliderShoot.end();
		++it)
	{
		objCheck = *it;
		if (obj == nullptr)
		{
			obj = *it;
			if (!obj->IsAlive())
			{
				obj->Init();
			}
			else
			{
				obj = nullptr;
			}
		}
		if (objCheck->IsAlive())
		{
			count++;
		}
	}

	// kiem tra so luong soldier toi da tren man hinh
	if (count < 3)
	{
		count = 0;
		return obj;
	}
	else
		return nullptr;
}

CBigStone* CPoolingObject::GetBigStone()
{
	CBigStone* obj = nullptr;
	CBigStone* objCheck = nullptr;
	int count = 0;
	for (std::vector<CBigStone*>::iterator it = this->m_listBigStone.begin();
		it != this->m_listBigStone.end();
		++it)
	{
		objCheck = *it;
		if (obj == nullptr)
		{
			obj = *it;
			if (!obj->IsAlive())
			{
				obj->Init();
			}
			else
			{
				obj = nullptr;
			}
		}
		if (objCheck->IsAlive())
		{
			count++;
		}
	}
	// kiem tra so luong bigStone toi da tren man hinh
	/*if (count < 4)
	{
		count = 0;
		return obj;
	}
	else
		return nullptr;*/
	return obj;
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
			obj->Init();
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

CWeapon* CPoolingObject::GetWeapon()
{
	for (std::vector<CWeapon*>::iterator it = this->m_listWeapon.begin();
		it != this->m_listWeapon.end();
		++it)
	{
		CWeapon* obj = *it;
		if (!obj->IsAlive())
		{
			return obj;
			break;
		}
	}
}

CCapsuleBoss* CPoolingObject::GetCapsuleBoss()
{
	for (std::vector<CCapsuleBoss*>::iterator it = this->m_listCapsuleBoss.begin();
		it != this->m_listCapsuleBoss.end();
		++it)
	{
		CCapsuleBoss* obj = *it;
		if (!obj->IsAlive())
		{
			return obj;
			break;
		}
	}
}

CBulletLaze* CPoolingObject::GetBulletLaze()
{
	CBulletLaze* obj = nullptr;
	CBulletLaze* objCheck = nullptr;
	int count = 0;
	for (std::vector<CBulletLaze*>::iterator it = this->m_listBulletLaze.begin();
		it != this->m_listBulletLaze.end();
		++it)
	{
		objCheck = *it;
		if (obj == nullptr)
		{
			obj = *it;
			if (!obj->IsAlive())
			{
				obj->Init();
			}
			else
			{
				obj = nullptr;
			}
		}
		if (objCheck->IsAlive())
		{
			count++;
		}
	}
	//Random so luong laze
	int ranCountLaze = 1 + rand() % 4;
	// kiem tra so luong laze toi da tren man hinh
	if (count < ranCountLaze)
	{
		count = 0;
		return obj;
	}
	else
	return nullptr;

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
			//obj->Update(deltaTime);
			if (obj->GetIDType() == 20 && obj->GetID() == 9)
			{
				int x = 0;
			}
			obj->Update(deltaTime, listObjectCollision);
			D3DXVECTOR3 pos;
			pos.x = obj->GetPos().x;
			pos.y = obj->GetPos().y;
			pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
			if(pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0
				|| !obj->IsAlive())
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

	//Update Soldier
	for (std::vector<CSoldier*>::iterator it = this->m_listSolider.begin();
		it != this->m_listSolider.end();
		++it)
	{
		CSoldier* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}

	//Update Soldier Shoot
	for (std::vector<CSoldierShoot*>::iterator it = this->m_listSoliderShoot.begin();
		it != this->m_listSoliderShoot.end();
		++it)
	{
		CSoldierShoot* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}

	//Update Big Stone
	for (std::vector<CBigStone*>::iterator it = this->m_listBigStone.begin();
		it != this->m_listBigStone.end();
		++it)
	{
		CBigStone* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}

	//Update Weapon
	for (std::vector<CWeapon*>::iterator it = this->m_listWeapon.begin();
		it != this->m_listWeapon.end();
		++it)
	{
		CWeapon* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}

	//Update Capsule
	for (std::vector<CCapsuleBoss*>::iterator it = this->m_listCapsuleBoss.begin();
		it != this->m_listCapsuleBoss.end();
		++it)
	{
		CCapsuleBoss* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			obj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		}

	}

	//Update Bullet Laze
	for (std::vector<CBulletLaze*>::iterator it = this->m_listBulletLaze.begin();
		it != this->m_listBulletLaze.end();
		++it)
	{
		CBulletLaze* obj = *it;
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

	////Draw Weapon
	for (std::vector<CWeapon*>::iterator it = this->m_listWeapon.begin();
		it != this->m_listWeapon.end();
		++it)
	{
		CWeapon* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//Solider
	for (std::vector<CSoldier*>::iterator it = this->m_listSolider.begin();
		it != this->m_listSolider.end();
		++it)
	{
		CSoldier* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//Solider Shoot
	for (std::vector<CSoldierShoot*>::iterator it = this->m_listSoliderShoot.begin();
		it != this->m_listSoliderShoot.end();
		++it)
	{
		CSoldierShoot* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//Big Stone
	for (std::vector<CBigStone*>::iterator it = this->m_listBigStone.begin();
		it != this->m_listBigStone.end();
		++it)
	{
		CBigStone* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//Capsule
	for (std::vector<CCapsuleBoss*>::iterator it = this->m_listCapsuleBoss.begin();
		it != this->m_listCapsuleBoss.end();
		++it)
	{
		CCapsuleBoss* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}

	//Bullet Laze
	for (std::vector<CBulletLaze*>::iterator it = this->m_listBulletLaze.begin();
		it != this->m_listBulletLaze.end();
		++it)
	{
		CBulletLaze* obj = *it;
		if (obj != NULL && obj->IsAlive())
		{
			CDrawObject::GetInstance()->Draw(obj);
		}

	}
}