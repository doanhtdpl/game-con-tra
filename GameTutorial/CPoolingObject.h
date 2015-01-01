#include "CSingleton.h"
#include "CEnemyEffect.h"
#include "CExplosionEffect.h"
#include "CBullet.h"
#include "CBulletItem.h"
#include "CSoldier.h"
#include "CSoldierShoot.h"
#include "CWeapon.h"
#include "CCapsuleBoss.h"
#include "CBigStone.h"
#include "CBulletLaze.h"

#ifndef __CEnemyDie_H__
#define __CEnemyDie_H__

class CPoolingObject : public CSingleton<CPoolingObject>
{
	friend class CSingleton<CPoolingObject>;
public:
	CEnemyEffect* GetEnemyEffect();
	CExplosionEffect* GetExplosionEffect();
	CBulletItem* GetBulletItem();
	CSoldier* GetSoliderObject();
	CSoldierShoot* GetSoliderShootObject();
	CWeapon* GetWeapon();
	CCapsuleBoss* GetCapsuleBoss();
	CBigStone* GetBigStone();
	CBulletLaze* GetBulletLaze();

	void CreateSoliderObject(int size);
	void CreateSoliderShootObject(int size);
	void CreateBulletItem(int size);
	void CreateEnemyEffect(int size);
	void CreateExplosionEffect(int size);
	void CreateWeapon(int size);
	void CreateCapsuleBoss(int size);
	void CreateBigStone(int size);
	void CreateBulletLaze(int size);
	void Update(float deltaTime, std::vector<CGameObject*>* listObjectColision);
	std::vector<CBullet*> m_listBulletOfObject;
	std::vector<CWeapon*> m_listWeapon; //Weapon dong
	void Draw();

protected:
	CPoolingObject();
	~CPoolingObject();
	std::vector<CEnemyEffect*> m_enemyEffect;
	std::vector<CExplosionEffect*> m_explosionEffect;
	std::vector<CBulletItem*> m_listBulletItem;
	std::vector<CSoldier*> m_listSolider;
	std::vector<CSoldierShoot*> m_listSoliderShoot;
	std::vector<CBigStone*> m_listBigStone;
	std::vector<CBulletLaze*> m_listBulletLaze;
	//Con boss map 5
	std::vector<CCapsuleBoss*> m_listCapsuleBoss;
private:
};


#endif

