#include "CScoreScense.h"
#include "CInput.h"
#include "CStateGamePlay.h"
#include "CStateManagement.h"
#include "CDrawObject.h"
#include "CMenuGame.h"
#include "CLoadGameObject.h"

CScoreScense::CScoreScense(void)
{
	this->Init();
}

CScoreScense::CScoreScense(const std::vector<int>& info)
{
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
	this->Init();//
}

void CScoreScense::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 60;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 512.0f;
	this->m_height = 448.0f;
	//Khoi tao cac thong so di chuyen
	this->m_left = false;
	//
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 1.3f;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.40f;
	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
	this->m_startFrame = 0;
	this->m_endFrame = 1;
	//
	this->m_timeDelay = 3.0f;
}

void CScoreScense::Update(float deltaTime)
{
	//this->Move(deltaTime);
	if (CInput::GetInstance()->GetKeyDown() == DIK_RETURN)
	{
		CStateManagement::GetInstance()->ChangeState(new CStateGamePlay(CMenuGame::m_mapId));
		CContra::GetInstance()->Reset();
		CLoadGameObject::GetInstance()->ChangeMap(CMenuGame::m_mapId);
	}
	else
	if (CInput::GetInstance()->GetKeyDown() == DIK_ESCAPE)
	{
		//Exit game
		std::exit(1);
	}
}

void CScoreScense::Move(float deltaTime)
{
	if (this->m_pos.x > this->m_width / 2)
	{
		this->m_pos.x -= 2;
	}
}

void CScoreScense::Draw()
{
	CDrawObject::GetInstance()->Draw(this);
	//hien thi diem len
	for (int i = 0; i < this->lenghtNumber; i++)
	{
		CDrawObject::GetInstance()->Draw(this->m_listNumber[i]);
	}
	//hien thi ten man
	for (int j = 0; j < this->lenghtWord; j++)
	{
		CDrawObject::GetInstance()->Draw(this->m_listWord[j]);
	}
}

void CScoreScense::InitScore(int score)
{
	this->m_ScoreMap = score;
	//Tinh toan ra so diem va so word
	stringstream ss;
	ss << this->m_ScoreMap;
	string tempScore = ss.str();
	//
	this->lenghtNumber = tempScore.size();
	//Khoi tao cac doi tuong chu so
	this->m_listNumber = new CWord*[tempScore.size()];
	
	string temp;
	for (int i = 0; i < tempScore.size(); i++)
	{
		temp = tempScore.at(i);
		this->m_listNumber[i] = new CWord(atoi(temp.c_str()));
		this->m_listNumber[i]->SetPos(D3DXVECTOR2(this->m_pos.x + i * 16, this->m_pos.y));
	}
}

int CScoreScense::InitWord(char _c)
{
	int temp = 0;
	switch (_c)
	{
		case 'A'://a
			temp = 10;
			break;
		case 'B'://b
			temp = 11;
			break;
		case 'C'://c
			temp = 12;
			break;
		case 'D'://d
			temp = 13;
			break;
		case 'E'://e
			temp = 14;
			break;
		case 'F'://f
			temp = 15;
			break;
		case 'G'://g
			temp = 16;
			break;
		case 'H'://h
			temp = 17;
			break;
		case 'I'://i
			temp = 18;
			break;
		case 'J'://j
			temp = 19;
			break;
		case 'K'://k
			temp = 20;
			break;
		case 'L'://l
			temp = 21;
			break;
		case 'M'://m
			temp = 22;
			break;
		case 'N'://n
			temp = 23;
			break;
		case 'O'://o
			temp = 24;
			break;
		case 'P'://p
			temp = 25;
			break;
		case 'Q'://q
			temp = 26;
			break;
		case 'R'://r
			temp = 27;
			break;
		case 'S'://s
			temp = 28;
			break;
		case 'T'://t
			temp = 29;
			break;
		case 'U'://u
			temp = 30;
			break;
		case 'V'://v
			temp = 31;
			break;
		case 'W'://w
			temp = 32;
			break;
		case 'X'://x
			temp = 33;
			break;
		case 'Y'://y
			temp = 34;
			break;
		case 'Z'://z
			temp = 35;
			break;
	}
	return temp;
}

void CScoreScense::InitNameStage(int mapId)
{
	string tempName;
	switch (mapId)
	{
	case 10:
		tempName = __NAME_MAP_1__;
		break;
	case 11:
		tempName = __NAME_MAP_3__;
		break;
	case 12:
		tempName = __NAME_MAP_5__;
		break;
	}
	this->lenghtWord = tempName.size();
	this->m_listWord = new CWord*[tempName.size()];
	for (int i = 0; i < tempName.size(); i++)
	{
		int tempNum = InitWord(tempName.at(i));
		this->m_listWord[i] = new CWord(tempNum);
		this->m_listWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x + i * 16, this->m_pos.y + 100));
	}
}

RECT* CScoreScense::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

CScoreScense::~CScoreScense()
{

}