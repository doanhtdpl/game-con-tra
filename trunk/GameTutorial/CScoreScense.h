#ifndef __CSCORE_SCENSE_H__
#define __CSCORE_SCENSE_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CWord.h"

class CScoreScense : public CStaticObject, public CAnimation
{
public:
	CScoreScense(void);
	CScoreScense(const std::vector<int>& info);
	~CScoreScense();
	std::string ClassName(){ return __CLASS_NAME__(CScoreScense); };
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	void Draw();
	void InitScore(int score);
	void InitNameStage(int mapId);
	int InitWord(char);
	RECT* GetRectRS();
protected:
	void Init();
	float m_timeDelay;
	int m_ScoreMap;
public:
	//tao 1 dong word de luu va ve diem so
	CWord** m_listNumber;
	//List luu ten man
	CWord** m_listWord;
	//Man thu n
	CWord* m_stageNumber;

	int lenghtNumber;
	int lenghtWord;
};

#endif // !__CSCORE_SCENSE_H__
