#include "CScoreScense.h"
#include "CInput.h"
#include "CStateGamePlay.h"
#include "CStateManagement.h"
#include "CDrawObject.h"
#include "CMenuGame.h"
#include "CLoadGameObject.h"

CScoreScense::CScoreScense(bool isScenseGameOver)
{
	this->m_isScenseGameOver = isScenseGameOver;
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
	#pragma region KHOI TAO CHUNG 1
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
	//
	this->lenghtlPWord = this->lenghtHIWord = 2;
	this->lenghtRestWord = 4;
	//
	string tempName = "LP";
	this->m_listLPWord = new CWord*[this->lenghtlPWord];
	for (int i = 0; i < this->lenghtlPWord; i++)
	{
		int tempNum = InitWord(tempName.at(i));
		if (tempNum != -1)
		{
			this->m_listLPWord[i] = new CWord(tempNum);
		}
	}
	//Tao moi rest
	tempName = "REST";
	this->m_listRestWord = new CWord*[this->lenghtRestWord];
	for (int i = 0; i < this->lenghtRestWord; i++)
	{
		int tempNum = InitWord(tempName.at(i));
		if (tempNum != -1)
		{
			this->m_listRestWord[i] = new CWord(tempNum);
		}
	}
	//Tao moi HI, hight score
	tempName = "HI";
	this->m_listHIWord = new CWord*[this->lenghtHIWord];
	for (int i = 0; i < this->lenghtHIWord; i++)
	{
		int tempNum = InitWord(tempName.at(i));
		if (tempNum != -1)
		{
			this->m_listHIWord[i] = new CWord(tempNum);
		}
	}
	#pragma endregion
	
	#pragma region KHOI TAO CHO GAME OVER
	//tao moi stage hoac game over
	if (this->m_isScenseGameOver)
	{
		//Khoi tao cac Lable
		tempName = "GAME OVER";
		this->lenghtStageWord = tempName.size();
		
		//tao moi lable Continue, End
		string tempContinue = "CONTINUE";
		this->lenghtContinueWord = tempContinue.size();
		this->m_listContinueWord = new CWord*[this->lenghtContinueWord];
		for (int i = 0; i < this->lenghtContinueWord; i++)
		{
			int tempNum = InitWord(tempContinue.at(i));
			if (tempNum != -1)
			{
				this->m_listContinueWord[i] = new CWord(tempNum);
			}
		}
		string tempEnd = "END";
		this->lenghtEndWord = tempEnd.size();
		this->m_listEndWord = new CWord*[this->lenghtEndWord];
		for (int i = 0; i < this->lenghtEndWord; i++)
		{
			int tempNum = InitWord(tempEnd.at(i));
			if (tempNum != -1)
			{
				this->m_listEndWord[i] = new CWord(tempNum);
			}
		}
		//Khoi tao doi tuong Choose Item
		this->m_itemChoose = new CChooseItem();
	}
	#pragma endregion
	
	#pragma region KHOI TAO CHO SCORE
	else
	{
		tempName = "STAGE";
		this->lenghtStageWord = 5;
	}
	#pragma endregion

	#pragma region KHOI TAO CHUNG 2
	this->m_listStageWord = new CWord*[this->lenghtStageWord];
	for (int i = 0; i < this->lenghtStageWord; i++)
	{
		int tempNum = InitWord(tempName.at(i));
		if (tempNum != -1)
		{
			this->m_listStageWord[i] = new CWord(tempNum);
		}
	}
	#pragma endregion
}

