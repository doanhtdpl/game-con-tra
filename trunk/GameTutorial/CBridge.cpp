#include "CBridge.h"
#include "CCollision.h"
#include "CContra.h"

CBridge::CBridge(void)
{
	this->Init();
}

CBridge::CBridge(const std::vector<int>& info)
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

void CBridge::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 9;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 256.0f;//56.0f; //78
	this->m_height = 64.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(1663.0f, 223.0f);
	//Khoi tao cac thong so di chuyen
	this->m_left = false;
	//
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.9f;
	this->m_increase = 1.4;
	this->m_totalFrame = 5;
	this->m_column = 1;
	//
	this->m_timeDelay = 0.0f;
	
	this->m_stateCurrent = STATE_BRIDGE::X4;
}

void CBridge::Update(float deltaTime)
{
	this->SetFrame(deltaTime);
	this->ChangeFrame(deltaTime);
	if (this->effect != NULL){
		this->effect->Update(deltaTime);
		if (!this->effect->IsAlive()){
			delete this->effect;
			this->effect = NULL;
		}
	}
}

void CBridge::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CBridge::SetFrame(float deltaTime)
{
	//Chuyen doi frame
	int currentFrame = this->m_currentFrame;
	switch (this->m_stateCurrent)
	{
	case STATE_BRIDGE::X4:
	{
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		break;
	}
	case STATE_BRIDGE::X3:
	{
		this->m_startFrame = 1;
		this->m_endFrame = 1;
		break;
	}
	case STATE_BRIDGE::X2:
	{
		this->m_startFrame = 2;
		this->m_endFrame = 2;
		break;
	}case STATE_BRIDGE::X:
	{
		this->m_startFrame = 3;
		this->m_endFrame = 3;
		break;
	}case STATE_BRIDGE::NONE:
	{
		this->m_startFrame = 4;
		this->m_endFrame = 4;
		break;
	}
	}
}

RECT* CBridge::GetBound()
{
	return nullptr;
}

RECT* CBridge::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CBridge::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height);
}

void CBridge::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	//Sắp va chạm > 0 và < 1
	//Hai Box Giao Nhau (Đã va chạm rồi) = 2 và moveX, moveY (độ lún)
	timeCollision = CCollision::GetInstance()->Collision(this, CContra::GetInstance(), normalX, normalY, moveX, moveY, deltaTime);
	if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
	{
		//trên - xuống normalY = 1
		//Trái phải normalX = -1
		// ==0 ko va chạm theo Y, X	
		if (this->effect == NULL){
			this->effect = new CExplosionEffect(this->GetPos());
		}
		this->m_isALive = false;
	}
}


CBridge::~CBridge()
{

}