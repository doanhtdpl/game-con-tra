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
#include "CSoldierShoot.h"
#include "CSniper.h"
#include "CWallTurret.h"
#include "CWeapon.h"
#include "CSWeapon.h"
#include "CEnemyEffect.h"
#include "CExplosionEffect.h"
#include "CDefenseCannon.h"
#include "CBigCapsule.h"
#include "CBridge.h"

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

};

#endif // !__CStateGamePlay_H__