void CScoreScense::Update(float deltaTime)
{
	if (this->m_isScenseGameOver)
	{
		//this->Move(deltaTime);
		int te = CInput::GetInstance()->GetKeyDown();
		if (CInput::GetInstance()->IsKeyDown(DIK_RETURN))
		{
			if (this->m_itemChoose->m_SelectedId == 0)
			{
				CStateManagement::GetInstance()->ChangeState(new CStateGamePlay(CMenuGame::m_mapId));
				CContra::GetInstance()->Reset();
				CLoadGameObject::GetInstance()->ChangeMap(CMenuGame::m_mapId);
			}
			else
			{
				//Exit game
				std::exit(1);
			}
		}
		else
		if (CInput::GetInstance()->IsKeyDown(DIK_UP))
		{
			this->m_itemChoose->m_SelectedId--;
			if (this->m_itemChoose->m_SelectedId < 0)
			{
				this->m_itemChoose->m_SelectedId = 0;
			}

		}
		else
		if (CInput::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			this->m_itemChoose->m_SelectedId++;
			if (this->m_itemChoose->m_SelectedId > 0)
			{
				this->m_itemChoose->m_SelectedId = 1;
			}
		}
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
	#pragma region VE NHUNG CAI CHUNG
	CDrawObject::GetInstance()->Draw(this);
	//La man hinh game over vs diemdeu hien len
	//hien thi chu LP len
	for (int i = 0; i < this->lenghtlPWord; i++)
	{
		this->m_listLPWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 200 + i * 16, this->m_pos.y + 160));
		CDrawObject::GetInstance()->Draw(this->m_listLPWord[i]);
	}
	//hien thi diem len(LP)
	for (int i = 0; i < this->lenghtNumberScore; i++)
	{
		CDrawObject::GetInstance()->Draw(this->m_listNumberScore[i]);
	}
	//hien thi chu HI len
	for (int i = 0; i < this->lenghtHIWord; i++)
	{
		this->m_listHIWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 70 + i * 16, this->m_pos.y + 60));
		CDrawObject::GetInstance()->Draw(this->m_listHIWord[i]);
	}
	//hien thi chu  noi dung HI len
	for (int i = 0; i < this->lenghtNumberHightScore; i++)
	{
		CDrawObject::GetInstance()->Draw(this->m_listHightScoreNumber[i]);
	}
	//Luon hien vi thay doi dc
	//hien thi chu STAGE len
	for (int i = 0; i < this->lenghtStageWord; i++)
	{
		this->m_listStageWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 40 + i * 16, this->m_pos.y - 40));
		CDrawObject::GetInstance()->Draw(this->m_listStageWord[i]);
	}
	#pragma endregion

	#pragma region VE CHO MAN HINH SCORE
	//
	//Man hinh diem moi hien con game over ko hien
	if (!this->m_isScenseGameOver)
	{
		//hien thi chu REST len
		for (int i = 0; i < this->lenghtRestWord; i++)
		{
			this->m_listRestWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 205 + i * 16, this->m_pos.y + 125));
			CDrawObject::GetInstance()->Draw(this->m_listRestWord[i]);
		}
		//hien thi chu noi dung REST len
		for (int i = 0; i < this->lenghtCountAliveNumber; i++)
		{
			CDrawObject::GetInstance()->Draw(this->m_listCountAliveNumber[i]);
		}
		//hien thi chu noi dung STAGE len
		for (int i = 0; i < this->lenghtStageNumber; i++)
		{
			CDrawObject::GetInstance()->Draw(this->m_listStageNumber[i]);
		}
		
		//hien thi ten man len
		for (int j = 0; j < this->lenghtWordStateName; j++)
		{
			CDrawObject::GetInstance()->Draw(this->m_listWordStageName[j]);
		}
	}
	#pragma endregion
	
	#pragma region VE CHO MAN HINH GAME OVER
	else//Man hinh game over ve them 2 lable 'CONTINUE', 'END'
	{
		//hien thi chu noi dung CONTINUE
		for (int i = 0; i < this->lenghtContinueWord; i++)
		{
			this->m_listContinueWord[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 10 + i * 16, this->m_pos.y - 90));
			CDrawObject::GetInstance()->Draw(this->m_listContinueWord[i]);
		}

		//hien thi END len
		for (int j = 0; j < this->lenghtEndWord; j++)
		{
			this->m_listEndWord[j]->SetPos(D3DXVECTOR2(this->m_pos.x - 10 + j * 16, this->m_pos.y - 120));
			CDrawObject::GetInstance()->Draw(this->m_listEndWord[j]);
		}

		//
		D3DXVECTOR2 pos;
		if (this->m_itemChoose->m_SelectedId == 0)
			pos = D3DXVECTOR2(this->m_listContinueWord[0]->GetPos().x - 35, this->m_listContinueWord[0]->GetPos().y);
		else
			pos = D3DXVECTOR2(this->m_listEndWord[0]->GetPos().x - 35, this->m_listEndWord[0]->GetPos().y);
		this->m_itemChoose->SetPos(pos);
		CDrawObject::GetInstance()->Draw(this->m_itemChoose);
	}
	#pragma endregion
}

