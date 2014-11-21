#ifndef __CGROUND_CANON_H__
#define __CGROUND_CANON_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CBulletN.h"

enum GROUNDCANON_SHOOT_STATE
{
	G_IS_SHOOTING_NORMAL = 0,
	G_IS_SHOOTING_DIAGONAL_UP_X = 1,
	G_IS_SHOOTING_DIAGONAL_UP_2X = 2,
};

class CGroundCanon : public CStaticObject, public CAnimation
{
public:
	CGroundCanon(void);
	CGroundCanon(const std::vector<int>& info);
	~CGroundCanon();
	std::string ClassName(){ return __CLASS_NAME__(CGroundCanon); };
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	void BulletUpdate(float deltaTime);
	GROUNDCANON_SHOOT_STATE m_stateCurrent;
	void SetFrame();
	bool m_isShoot;
	void MoveUp(float deltaTime);
	//Tham so dung de test
public:
	//Phai co mot bien de giu nhung vien dan ma enemy da ban ra
	std::vector<CBullet_N*> m_listBullet;
	int m_bulletCount; //So luong vien dan da ban ra
	float m_timeDelay;
	float m_heightMax;
};

#endif // !__CGROUND_CANON_H__
