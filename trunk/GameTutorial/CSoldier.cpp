#include "CSoldier.h"
#include "CPoolingObject.h"
#include "CCollision.h"
#include "CContra.h"
#include "CLoadGameObject.h"

CSoldier::CSoldier(void)
{
	this->Init();
}
	
CSoldier::CSoldier(const std::vector<int>& info)
{
	this->Init();//
	if(!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}
CSoldier::CSoldier(D3DXVECTOR2 pos)
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 40.0f;//56.0f; //78
	this->m_height = 66.0f; //88.0f; //84
	this->m_pos = pos;
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 300.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = 0;
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 6;
	this->m_column = 6;
	//
	this->m_isShoot = false;
	this->m_stateCurrent = SOLDIER_STATE::S_IS_JOGGING;
}

void CSoldier::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 40.0f;//56.0f; //78
	this->m_height = 66.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(200.0f, 400.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 140.0f;
	this->m_vyDefault = 400.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = 0;
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 6;
	this->m_column = 6;
	//
	this->m_isShoot = false;
	this->m_stateCurrent = SOLDIER_STATE::S_IS_JOGGING;
	//Test
	this->m_jump = false;
	this->m_waitForChangeSprite = 0.0f;
}

void CSoldier::Update(float deltaTime)
{
	if (this->IsAlive())
	{
		this->SetFrame(deltaTime);
		this->ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
	}
}

void CSoldier::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	if (this->IsAlive())
	{
		this->SetFrame(deltaTime);
		this->ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
		this->OnCollision(deltaTime, listObjectCollision);
	}
}

