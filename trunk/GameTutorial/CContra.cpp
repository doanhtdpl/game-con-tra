#include "CContra.h"
#include "CInput.h"
#include "CCamera.h"

CContra::CContra()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 72.0f;//56.0f; //78
	this->m_height = 92.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(50.0f, 280.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	this->m_currentJump = 0.0f;
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
			if(this->m_pos.y <= 200)
			{ 
				this->m_elapseTimeChangeFrame = 0.00f;
				//this->m_stateCurrent = ON_GROUND::IS_STANDING;
				this->m_vy = this->m_vyDefault;
				//this->m_elapseTimeChangeFrame = 0.23f;
				this->m_pos.y = 200;
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
			this->m_vy += this->m_a * deltaTime;
			this->m_pos.y += this->m_vy * deltaTime;
			this->m_currentJump += this->m_vy * deltaTime;
			//Neu co vao cham thi cai dat lai posY cua doi tuong
			if(this->m_pos.y <= 290)
			{ 
				this->m_elapseTimeChangeFrame = 0.00f;
				//this->m_stateCurrent = ON_GROUND::IS_STANDING;
				this->m_vy = this->m_vyDefault;
				//this->m_elapseTimeChangeFrame = 0.23f;
				this->m_pos.y = 280;
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
				this->m_startFrame = 0;
				this->m_endFrame = 5;
				break;
			}
		case ON_GROUND::IS_SHOOTING_UP:
			{
				this->m_startFrame = 30;
				this->m_endFrame = 31;
				break;
			}
		case ON_GROUND::IS_STANDING:
			{
				this->m_startFrame = 0;
				this->m_endFrame = 0;
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
	if(!this->m_isJumping)
	{
		this->m_vx = 0;
		this->m_isShoot = false;
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
		if(!this->m_isUnderWater)
		{
			this->m_stateCurrent = ON_GROUND::IS_STANDING;
		}
		else
		{
			this->m_stateCurrent = UNDER_WATER::IS_STANDING_UNDER_WATER;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_BAN__
	if(CInput::GetInstance()->IsKeyDown(DIK_C))
	{
		this->m_isShoot = true;
	}
#pragma endregion

#pragma region __XU_LY_PHIM_NHAY__
	if(CInput::GetInstance()->IsKeyDown(DIK_X))
	{
		if(this->m_stateCurrent != ON_GROUND::IS_LYING)
		{
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
			if(!this->m_isUnderWater && !this->m_isJumping)
			{
				this->m_isJumping = true;
				//this->m_vy = this->m_vyDefault;
			}
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_LEN__

	if(CInput::GetInstance()->IsKeyDown(DIK_UP))
	{
		this->m_stateShoot = SHOOT::IS_UP;
		if(CInput::GetInstance()->IsKeyDown(DIK_X) || this->m_isJumping)
		{
			//Chuyen sang trang thai nhay
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
		}else
		{
			this->m_stateCurrent = ON_GROUND::IS_SHOOTING_UP;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_XUONG__
	if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_stateShoot = SHOOT::IS_NORMAL;
		if(this->m_stateCurrent == ON_GROUND::IS_LYING && this->m_isJumping)
		{
			//Chuyen sang trang thai roi
			this->m_stateCurrent = ON_GROUND::IS_FALL;
		}else if(CInput::GetInstance()->IsKeyDown(DIK_DOWN) && this->m_isJumping)
		{
			this->m_stateCurrent = ON_GROUND::IS_JUMPING;
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
		}else
		{
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
				else if(CInput::GetInstance()->IsKeyDown(DIK_X))
				{
					//Nhay
					this->m_stateCurrent = ON_GROUND::IS_JUMPING;
				}else if(CInput::GetInstance()->IsKeyDown(DIK_C))
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

void CContra::Update(float deltaTime)
{
	this->InputUpdate(deltaTime);
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->MoveUpdate(deltaTime);
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