#ifndef __CSUBARM_H__
#define __CSUBARM_H__

#include "CDynamicObject.h"
#include "CMove.h"

enum SUB_ARM_TYPE
{
	SUB_ARM_FIRST = 0, //Dau canh tay
	SUB_ARM_COMPONENT = 1 //Cac thanh phan
};

class CSubArm : public CDynamicObject
{
public:
	CSubArm();
	~CSubArm();
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	virtual void MoveUpdate(float deltaTime);
	virtual RECT* GetRectRS();
	virtual Box GetBox();
	virtual void Init();
	void SetArmType(SUB_ARM_TYPE type){this->m_armType = type;};
	void Move(D3DXVECTOR2 posCenter, float radian, bool direction, float deltaTime);
	bool Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, double angleStart, double angleEnd, bool direction, float deltaTime);
	void Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, float deltaTime);
	bool Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, bool direction, float deltaTime);
	bool Move(D3DXVECTOR2 posCenter, float radian, double angleStart, double angleEnd, float deltaTime);
	bool Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, double angleStart, double angleEnd, float deltaTime);
	void Move(float rotation, D3DXVECTOR2 posStart, D3DXVECTOR2 posEnd, float deltaTime);
	float WaitForAppear;
protected:
	D3DXVECTOR2 m_posCenter; //vi tri tam quay
	double m_rotation; //Goc quay cua tam dan
	float m_radian; //ban kinh quay
	double m_angle; //goc quay cua cuc nho
	double m_angleDefault; //
	float m_curveCurr; //cung quay
	float m_waitForHandAppear;
	SUB_ARM_TYPE m_armType; //Kieu cua cuc nho
};

#endif // !__CSUBARM_H__
