#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__
#include "CState.h"
#include <iostream>
#include "CSprite.h"
#include "CTexture.h"
#include "CContra.h"
#include "CSimon.h"
#include "CDynamicObject.h"

class CStateLogo : public CState
{
public:
	CStateLogo();
	virtual ~CStateLogo();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
protected:
	int m_count;
	CSprite* sprite;
	CTexture** texture;
	CSimon* simon;
	CContra* contra;
};

#endif // !__CSTATELOGO_H__

