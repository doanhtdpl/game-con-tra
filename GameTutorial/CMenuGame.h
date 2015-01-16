#ifndef __CMENU_GAME_H__
#define __CMENU_GAME_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CChooseItem.h"
#include "CScoreScense.h"

class CMenuGame : public CStaticObject, public CAnimation
{
public:
	CMenuGame(void);
	CMenuGame(const std::vector<int>& info);
	~CMenuGame();
	std::string ClassName(){ return __CLASS_NAME__(CMenuGame); };
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	virtual void Draw();
	RECT* GetRectRS();
protected:
	void Init();
	float m_timeDelay;
public: 
	static int m_mapId;
	CChooseItem* m_itemChoose;
	CScoreScense* m_scoreScense;
	bool m_isMoveComplete;
	bool m_isChoosePlay;
	bool m_isCanShowScoreScense;
};

#endif // !__CMENU_GAME_H__
