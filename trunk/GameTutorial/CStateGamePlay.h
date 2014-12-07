#ifndef __CStateGamePlay_H__
#define __CStateGamePlay_H__
#include "CState.h"
#include <iostream>
#include "CSprite.h"
#include "CTexture.h"
#include "CContra.h"
#include "CDynamicObject.h"
#include "CHidenObject.h"
#include "CSoldier.h"
#include "CSniper.h"
#include "CWallTurret.h"
#include "CWeapon.h"
#include "CSWeapon.h"

class CStateGamePlay : public CState
{
public:
	CStateGamePlay();
	virtual ~CStateGamePlay();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
protected:
	CSoldier* sObj;
	CSniper* nobj;
	CWallTurret* wobj;
	CWeapon* weObj;
	CSWeapon* wseObj;
	// Test collision
	Box first;
	Box second;
	Box broadphaseBox;
	bool isCollision;
	float collisiontime;
	float increse;
};

#endif // !__CStateGamePlay_H__

