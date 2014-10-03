#include "DynamicObject.h"

DynamicObject::DynamicObject(void)
{
	this->m_isMoveLeft = false;
	this->m_isMoveRight = false;
	this->m_canJump = 0;
	this->_Left = false;
	this->m_vx = 0;
	this->m_vy = 0;
	this->m_jumpMax = 0;
}

DynamicObject::DynamicObject(std::vector<std::string> arr) : CGameObject(arr)
{

}

DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::move(float Delta_Time)
{
	if (this->_pos.x < this->_width / 2)
		this->_pos.x = this->_width / 2;

	if (this->m_isMoveLeft)
	{
		if (this->m_vx < 0)
		{
			this->_pos.x += this->m_vx * Delta_Time;
		}
	}

	if (this->m_isMoveRight)
	{
		if (this->m_vx > 0)
		{
			this->_pos.x += this->m_vx * Delta_Time;
		}
	}

	this->_pos.y += this->m_vy * Delta_Time;
	if (this->_pos.y < 0)
	{
		this->_isALive = false;//die
	}
}

std::string DynamicObject::className()
{
	return "Dynamic Object";
}

void DynamicObject::update(float deltatime)
{

}

void DynamicObject::update(float delta_Time, std::vector<CGameObject*> listObjectCollision)
{
	this->MoveUpdate(delta_Time);
	this->move(delta_Time);
}
