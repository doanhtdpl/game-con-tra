#include "CGameObject.h"
using namespace std;

CGameObject::CGameObject(void)
{
	//_ID = 0;
	m_isALive = true;
	m_rectRS = NULL;
	m_isAnimatedSprite = false;
	this->m_height = 0;
	this->m_width = 0;
	this->m_posZ = 0;
}

CGameObject::CGameObject(std::vector<std::string> arr)
{
	this->m_posZ = 0;
}

CGameObject::~CGameObject(void)
{
}

std::string CGameObject::ClassName()
{
	return __CLASS_NAME__(CGameObject);
}

void CGameObject::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

void CGameObject::Update(float deltaTime)
{

}

RECT CGameObject::GetRect()
{
	this->m_rect.top = m_pos.y + this->m_height / 2;
	this->m_rect.bottom = this->m_rect.top - this->m_height;

	this->m_rect.left = m_pos.x - this->m_width / 2;
	this->m_rect.right = this->m_rect.left + this->m_width;

	return this->m_rect;
}