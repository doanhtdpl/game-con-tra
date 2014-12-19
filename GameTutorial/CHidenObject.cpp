#include "CHidenObject.h"
#include "CCamera.h"

CHidenObject::CHidenObject() : CStaticObject()
{
	this->m_id = 1;
	this->m_idType = 15;
	this->m_width = 1450;
	this->m_height = 10;
	this->m_pos = D3DXVECTOR2(735.0f, 5.0f);
	this->m_isALive = true;
}

CHidenObject::CHidenObject(const std::vector<int>& info) : CStaticObject()
{
	this->m_isALive = true;//
	if(!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
		switch (info.at(0))
		{
		case 15001:
			this->m_type = HIDEN_OBJECT_TYPE::ON_GROUND;
			break;
		case 15002:
			this->m_type = HIDEN_OBJECT_TYPE::UNDER_WATER;
			break;
		case 15003:
			this->m_type = HIDEN_OBJECT_TYPE::CREATE_ENEMY;
			break;
		default:
			break;
		}
	}
}

CHidenObject::~CHidenObject()
{

}

void CHidenObject::Update(float deltaTime)
{

}

Box CHidenObject::GetBox()
{
	///D3DXVECTOR3 pos = CCamera::GetInstance()->GetPointTransform(this->m_pos.x, this->m_pos.y);
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, 0, 0);
}

void CHidenObject::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

//Sang test
RECT* CHidenObject::GetRectRS()
{
	RECT* rectRS = new RECT();
	rectRS->left = 0;
	rectRS->right = 64;
	rectRS->top = 0 ;
	rectRS->bottom = 64;

	return rectRS;
}