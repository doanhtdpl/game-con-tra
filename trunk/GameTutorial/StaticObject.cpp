#include "StaticObject.h"


StaticObject::StaticObject(void) :CGameObject()
{
}

StaticObject::StaticObject(std::vector<std::string> arr) : CGameObject(arr)
{

}

StaticObject::~StaticObject(void)
{
}

std::string StaticObject::className()
{
	return "Static Object";
}

void StaticObject::update(float deltaTime)
{

}

void StaticObject::update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}
