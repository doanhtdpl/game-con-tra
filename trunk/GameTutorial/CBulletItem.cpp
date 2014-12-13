#include "CBulletItem.h"

CBulletItem::CBulletItem(void)
{
	this->Init();
}

CBulletItem::CBulletItem(D3DXVECTOR2 pos)
{
	this->Init();
	this->m_pos = pos;
}

CBulletItem::CBulletItem(const std::vector<int>& info)
{
	this->Init();//
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}

void CBulletItem::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 8;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 54.0f;//56.0f; //78
	this->m_height = 30.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(1100.0f, 200.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 10;
	this->m_column = 10;

	this->m_stateItem = STATE_BULLET_ITEM::BULLET_ITEM_L;
	this->m_angle = 0;
}

void CBulletItem::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	
}

void CBulletItem::MoveUpdate(float deltaTime)
{
	this->m_angle += 4.0 * deltaTime;
	//this->m_vx += this->m_a  * deltaTime;
	//this->m_vy += this->m_a * deltaTime * sin(this->m_angle);
	this->m_pos.x += this->m_vx * deltaTime;
	this->m_pos.y += 5.0f * sin(this->m_angle);
}

void CBulletItem::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{

}

void CBulletItem::SetFrame()
{
	switch (this->m_stateItem)
	{
	case STATE_BULLET_ITEM::BULLET_ITEM_B:
		{
			this->m_startFrame = 2;
			this->m_endFrame = 2;
			break;
		}
	case STATE_BULLET_ITEM::BULLET_ITEM_F:
		{
			this->m_startFrame = 3;
			this->m_endFrame = 3;
			break;
		}
	case STATE_BULLET_ITEM::BULLET_ITEM_L:
		{
			this->m_startFrame = 5;
			this->m_endFrame = 5;
			break;
		}
	case STATE_BULLET_ITEM::BULLET_ITEM_M:
		{
			this->m_startFrame = 1;
			this->m_endFrame = 1;
			break;
		}
	case STATE_BULLET_ITEM::BULLET_ITEM_R:
		{
			this->m_startFrame = 6;
			this->m_endFrame = 6;
			break;
		}
	case STATE_BULLET_ITEM::BULLET_ITEM_S:
		{
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			break;
		}
		default:
		{
			break;
		}
	}
}

RECT* CBulletItem::GetBound()
{
	return nullptr;
}

RECT* CBulletItem::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CBulletItem::GetBox()
{
	return Box();
}

CBulletItem::~CBulletItem()
{

}