void CSoldier::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	for (std::vector<CBullet*>::iterator it = CPoolingObject::GetInstance()->m_listBulletOfObject.begin(); it != CPoolingObject::GetInstance()->m_listBulletOfObject.end();)
	{
		CBullet* obj = *it;
		timeCollision = CCollision::GetInstance()->Collision(obj, this, normalX, normalY, moveX, moveY, deltaTime);
		if((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
		{
			// Gan trang thai die cho doi tuong
			this->m_stateCurrent = SOLDIER_STATE::S_IS_DIE;
			// Xoa vien dan ra khoi d.s
			it = CPoolingObject::GetInstance()->m_listBulletOfObject.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (this->m_stateCurrent != SOLDIER_STATE::S_IS_DIE)
	{
			//Kiem tra va cham voi ground
		bool checkColWithGround = false;
		// xet va cham vs ground
		for (std::vector<CGameObject*>::iterator it = listObjectCollision->begin(); it != listObjectCollision->end(); it++)
		{
			CGameObject* obj = *it;
			//Lay thoi gian va cham
			//Neu doi tuong la ground va dang va cham
			if((obj->GetIDType() == 15 && obj->GetID() == 1) && !checkColWithGround)
			{
				timeCollision = CCollision::GetInstance()->Collision(this, obj, normalX, normalY, moveX, moveY, deltaTime);
				if((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
				{
					if(normalY > 0)
					{
						checkColWithGround = true;
						this->m_stateCurrent = SOLDIER_STATE::S_IS_JOGGING;
						if( timeCollision == 2.0f)
						{
							//this->m_isJumping = false;
							this->m_pos.y += moveY;
							this->m_vy = 0;
							this->m_a = 0;
						}
						else
						{
							//this->m_pos.y += timeCollision*this->m_vy * deltaTime;
							//this->m_a = 0;
						}
					}
				}
			}
		}

		if(!checkColWithGround)
		{
			this->m_a = -700.0f;
			//this->m_left = !this->m_left;
			if (this->m_jump)
			{
				if(this->m_vy == 0.0f)
					this->m_vy = this->m_vyDefault;
				this->m_stateCurrent = SOLDIER_STATE::S_IS_JUMP;
			}
			else
			{
				this->m_left = !this->m_left;
			}
		}
	}
	
}

void CSoldier::MoveUpdate(float deltaTime)
{
	if(!(this->m_isJumping && this->m_canJump))
	{
		this->m_vx = this->m_vxDefault;
		//this->m_vy += this->m_a * deltaTime;
	}
	//Neu no roi khoi cau, hoac roi khoi nen thi chuyen sang trang thai nhay
#pragma region TRANG_THAI_CHAY
	if(this->m_stateCurrent == SOLDIER_STATE::S_IS_JOGGING)
	{
		if(!this->m_left)
		{
			this->m_vx = m_vxDefault;
			if (this->m_vx < 0)
			{	
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}else
		{
			this->m_vx = -m_vxDefault;
			if (this->m_vx > 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}

		// test nhay cho soldier
		/*m_s += int(this->m_vx * deltaTime);
		if(m_s >= 300)
		{
			this->m_isJumping = true;
			this->m_stateCurrent = SOLDIER_STATE::S_IS_JUMP;
			this->m_vy = this->m_vyDefault;
			this->m_vxDefault = 150.0f;
			m_s = this->m_pos.y;
		}*/
	}
#pragma endregion
#pragma region TRANG_THAI_NHAY
	else if(this->m_stateCurrent == SOLDIER_STATE::S_IS_JUMP)
	{
		//this->m_vx += this->m_a * deltaTime;
		if(!this->m_left)
		{
			this->m_vx = m_vxDefault;
			if (this->m_vx < 0)
			{	
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}else
		{
			this->m_vx = -m_vxDefault;
			if (this->m_vx > 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}
		this->m_vy += this->m_a * deltaTime;
		this->m_pos.y += this->m_vy * deltaTime;
		/*if(this->m_pos.y <= this->m_s)
		{
			this->m_pos.y = this->m_s;
			this->m_stateCurrent = SOLDIER_STATE::S_IS_STANDING;
			this->m_vxDefault = 100.0f;
			this->m_isJumping = false;
			this->m_s = 0;
		}*/
	}
#pragma endregion
	else
	{
		this->m_isShoot = true;
		this->m_vx = 0;
	}
	this->m_pos.x += this->m_vx * deltaTime;
	this->m_vy += this->m_a * deltaTime;
	this->m_pos.y += this->m_vy * deltaTime;
}

void CSoldier::BulletUpdate(float deltaTime)
{
	if(this->m_isShoot)
	{
		//Khoi tao mot vien dan va add vao quadtree
		this->m_stateCurrent = SOLDIER_STATE::S_IS_JOGGING;
	}
}

void CSoldier::SetFrame(float deltaTime)
{
	//Chuyen doi frame
	switch (this->m_stateCurrent)
	{
	case SOLDIER_STATE::S_IS_JOGGING:
		{
			this->m_startFrame = 0;
			this->m_endFrame = 5;
			break;
		}
	case SOLDIER_STATE::S_IS_JUMP:
		{
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			break;
		}
	case SOLDIER_STATE::S_IS_STANDING:
		{
			this->m_startFrame = 0;
			this->m_endFrame = 0;
			break;
		}
	case SOLDIER_STATE::S_IS_DIE:
		{
			this->m_currentFrame = 5;
			this->m_startFrame = 5;
			this->m_endFrame = 5;
			if (this->m_waitForChangeSprite <= 0.2f)
			{
				this->m_waitForChangeSprite += deltaTime;
				this->m_pos.y += 5;
				this->m_pos.x -= 2;
			}
			else
			{
				// Lay doi tuong ra
				CEnemyEffect* effect = CPoolingObject::GetInstance()->GetEnemyEffect();
				effect->SetAlive(true);
				effect->SetPos(this->m_pos);

				this->m_isALive = false;
			}
			break;
		}
	default:
		break;
	}
}

RECT* CSoldier::GetBound()
{
	return nullptr;
}

RECT* CSoldier::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CSoldier::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}

void CSoldier::setJump(bool jump)
{
	this->m_jump = jump;
}

CSoldier::~CSoldier()
{

}