#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__
#include "CState.h"
#include <iostream>
#include "CSprite.h"
#include "CTexture.h"

class CStateLogo : public CState
{
public:
	CStateLogo();
	virtual ~CStateLogo();
	void Init();
	void Update();
	void Render();
	void Destroy();
protected:
	int m_count;
	CSprite* sprite;
	CTexture* texture;
};

#endif // !__CSTATELOGO_H__

