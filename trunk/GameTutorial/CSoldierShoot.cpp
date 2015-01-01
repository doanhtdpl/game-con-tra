#include "CSoldierShoot.h"
#include "CPoolingObject.h"
#include "CCollision.h"
#include "CContra.h"
#include "CLoadGameObject.h"
#include "CCamera.h"

CSoldierShoot::CSoldierShoot(void)
{
	this->Init();
}

CSoldierShoot::CSoldierShoot(const std::vector<int>& info)
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

void CSoldierShoot::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 3;
	this->m_idType = 12;
	this->m_idImage = 3;
	this->m_isALive = false;
	this->m_isAnimatedSprite = true;
	this->m_width = 50.0f;
	this->m_height = 66.0f;
	//this->m_pos = D3DXVECTOR2(550.0f, 180.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 80.0f;
	this->m_vyDefault = 400.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = 0;
	this->m_left = true;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 9;
	this->m_column = 9;
	//
	this->m_isShoot = false;
	this->m_allowShoot = true;
	this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_JOGGING;
	//Test
	this->m_jump = true;
	this->m_flag = false;
	this->m_waitForChangeSprite = 0.0f;
	this->m_countRepeat = 0;
	//
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.80f;
	this->m_timeDelayBullet = 0.10f;
}

void CSoldierShoot::Update(float deltaTime)
{
	if (this->IsAlive())
	{
		this->ChangeFrame(deltaTime);
		this->BulletUpdate(deltaTime);
		this->MoveUpdate(deltaTime);
		this->SetFrame(deltaTime);
	}
	else
		this->BulletUpdate(deltaTime);
}

void CSoldierShoot::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
	if (this->IsAlive())
	{
		this->SetFrame(deltaTime);
		this->ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
		this->BulletUpdate(deltaTime);
		this->OnCollision(deltaTime, listObjectCollision);
	}
}

void CSoldierShoot::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
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
		if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
		{
			// Gan trang thai die cho doi tuong
			this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_DIE;
			// Xoa vien dan ra khoi d.s
			it = CPoolingObject::GetInstance()->m_listBulletOfObject.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (this->m_stateCurrent != SOLDIER_SHOOT_STATE::SS_IS_DIE)
	{
		//Kiem tra va cham voi ground
		bool checkColWithGround = false;
		// xet va cham vs ground
		for (std::vector<CGameObject*>::iterator it = listObjectCollision->begin(); it != listObjectCollision->end(); it++)
		{
			CGameObject* obj = *it;
			//Lay thoi gian va cham
			//Neu doi tuong la ground va dang va cham
			if (((obj->GetIDType() == 15 && (obj->GetID() == 1 || obj->GetID() == 8)) || (obj->GetIDType() == 16 && obj->GetID() == 1)) && !checkColWithGround)
			{
				timeCollision = CCollision::GetInstance()->Collision(this, obj, normalX, normalY, moveX, moveY, deltaTime);
				if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
				{
					if (normalY > 0)
					{
						checkColWithGround = true;
						if (this->m_stateCurrent == SOLDIER_SHOOT_STATE::SS_IS_JUMP)
						{
							if (this->m_vy < -200.0f)
							{
								if (timeCollision == 2.0f)
								{
									//this->m_isJumping = false;
									this->m_pos.y += moveY;
									this->m_vy = 0;
									this->m_a = 0;

									//if (!this->m_stateCurrent == SOLDIER_SHOOT_STATE::SS_IS_STANDING)
									//{
									this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_JOGGING;

									//}
								}

							}
						}
						else
						{
							if (timeCollision == 2.0f)
							{
								//this->m_isJumping = false;
								this->m_pos.y += moveY;
								this->m_vy = 0;
								this->m_a = 0;
								if (!this->m_stateCurrent == SOLDIER_SHOOT_STATE::SS_IS_STANDING)
								{
									this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_JOGGING;
								}
							}
						}
					}
				}
			}
		}

		if (!checkColWithGround)
		{
			this->m_a = -700.0f;

			if (this->m_jump)
			{
				if (this->m_vy == 0.0f)
					this->m_vy = this->m_vyDefault;
				this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_JUMP;
			}
			else
			{
				// Soldier quay dau nguoc lai.
				this->m_left = !this->m_left;
				this->m_countRepeat++;
				if (m_countRepeat > 2)
				{
					this->m_countRepeat = 0;
					this->m_jump = true;
				}
				// Xet gia tri tiep theo la nhay.
				//this->m_jump = true;
			}
		}
	}

}