int CScoreScense::InitWord(char _c)
{
	int temp = -1;
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
	case ' '://Sapce
		temp = 36;
		break;
	}
	return temp;
}

void CScoreScense::InitScore(int score)
{
	this->m_ScoreMap = score;
	//Tinh toan ra so diem va so word
	stringstream ss;
	ss << this->m_ScoreMap;
	string tempScore = ss.str();
	//
	this->lenghtNumberScore = tempScore.size();
	//Khoi tao cac doi tuong chu so
	this->m_listNumberScore = new CWord*[tempScore.size()];
	
	string temp;
	for (int i = 0; i < tempScore.size(); i++)
	{
		temp = tempScore.at(i);
		this->m_listNumberScore[i] = new CWord(atoi(temp.c_str()));
		this->m_listNumberScore[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 100 + i * 16, this->m_pos.y + 160));
		//this->m_listNumberScore[i]->SetPos(D3DXVECTOR2(this->m_pos.x + 15 + i * 16, this->m_pos.y + 90));
	}
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
	this->lenghtWordStateName = tempName.size();
	this->m_listWordStageName = new CWord*[tempName.size()];
	for (int i = 0; i < tempName.size(); i++)
	{
		int tempNum = InitWord(tempName.at(i));
		if (tempNum != -1)
		{
			this->m_listWordStageName[i] = new CWord(tempNum);
			this->m_listWordStageName[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 60 + i * 16, this->m_pos.y - 80));
		}
	}
}

void CScoreScense::InitHightScore(int hightScore)
{
	//Tinh toan ra hight Score va so word
	stringstream ss;
	ss << hightScore;
	string tempHightScore = ss.str();
	//
	this->lenghtNumberHightScore = tempHightScore.size();
	//Khoi tao cac doi tuong chu so
	this->m_listHightScoreNumber = new CWord*[tempHightScore.size()];

	string temp;
	for (int i = 0; i < tempHightScore.size(); i++)
	{
		temp = tempHightScore.at(i);
		this->m_listHightScoreNumber[i] = new CWord(atoi(temp.c_str()));
		this->m_listHightScoreNumber[i]->SetPos(D3DXVECTOR2(this->m_pos.x + 20 + i * 16, this->m_pos.y + 60));
	}
}

void CScoreScense::InitCountAlive(int countAlive)
{
	//Tinh toan ra so mang va so word
	stringstream ss;
	ss << countAlive;
	string tempCountAlive = ss.str();
	//
	this->lenghtCountAliveNumber = tempCountAlive.size();
	//Khoi tao cac doi tuong chu so
	this->m_listCountAliveNumber = new CWord*[tempCountAlive.size()];

	string temp;
	for (int i = 0; i < tempCountAlive.size(); i++)
	{
		temp = tempCountAlive.at(i);
		this->m_listCountAliveNumber[i] = new CWord(atoi(temp.c_str()));
		this->m_listCountAliveNumber[i]->SetPos(D3DXVECTOR2(this->m_pos.x - 100 + i * 16, this->m_pos.y + 125));
	}
}

void CScoreScense::InitStageNumber(int stageNumberCurrent)
{
	switch (stageNumberCurrent)
	{
		case 10:
			stageNumberCurrent = 1;
			break;
		case 11:
			stageNumberCurrent = 3;
			break;
		case 12:
			stageNumberCurrent = 5;
			break;
	}
	//Tinh toan ra man hien tai va so word
	stringstream ss;
	ss << stageNumberCurrent;
	string tempStageNumber = ss.str();
	//
	this->lenghtStageNumber = tempStageNumber.size();
	//Khoi tao cac doi tuong chu so
	this->m_listStageNumber = new CWord*[tempStageNumber.size()];

	string temp;
	for (int i = 0; i < tempStageNumber.size(); i++)
	{
		temp = tempStageNumber.at(i);
		this->m_listStageNumber[i] = new CWord(atoi(temp.c_str()));
		this->m_listStageNumber[i]->SetPos(D3DXVECTOR2(this->m_pos.x + 60 + i * 16, this->m_pos.y - 40));
	}
}

RECT* CScoreScense::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

CScoreScense::~CScoreScense()
{

}