#include "CGameObject.h"
using namespace std;

CGameObject::CGameObject(void)
{
	//_ID = 0;
	_isALive = true;
	_rectRS = NULL;
	_isAnimatedSprite = false;
	this->_height = 0;
	this->_width = 0;
	this->z = 0;
}

CGameObject::CGameObject(std::vector<std::string> arr)
{
	this->z = 0;
}

CGameObject::~CGameObject(void)
{
}

std::string CGameObject::className()
{
	return "Game Object";
}

void CGameObject::update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

void CGameObject::update(float deltaTime)
{

}

RECT CGameObject::getRect()
{
	this->_rect.top = _pos.y + this->_height / 2;
	this->_rect.bottom = this->_rect.top - this->_height;

	this->_rect.left = _pos.x - this->_width / 2;
	this->_rect.right = this->_rect.left + this->_width;

	return this->_rect;
}