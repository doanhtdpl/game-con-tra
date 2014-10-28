#ifndef __CSNIPER_H__
#define __CSNIPER_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CBulletN.h"

enum SNIPER_SHOOT_STATE
{
	SN_IS_SHOOTING_DOWN = 0,
	SN_IS_SHOOTING_UP = 1,
	SN_IS_SHOOTING_NORMAL = 2,
	SN_IS_SHOOTING_DIAGONAL_UP = 3,
	SN_IS_SHOOTING_DIAGONAL_DOWN = 4
};

class CSniper : public CStaticObject, public CAnimation
{
public:
	CSniper(void);
	CSniper(const std::vector<int>& info);
	~CSniper();
	std::string ClassName(){return __CLASS_NAME__(CSniper);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	void BulletUpdate(float deltaTime);
	SNIPER_SHOOT_STATE m_stateCurrent;
	void SetFrame();
	bool m_isShoot;
	//Tham so dung de test
public:
	//Phai co mot bien de giu nhung vien dan ma enemy da ban ra
	std::vector<CBullet_N*> m_listBullet;
	int m_bulletCount; //So luong vien dan da ban ra
	float m_timeDelay;

};

#endif // !__CSNIPER_H__
