#include "CContra.h"
#include "CInput.h"
#include "CCamera.h"
#include <cmath>

CContra::CContra()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 72.0f;//56.0f; //78
	this->m_height = 92.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(50.0f, 285.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 100.0f;
	this->m_vyDefault = 400.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_left = false;
	//Trang thai ban dau la dang dung yen
	this->m_stateCurrent = ON_GROUND::IS_STANDING;
	//Tren mat dat
	this->m_isUnderWater = false;
	this->m_isShoot = false;
	this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.23f;
	this->m_increase = 1;
	this->m_totalFrame = 50;
	this->m_column = 6;
	//
	this->m_currentFall = 0;
	this->m_currentJump = 0;
	
}

CContra::~CContra()
{

}

void CContra::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	//Kiem tra doi tuong co nhay duoc hay ko
	if(this->m_canJump && this->m_isJumping)
	{
		if(this->m_stateCurrent == ON_GROUND::IS_FALL)
		{
			this->m_pos.y -= this->m_vy * deltaTime;
			this->m_currentFall -= this->m_vy * deltaTime;
			if(this->m_currentFall <= -60)
			{ 
				this->m_currentFall = 0.0f;
				this->m_elapseTimeChangeFrame = 0.00f;
				this->m_stateCurrent = ON_GROUND::IS_STANDING;
				this->m_vy = this->m_vyDefault;
				//this->m_elapseTimeChangeFrame = 0.23f;
				//this->m_pos.y = 220;
				this->m_isJumping = false;
			}
		}
		else
		{
			//Neu nhay den do cao cuc dai, gia toc doi chieu
			this->m_elapseTimeChangeFrame = 0.10f;
			if(this->m_vy <= 0)
			{
	//			this->m_a = 1500.0f;
			}
			if(this->m_currentJump == 0)
				this->m_currentJump = m_pos.y;
			this->m_vy += this->m_a * deltaTime;
			this->m_pos.y += this->m_vy * deltaTime;
			//Neu co vao cham thi cai dat lai posY cua doi tuong
			if(this->m_pos.y <= this->m_currentJump)
			{ 
				this->m_pos.y = this->m_currentJump;
				this->m_currentJump = 0;
				this->m_elapseTimeChangeFrame = 0.00f;
				//this->m_stateCurrent = ON_GROUND::IS_STANDING;
				this->m_vy = this->m_vyDefault;
				//this->m_elapseTimeChangeFrame = 0.23f;
				this->m_isJumping = false;
			}
		}
	}
	if(this->m_isMoveLeft)
	{
		if (this->m_vx < 0)
		{	
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}else if(this->m_isMoveRight)
	{
		if (this->m_vx > 0)
		{
			this->m_pos.x += this->m_vx * deltaTime;
		}
	}
	if(this->m_pos.x > 400)
		{
			if(this->m_vx * deltaTime - int(this->m_vx * deltaTime) > 0.6)
				CCamera::GetInstance()->Update(int(this->m_vx * deltaTime) + 1, 0);
			else
				CCamera::GetInstance()->Update(int(this->m_vx * deltaTime), 0);
		}
#pragma endregion
}

void CContra::SetFrame()
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	//Neu dan duoc ban ra thi tang toc do chuyen frame	
	if(!this->m_isUnderWater)
	{
		switch (this->m_stateCurrent)
		{
		case ON_GROUND::IS_FALL:
			{
				this->m_startFrame = 19;
				this->m_endFrame = 19;
				break;
			}
		case ON_GROUND::IS_JOGGING:
			{
				this->m_startFrame = 18;
				this->m_endFrame = 23;
				break;
			}
		case ON_GROUND::IS_JUMPING:
			{
				this->m_startFrame = 32;
				this->m_endFrame = 35;
				break;
			}
		case ON_GROUND::IS_LYING:
			{
				this->m_startFrame = 29;
				this->m_endFrame = 29;
				break;
			}
		case ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN:
			{
				this->m_startFrame = 12;
				this->m_endFrame = 17;
				break;
			}
		case ON_GROUND::IS_SHOOTING_DIAGONAL_UP:
			{
				this->m_startFrame = 6;
				this->m_endFrame = 11;
				break;
			}
		case ON_GROUND::IS_SHOOTING_NORMAL:
			{
				if(this->m_currentFrame > 17 && this->m_currentFrame < 24)
				{
					 this->m_currentFrame -= 18;
				}
				this->m_startFrame = 0;
				this->m_endFrame = 5;
				break;
			}
		case ON_GROUND::IS_SHOOTING_UP:
			{
				//Kiem tra co ban hay la khong
				if(this->m_isShoot)
				{
					this->m_currentFrame = 31;
					this->m_startFrame = 30;
					this->m_endFrame = 31;
				}
				else
				{
					this->m_startFrame = 30;
					this->m_endFrame = 30;
				}
				break;
			}
		case ON_GROUND::IS_STANDING:
			{
				if(this->m_isShoot)
				{
					this->m_currentFrame = 3;
					this->m_startFrame = 0;
					this->m_endFrame = 3;
					this->m_increase = 3;
				}
				else
				{
					this->m_startFrame = 0;
					this->m_endFrame = 0;
				}
				break;
			}
		default:
			{
				break;
			}
		}
	}
	else
	{
		switch (this->m_stateCurrent)
		{
		case UNDER_WATER::IS_JOGGING_UNDER_WATER:
			{
				break;
			}
		case UNDER_WATER::IS_LYING_UNDER_WATER:
			{
				break;
			}
		case UNDER_WATER::IS_STANDING_UNDER_WATER:
			{
				break;
			}
		default:
			break;
		}
	}
