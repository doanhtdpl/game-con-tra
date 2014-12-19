#include "CSingleton.h"
#include "CEnemyEffect.h"
#include "CExplosionEffect.h"
#include "CBullet.h"
#include "CBulletItem.h"
#ifndef __CEnemyDie_H__
#define __CEnemyDie_H__

class CPoolingObject : public CSingleton<CPoolingObject>
{
	friend class CSingleton<CPoolingObject>;
public:
	CEnemyEffect* GetEnemyEffect();
	CExplosionEffect* GetExplosionEffect();
	CBulletItem* GetBulletItem();
	void CreateBulletItem(int size);
	void CreateEnemyEffect(int size);
	void CreateExplosionEffect(int size);
	void Update(float deltaTime, std::vector<CGameObject*>* listObjectColision);
	std::vector<CBullet*> m_listBulletOfObject;
	void Draw();

protected:
	CPoolingObject();
	~CPoolingObject();
	std::vector<CEnemyEffect*> m_enemyEffect;
	std::vector<CExplosionEffect*> m_explosionEffect;
	std::vector<CBulletItem*> m_listBulletItem;
private:

};


#endif

