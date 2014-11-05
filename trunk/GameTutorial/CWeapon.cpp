#include "CWeapon.h"

CWeapon::CWeapon(void)
{
	this->Init();
}
	
CWeapon::CWeapon(const std::vector<int>& info)
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

void CWeapon::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 20; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 54.0f;//56.0f; //78
	this->m_height = 30.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(800.0f, 400.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = 700.0f;
	this->m_canJump = false;
	this->m_jumpMax = 0.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 180.0f;
	this->m_vyDefault = 100.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_left = false;
	this->m_angle = 0;
}

void CWeapon::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
}

void CWeapon::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CWeapon::MoveUpdate(float deltaTime)
{
	this->m_angle += 4.0 * deltaTime;
	//this->m_vx += this->m_a  * deltaTime;
	//this->m_vy += this->m_a * deltaTime * sin(this->m_angle);
	this->m_pos.x += this->m_vx * deltaTime;
	this->m_pos.y += 5.0f * sin(this->m_angle);
}
RECT* CWeapon::GetBound()
{
	return nullptr;
}

RECT* CWeapon::GetRectRS()
{
	return nullptr;
}

Box CWeapon::GetBox()
{
	return Box();
}

CWeapon::~CWeapon()
{

}