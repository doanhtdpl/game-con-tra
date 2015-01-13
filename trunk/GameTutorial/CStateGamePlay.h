#ifndef __CStateGamePlay_H__
#define __CStateGamePlay_H__
#include "CState.h"
#include <iostream>
#include "CContra.h"
#include "CDynamicObject.h"
#include "CSubArm.h"
#include "CBossArm.h"

class CStateGamePlay : public CState
{
public:
	CStateGamePlay();
	CStateGamePlay(int mapId);
	virtual ~CStateGamePlay();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
public:
	int m_mapId;
};

#endif // !__CStateGamePlay_H__

