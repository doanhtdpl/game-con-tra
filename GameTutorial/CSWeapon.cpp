#include "CSWeapon.h"

CSWeapon::CSWeapon(void)
{
	this->Init();
}
	
CSWeapon::CSWeapon(const std::vector<int>& info)
{
	this->Init();//
	if(!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}

void CSWeapon::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 3;
	this->m_idType = 20; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 64.0f;//56.0f; //78
	this->m_height = 64.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(900.0f, 100.0f);
	//Khoi tao cac thong so di chuyen
	this->m_left = false;
	//
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 6;
	this->m_elapseTimeChangeFrame = 0.9f;
	this->m_increase = 1.4;
	this->m_totalFrame = 7;
	this->m_column = 7;
	//
	this->m_timeDelay = 0.0f;
}

void CSWeapon::Update(float deltaTime)
{
	this->SetFrame(deltaTime);
	this->ChangeFrame(deltaTime);
}

void CSWeapon::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CSWeapon::SetFrame(float deltaTime)
{
	if(this->m_currentFrame >= 1 && this->m_currentFrame <= 4)
	{
		this->m_elapseTimeChangeFrame = 0.03f;
	}
	else if(this->m_currentFrame <= 0)
	{
		this->m_elapseTimeChangeFrame = 1.4f;
	}
	else
	{
		this->m_elapseTimeChangeFrame = 0.45f;
	}
	//Chuyen frame
	this->m_startFrame = 0;
	this->m_endFrame = 6;
}

RECT* CSWeapon::GetBound()
{
	return nullptr;
}

RECT* CSWeapon::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CSWeapon::GetBox()
{
	return Box();
}

CSWeapon::~CSWeapon()
{

}