#pragma endregion
}

void CContra::InputUpdate(float deltaTime)
{
#pragma region __KHONG_CO_SU_KIEN_PHIM__
	////Khong duoc phep ban
	this->m_isShoot = false;
	this->m_keyDown = CInput::GetInstance()->GetKeyDown();
	this->m_keyUp = CInput::GetInstance()->GetKeyUp();
	this->m_increase = 1;
	if(!this->m_isJumping)
	{
		this->m_vx = 0;
		this->m_isMoveLeft = false;
		this->m_isMoveRight = false;
		this->m_stateShoot = SHOOT::IS_NORMAL;
		if(this->m_stateCurrent == ON_GROUND::IS_JUMPING)
		{
			this->m_elapseTimeChangeFrame = 0.00f;
		}
		else
		{
			this->m_elapseTimeChangeFrame = 0.23f;
		}
		//Neu dang nam va phim down duoc giu
		if(!(this->m_stateCurrent == ON_GROUND::IS_LYING && CInput::GetInstance()->IsKeyDown(DIK_DOWN)) && this->m_stateCurrent != ON_GROUND::IS_FALL)
		{
			if(!this->m_isUnderWater)
			{
				this->m_stateCurrent = ON_GROUND::IS_STANDING;
			}
			else
			{
				this->m_stateCurrent = UNDER_WATER::IS_STANDING_UNDER_WATER;
			}
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_BAN__
	if(m_keyDown == DIK_C)
	{
		this->m_isShoot = true;
	}
#pragma endregion

#pragma region __XU_LY_PHIM_NHAY__
	if(m_keyDown == DIK_X)
	{
		//if(this->m_stateCurrent != ON_GROUND::IS_LYING && this->m_stateCurrent != ON_GROUND::IS_FALL)
		if(!CInput::GetInstance()->IsKeyDown(DIK_DOWN) || this->m_stateCurrent == ON_GROUND::IS_JUMPING)
		{
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
		}
		else
		{
			this->m_stateCurrent = ON_GROUND::IS_FALL;
		}
		//Duoc phep nhay
		if(!this->m_isUnderWater && !this->m_isJumping)
		{
			this->m_isJumping = true;
			//this->m_vy = this->m_vyDefault;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_LEN__

	if(CInput::GetInstance()->IsKeyDown(DIK_UP))
	{
		this->m_stateShoot = SHOOT::IS_UP;
		if(this->m_keyDown == DIK_X || this->m_isJumping)
		{
			//Chuyen sang trang thai nhay
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
		}
		else
		{
			this->m_stateCurrent = ON_GROUND::IS_SHOOTING_UP;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_XUONG__
	if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_stateShoot = SHOOT::IS_NORMAL;
		if(this->m_stateCurrent == ON_GROUND::IS_FALL)
		{
			//Chuyen sang trang thai roi
			this->m_stateCurrent = ON_GROUND::IS_FALL;
		}else if(this->m_isJumping)
		{
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
			this->m_stateShoot = SHOOT::IS_DOWN;
		}else
		{
			this->m_stateCurrent = ON_GROUND::IS_LYING;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_QUA_TRAI_HOAC_PHAI__
	if((CInput::GetInstance()->IsKeyDown(DIK_LEFT) || CInput::GetInstance()->IsKeyDown(DIK_RIGHT)))
	{
		if(CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			this->m_left = false;
			this->m_isMoveRight = true;
			this->m_isMoveLeft = false;
			this->m_vx = this->m_vxDefault;
		}
		else
		{
			this->m_left = true;
			this->m_isMoveRight = false;
			this->m_isMoveLeft = true;
			this->m_vx = -this->m_vxDefault;
		}
		this->m_stateShoot = SHOOT::IS_NORMAL;
		if(this->m_isJumping)
		{
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
			if(CInput::GetInstance()->IsKeyDown(DIK_UP))
			{
				this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
			}
			else if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
			{
				this->m_stateShoot = SHOOT::IS_DIAGONAL_DOWN;
			}
		}else{
			//Kiem tra contra co nam duoi nuoc hay ko
			if(!this->m_isUnderWater)
			{
				//Kiem tra neu phim di len duoc nhan
				if(CInput::GetInstance()->IsKeyDown(DIK_UP))
				{
					//Ban cheo len
					this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
					this->m_stateCurrent = ON_GROUND::IS_SHOOTING_DIAGONAL_UP;
				}
				else if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
				{
					//Ban cheo xuong
					this->m_stateShoot = SHOOT::IS_DIAGONAL_DOWN;
					this->m_stateCurrent = ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN;
				}
				else if(this->m_keyDown == DIK_X)
				{
					//Nhay
					this->m_stateCurrent = ON_GROUND::IS_JUMPING;
				}else if(CInput::GetInstance()->IsKeyDown(DIK_C) || this->m_isShoot)
				{
					//Ban binh thuong
					this->m_stateCurrent = ON_GROUND::IS_SHOOTING_NORMAL;
				}else
				{
					//Chuyen sprite
					this->m_stateCurrent = ON_GROUND::IS_JOGGING;
				}
			}
			else //Dang nam duoi nuoc
			{
				if(CInput::GetInstance()->IsKeyDown(DIK_UP))
				{
					//Ban cheo len
					this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
				}else if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
				{
					//Chuyen sang trang thai lan, khong di chuyen
					this->m_stateCurrent = UNDER_WATER::IS_LYING_UNDER_WATER;
					this->m_vx = 0;
				}else
				{
					this->m_stateCurrent = UNDER_WATER::IS_JOGGING_UNDER_WATER;
				}
			}
		}
	}
#pragma endregion
}

void CContra::ChangeFrame(float deltaTime)
{
	this->m_currentTime += deltaTime;
	if(this->m_currentTime > this->m_elapseTimeChangeFrame)
	{
		this->m_currentFrame += this->m_increase;
		if(this->m_currentFrame > this->m_endFrame || this->m_currentFrame < this->m_startFrame)
		{
			this->m_currentFrame = this->m_startFrame;
		}
		this->m_currentTime -= this->m_elapseTimeChangeFrame;
	}
}

//Kiem tra co tao ra dan hay ko, sau nay add vao quadtree no se tu dong di chuyen
void CContra::BulletUpdate(float deltaTime)
{
	if(this->m_isShoot)
	{
		//Cap nhat goc quay
		float rotation = 0;
		switch (this->m_stateShoot)
		{
		case SHOOT::IS_NORMAL:
			{
				rotation = 0; //Goc ban bang 0
				break;
			}
		case SHOOT::IS_UP:
			{
				rotation = PI/2; //Goc ban bang 90
				break;
			}
		case SHOOT::IS_DOWN:
			{
				rotation = -PI/2;
				break;
			}
		case SHOOT::IS_DIAGONAL_UP:
			{ 
				rotation = PI/4; //Goc ban bang 45
				break;
			}
		case SHOOT::IS_DIAGONAL_DOWN:
			{
				//this->m_a = -700;
				//this->m_vy = -400.0f;
				rotation = -PI/4;// //Goc ban bang -45
				break;
			}
		default:
			{
				rotation = 0;
				break;
			}
		}

		// Them dan S.
		/*CBullet_S* bullet = new CBullet_S(rotation);
		this->m_listBullet.push_back(bullet->m_bullet_1);
		this->m_listBullet.push_back(bullet->m_bullet_2);
		this->m_listBullet.push_back(bullet->m_bullet_3);
		this->m_listBullet.push_back(bullet->m_bullet_4);
		this->m_listBullet.push_back(bullet->m_bullet_5);*/

		CBullet_F* bulletF = new CBullet_F(rotation);
		this->m_listBullet.push_back(bulletF);

		this->m_isShoot = false;
	}
	//Update trang thai dan
	D3DXVECTOR3 pos;
	for (int i = 0; i < this->m_listBullet.size(); i++)
	{
		this->m_listBullet.at(i)->Update(deltaTime);
		pos.x = this->m_listBullet.at(i)->GetPos().x;
		pos.y = this->m_listBullet.at(i)->GetPos().y;
		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		if(pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
		{
			delete this->m_listBullet.at(i);
			this->m_listBullet.erase(this->m_listBullet.begin() + i);
		}
	}

}

void CContra::Update(float deltaTime)
{
	this->InputUpdate(deltaTime);
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->MoveUpdate(deltaTime);
	this->BulletUpdate(deltaTime);
}

void CContra::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

RECT* CContra::GetRectRS()
{
	return this->UpdateRectResource(m_height, m_width);
}

RECT CContra::GetRect()
{
	return RECT();
}