void CSoldierShoot::MoveUpdate(float deltaTime)
{
	if (!(this->m_isJumping && this->m_canJump))
	{
		this->m_vx = this->m_vxDefault;
	}
	//Neu no roi khoi cau, hoac roi khoi nen thi chuyen sang trang thai nhay
#pragma region TRANG_THAI_CHAY
	if (this->m_stateCurrent == SOLDIER_SHOOT_STATE::SS_IS_JOGGING)
	{
		if (!this->m_left)
		{
			this->m_vx = m_vxDefault;
			if (this->m_vx < 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}
		else
		{
			this->m_vx = -m_vxDefault;
			if (this->m_vx > 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}
	}
#pragma endregion
#pragma region TRANG_THAI_NHAY
	else if (this->m_stateCurrent == SOLDIER_SHOOT_STATE::SS_IS_JUMP)
	{
		//this->m_vx += this->m_a * deltaTime;
		if (!this->m_left)
		{
			this->m_vx = m_vxDefault;
			if (this->m_vx < 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}
		else
		{
			this->m_vx = -m_vxDefault;
			if (this->m_vx > 0)
			{
				this->m_pos.x += int(this->m_vx * deltaTime);
			}
		}
		this->m_vy += this->m_a * deltaTime;
		this->m_pos.y += this->m_vy * deltaTime;
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

	// Xet' alive = false khi soldier ra khoi man hinh
	D3DXVECTOR3 pos;
	pos = CCamera::GetInstance()->GetPointTransform(this->m_pos.x, this->m_pos.y);
	if (pos.x > __SCREEN_WIDTH + 100 || pos.x < -100 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
	{
		this->m_isALive = false;
	}
}

void CSoldierShoot::BulletUpdate(float deltaTime)
{
	//Khoi tao mot vien dan va add vao quadtree
#pragma region THIET LAP GOC BAN

#pragma endregion

#pragma region THIET LAP TRANG THAI BAN
	//Kiem tra xem gan contra hay ko rui ban
	D3DXVECTOR2 posContra = CContra::GetInstance()->GetPos();
	if (posContra.y >= (this->m_pos.y - this->m_height / 3) && posContra.y <= (this->m_pos.y + this->m_height) &&
		abs(posContra.x - this->m_pos.x) <= 180 && abs(posContra.x - this->m_pos.x) >= 130)
	{
		if (posContra.x - this->m_pos.x > 0){
			this->m_bulletCount = 0;
		}
		else
		{
			if (!this->m_flag)
			{
				this->m_bulletCount = 0;
				this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_STANDING;
				this->m_isShoot = true;
				this->m_flag = true;
			}
		}
	}
	else
		this->m_flag = false;
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	if (this->m_left)
	{
		offset.x = -this->m_width / 2 - 5;
		offset.y = 16;
	}
	else
	{
		offset.x = this->m_width / 2 + 5;
		offset.y = 16;
	}
#pragma endregion

#pragma region THIET LAP TOC DO DAN

	if (this->m_isShoot)
	{
		if (this->m_currentFrame == 8)
		{
			if (m_bulletCount <= 1)
			{
				if (this->m_timeDelayBullet <= 0.0f)
				{
					this->m_timeDelayBullet = 0.10f;

					CBullet_N* bullet = new CBullet_N(PI, this->m_pos, offset, !this->m_left);
					bullet->m_isContra = false;
					m_listBullet.push_back(bullet);
					m_bulletCount++;
				}
				else
				{
					this->m_timeDelayBullet -= deltaTime;
				}
			}
		}
	}
	//Update trang thai dan
	D3DXVECTOR3 pos;
	for (int i = 0; i < this->m_listBullet.size(); i++)
	{
		this->m_listBullet.at(i)->Update(deltaTime);
		pos.x = this->m_listBullet.at(i)->GetPos().x;
		pos.y = this->m_listBullet.at(i)->GetPos().y;
		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		if (pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
		{
			delete this->m_listBullet.at(i);
			this->m_listBullet.erase(this->m_listBullet.begin() + i);
		}
	}
#pragma endregion
}

void CSoldierShoot::SetFrame(float deltaTime)
{
	//Chuyen doi frame
	switch (this->m_stateCurrent)
	{
	case SOLDIER_SHOOT_STATE::SS_IS_JOGGING:
	{
											   this->m_startFrame = 0;
											   this->m_endFrame = 5;
											   break;
	}
	case SOLDIER_SHOOT_STATE::SS_IS_JUMP:
	{
											this->m_startFrame = 6;
											this->m_endFrame = 6;
											break;
	}
	case SOLDIER_SHOOT_STATE::SS_IS_STANDING:
	{
												if (this->m_isShoot)
												{
													this->m_startFrame = 7;
													this->m_endFrame = 8;

													if (this->m_timeDelay <= 0.0f)
													{
														if (this->m_currentFrame == 7)
														{
															this->m_bulletCount = 0;
														}
														this->m_timeDelay = 0.80f;
														this->m_stateCurrent = SOLDIER_SHOOT_STATE::SS_IS_JOGGING;
														this->m_flag = true;
													}
													else
														this->m_timeDelay -= deltaTime;
												}
												else
												{
													this->m_startFrame = 7;
													this->m_endFrame = 7;
												}
												this->m_vx = 0;


												break;
	}
	case SOLDIER_SHOOT_STATE::SS_IS_DIE:
	{
										   this->m_currentFrame = 6;
										   this->m_startFrame = 6;
										   this->m_endFrame = 6;
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

RECT* CSoldierShoot::GetBound()
{
	return nullptr;
}

RECT* CSoldierShoot::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CSoldierShoot::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}

void CSoldierShoot::setJump(bool jump)
{
	this->m_jump = jump;
}

CSoldierShoot::~CSoldierShoot()
{

}