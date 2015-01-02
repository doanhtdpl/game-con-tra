#ifndef __CBOSSARM_H__
#define __CBOSSARM_H__

#include "CDynamicObject.h"
#include "CMove.h"
#include "CSubArm.h"

class CBossArm : public CDynamicObject
{
public:
	CBossArm();
	~CBossArm();
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	virtual void MoveUpdate(float deltaTime);
	virtual RECT* GetRectRS();
	virtual Box GetBox();
	virtual void Init();
	void Move(float curve, float deltaTime);
	void Draw();
public:
	/*CSubArm* subArmOne;
	CSubArm* subArmTwo;
	CSubArm* subArmThree;
	CSubArm* subArmFour;
	CSubArm* subArmFive;*/
	CSubArm** subArms;
	//
protected:
	float m_timeCurr;
	bool m_isChangeDirection; //Cuc dau tien doi huong, delay
};

#endif // !__CBOSSARM_H__
