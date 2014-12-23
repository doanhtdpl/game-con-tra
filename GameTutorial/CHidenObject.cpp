#include "CHidenObject.h"
#include "CCamera.h"
#include "CCollision.h"
#include "CContra.h"
#include "CSoldier.h"
#include "CPoolingObject.h"


bool CHidenObject::m_createEnemy = false;
bool CHidenObject::m_createWeapon = false;
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
	this->m_waitForCreateEnemy = 1.0f;
	this->countWeapon = 0;
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
			this->m_type = HIDEN_OBJECT_TYPE::CREATE_WEAPON;
			break;
		case 15004:
			this->m_type = HIDEN_OBJECT_TYPE::CREATE_ENEMY;
			break;
		case 15006:
			this->m_type = HIDEN_OBJECT_TYPE::ENEMY_POS_R;
			break; 
		case 15007:
			this->m_type = HIDEN_OBJECT_TYPE::ENEMY_POS_L;
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

void CHidenObject::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	if (this->m_type == HIDEN_OBJECT_TYPE::CREATE_ENEMY)
	{
		if (CCollision::GetInstance()->Collision(CContra::GetInstance(), this))
		{
			CHidenObject::m_createEnemy = true;
		}
		else
		{
			CHidenObject::m_createEnemy = false;
		}
	}

	// create enemy posision
	if (this->m_type == HIDEN_OBJECT_TYPE::ENEMY_POS_L || this->m_type == HIDEN_OBJECT_TYPE::ENEMY_POS_R)
	{
		if (CHidenObject::m_createEnemy)
		{
			// Sinh enemy 
			this->m_waitForCreateEnemy += deltaTime;

			if (this->m_waitForCreateEnemy > 1.0f)
			{
				this->m_waitForCreateEnemy = 0.0f;

				CSoldier* soldier = CPoolingObject::GetInstance()->GetSoliderObject();
				if (soldier != nullptr)
				{
					soldier->SetAlive(true);
					// Random jump
					soldier->setJump(rand()%2 == 1);
					// set left right
					if (this->m_id == 7)
						soldier->SetLeft(false);
					else
						soldier->SetLeft(true);
					// Set vi tri cho soldier
					D3DXVECTOR2 soldierPos = this->m_pos;
					soldierPos.x = CContra::GetInstance()->GetPos().x + 100;
					soldier->SetPos(this->m_pos);
				}
			}
		}
	}

	// Create weapon
	if (this->m_type == HIDEN_OBJECT_TYPE::CREATE_WEAPON)
	{
		if (CCollision::GetInstance()->Collision(CContra::GetInstance(), this))
		{
			CHidenObject::m_createWeapon = true;
			// tao weapon
		}
	}

	if (CHidenObject::m_createWeapon)
	{
		if (this->m_idType == 14 && this->countWeapon == 0)
		{
			CWeapon* weapon = CPoolingObject::GetInstance()->GetWeapon();
			weapon->SetID(this->m_id);
			weapon->Init();
			weapon->SetPos(this->GetPos());
			weapon->SetAlive(true);

			this->countWeapon ++;
			CHidenObject::m_createWeapon = false;
		}
	}
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