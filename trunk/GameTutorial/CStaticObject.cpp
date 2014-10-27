#include "CStaticObject.h"


CStaticObject::CStaticObject(void) : CGameObject()
{
}

CStaticObject::CStaticObject(const std::vector<int>& info) : CGameObject(info)
{

}

CStaticObject::~CStaticObject(void)
{

}

void CStaticObject::Update(float deltaTime)
{

}

void CStaticObject::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

void CStaticObject::HandleCollision(float deltatime, std::vector<CGameObject*> listObjectCollision)
{

}