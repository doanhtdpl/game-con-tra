#ifndef __CSOLDIER_H__
#define __CSOLDIER_H__

#include "CDynamicObject.h"
#include "CAnimation.h"

enum SOLDIER_STATE
{
	S_IS_JOGGING = 0, //Chay
	S_IS_STANDING = 1, //Dung lai va ban dan
	S_IS_JUMP = 2 // Nhay
};

class CSoldier : public CDynamicObject, public CAnimation
{
public:
	CSoldier(void);
	CSoldier(const std::vector<int>& info);
	~CSoldier();
	std::string ClassName(){return __CLASS_NAME__(CSoldier);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	//virtual void ChangeFrame(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	void BulletUpdate(float deltaTime);
	SOLIDER_STATE m_stateCurrent;
	void SetFrame();
	bool m_isShoot;
	//Tham so dung de test
	float m_s;
};

#endif // !__CSOLDIER_H__
