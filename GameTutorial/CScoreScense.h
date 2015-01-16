#ifndef __CSCORE_SCENSE_H__
#define __CSCORE_SCENSE_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CWord.h"
#include "CChooseItem.h"

class CScoreScense : public CStaticObject, public CAnimation
{
public:
	CScoreScense(bool);
	CScoreScense(const std::vector<int>& info);
	~CScoreScense();
	std::string ClassName(){ return __CLASS_NAME__(CScoreScense); };
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	void Draw();
	void InitScore(int score);
	void InitNameStage(int mapId);
	void InitHightScore(int hightScore);
	void InitCountAlive(int countAlive);
	void InitStageNumber(int stageNumberCurrent);
	int InitWord(char);
	RECT* GetRectRS();
protected:
	void Init();
	float m_timeDelay;
	int m_ScoreMap;
	bool m_isScenseGameOver;//Cho biet la man diem qua man hay man hinh diem game over
public:
	//Choose item
	CChooseItem* m_itemChoose;
	//tao 1 dong word de luu va ve diem so
	CWord** m_listNumberScore;
	//List luu ten man
	CWord** m_listWordStageName;
	//Man thu n
	CWord** m_listStageNumber;
	//So man cua contra
	CWord** m_listCountAliveNumber;
	//Hight Score cua game
	CWord** m_listHightScoreNumber;
	//List luu label 'lP'//Score
	CWord** m_listLPWord;
	//List luu label 'REST'//So mang
	CWord** m_listRestWord;
	//List luu label 'HI'//Hight Score
	CWord** m_listHIWord;
	//List luu label 'STAGE'//Man
	CWord** m_listStageWord;
	//List luu Label "CONTINUE"
	CWord** m_listContinueWord;
	//List luu Label "END"
	CWord** m_listEndWord;
	///
	int lenghtNumberScore;//do dai cua diem
	int lenghtWordStateName;//Do dai cua ten man
	int lenghtNumberHightScore;//do dai cua diem cao nhat
	int lenghtCountAliveNumber;//Do dai cua so mang contra
	int lenghtStageNumber;//Do dai cua man thu
	int lenghtlPWord;//do dai cua diem
	int lenghtRestWord;//Do dai cua ten man
	int lenghtHIWord;//Do dai cua ten man
	int lenghtStageWord;//Do dai cua ten man
	int lenghtContinueWord;//Do dai cua Label CONTINUE
	int lenghtEndWord;//Do dai cua Lable END
	//Ham lay ra no la man hinh game over hay man hinh diem
	bool IsScenseGameOver()
	{
		return this->m_isScenseGameOver;
	}
};
#endif // !__CSCORE_SCENSE_H__
