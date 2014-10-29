#ifndef __CWALL_TURRET_H__
#define __CWALL_TURRET_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CBulletN.h"

enum WALLTURRET_SHOOT_STATE
{
	W_IS_SHOOTING_DOWN = 0,
	W_IS_SHOOTING_UP = 1,
	W_IS_SHOOTING_NORMAL = 2,
	W_IS_SHOOTING_DIAGONAL_UP_X = 3,
	W_IS_SHOOTING_DIAGONAL_UP_2X = 4,
	W_IS_SHOOTING_DIAGONAL_DOWN_X = 5,
	W_IS_SHOOTING_DIAGONAL_DOWN_2X = 6
};

class CWallTurret : public CStaticObject, public CAnimation
{
public:
	CWallTurret(void);
	CWallTurret(const std::vector<int>& info);
	~CWallTurret();
	std::string ClassName(){return __CLASS_NAME__(CWallTurret);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	void BulletUpdate(float deltaTime);
	WALLTURRET_SHOOT_STATE m_stateCurrent;
	void SetFrame();
	bool m_isShoot;
	//Tham so dung de test
public:
	//Phai co mot bien de giu nhung vien dan ma enemy da ban ra
	std::vector<CBullet_N*> m_listBullet;
	int m_bulletCount; //So luong vien dan da ban ra
	float m_timeDelay;
	double m_oldangle;
	double m_totalCurr;
	double m_space;
	bool m_direction;
	bool m_IsCre;
};

#endif // !__CWALL_TURRET_H__
