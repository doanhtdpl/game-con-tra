﻿#include "CBridge.h"
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
	this->m_currentTime = 1.3f;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 1.3f;
	this->m_increase = 1;
	this->m_totalFrame = 5;
	this->m_column = 1;
	this->m_startFrame = 0;
	this->m_endFrame = 4;
	//
	this->m_timeDelay = 0.0f;
	
	this->m_stateCurrent = STATE_BRIDGE::X4;
	this->m_isCollisionContra = false;


	//Tao hieu dung
	this->effect = new CExplosionEffect(D3DXVECTOR2(this->m_pos.x - 5*this->m_width/8, this->m_pos.y + this->m_height/4));
	this->effect->SetAlive(false);
}

void CBridge::Update(float deltaTime)
{
	//this->SetFrame(deltaTime); //Cai ham nay bo vao cho changeFrame, tuc la sau moi lan Frame thay doi thi set lai frame
	this->ChangeFrame(deltaTime);
	if (this->effect != NULL && this->effect->IsAlive()){
		this->effect->Update(deltaTime);
	}
}

void CBridge::ChangeFrame(float deltaTime)
{
	if (m_isCollisionContra)
	{
		this->m_currentTime += deltaTime;
		if (this->m_currentTime > this->m_elapseTimeChangeFrame)
		{
			this->m_currentFrame += this->m_increase;
			if (this->m_currentFrame > this->m_endFrame){
				this->m_isALive = false;
				this->effect->SetAlive(false);
				this->m_isCollisionContra = false;
			}
			if (this->m_currentFrame > this->m_endFrame || this->m_currentFrame < this->m_startFrame)
			{
				this->m_currentFrame = this->m_startFrame;
			}
			this->m_currentTime -= this->m_elapseTimeChangeFrame;
			if (this->m_currentFrame > this->m_startFrame){
				this->SetFrame(deltaTime);
			}
		//	this->m_pos.x += 32 * this->m_currentFrame;
		}
	}
}


void CBridge::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CBridge::SetFrame(float deltaTime)
{
	D3DXVECTOR2 posEff = this->effect->GetPos();
	this->effect->SetPos(D3DXVECTOR2(posEff.x + this->m_width / 4, posEff.y));
	this->effect->SetAlive(true);
	
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
	switch (this->m_currentFrame)
	{
		case 0:
			return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height);
		case 1:
			return Box(this->m_pos.x+32, this->m_pos.y, this->m_width-64, this->m_height);
		case 2:
			return Box(this->m_pos.x+32*2, this->m_pos.y, this->m_width-64*2, this->m_height);
		case 3:			
			return Box(this->m_pos.x+32*3, this->m_pos.y, this->m_width-64*3, this->m_height);
	}
	return Box(this->m_pos.x, this->m_pos.y, 0, 0);
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
		this->m_isCollisionContra = true;
	}
}


CBridge::~CBridge()
{

}