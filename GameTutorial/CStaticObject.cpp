#include "CStaticObject.h"


CStaticObject::CStaticObject(void) : CGameObject()
{
}

CStaticObject::CStaticObject(std::vector<std::string> arr) : CGameObject(arr)
{

}

CStaticObject::~CStaticObject(void)
{
}

std::string CStaticObject::ClassName()
{
	return __CLASS_NAME__(CStaticObject);
}

void CStaticObject::Update(float deltaTime)
{

}

void CStaticObject::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}
