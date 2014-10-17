#ifndef __CCONTRA_H__
#define __CCONTRA_H__
#include "CDynamicObject.h"
#include "CAnimation.h"

enum ON_GROUND
{
	IS_STANDING = 10,
	IS_JOGGING = 11,
	IS_JUMPING = 12,
	IS_LYING = 13,
	IS_FALL = 14,
	IS_SHOOTING_UP = 15,
	IS_SHOOTING_DOWN = 16,
	IS_SHOOTING_DIAGONAL_UP = 17,
	IS_SHOOTING_DIAGONAL_DOWN = 18,
	IS_DIE = 19
};

enum UNDER_WATER
{
	IS_STANDING_UNDER_WATER = 20,
	IS_LYING_UNDER_WATER = 21,
	IS_JOGGING_UNDER_WATER = 22,
	IS_DIE_UNDER_WATER = 23
};

enum SHOOT
{
	IS_NORMAL,
	IS_UP,
	IS_DOWN,
	IS_DIAGONAL_UP,
	IS_DIAGONAL_DOWN
};

class CContra : public CDynamicObject, CAnimation
{
public:
	CContra();
	~CContra();
	std::string ClassName(){ return __CLASS_NAME__(CContra);};
	virtual void MoveUpdate(float deltaTime);
	void ChangeFrame(float deltaTime);
	void InputUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	RECT GetRect();
	RECT* GetRectRS();
protected:
	void SetFrame();
	int m_startFrame;
	int m_endFrame;
	bool m_isUnderWater;
	bool m_isShoot;
	int m_stateCurrent;
	int m_stateShoot;
	int m_currentJump;
};

#endif // !__CCONTRA_H__
