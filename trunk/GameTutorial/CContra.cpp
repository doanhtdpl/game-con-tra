#include "CContra.h"
#include "CInput.h"
#include "CCamera.h"
#include "CCollision.h"
#include "CHidenObject.h"
#include "CSoldier.h"
#include "CPoolingObject.h"
#include <cmath>

CContra::CContra()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 0;
	this->m_idType = 10; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 72.0f;//56.0f; //78
	this->m_height = 92.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(200.0f, 500.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -800.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 170.0f;
	this->m_vyDefault = 380.0f;
	this->m_vx = 0;//this->m_vxDefault;
	this->m_vy = -this->m_vyDefault;
	this->m_left = false;
	//Trang thai ban dau la dang dung yen
	this->m_stateCurrent = ON_GROUND::IS_FALL;
	//Tren mat dat
	this->m_isUnderWater = false;
	this->m_isShoot = true;
	this->m_isShooting = false;
	this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.3f;
	this->m_increase = 1;
	this->m_totalFrame = 50;
	this->m_column = 6;
	//
	this->m_currentFall = 0;
	this->m_currentJump = 0;
	//
	this->m_waitForShoot = 0.4f;
	this->m_waitChangeSprite = 0.0f;

	//Test va cham mat nuoc
	//this->m_pos = D3DXVECTOR2(200, 285);
	//this->m_isUnderWater = true;
	//this->m_startFrame = UNDER_WATER::IS_STANDING_UNDER_WATER;
	
	this->m_typeBullet = BULLET_TYPE::BULLET_N;
	this->m_allowShoot = true;
}

CContra::CContra(const std::vector<int>& info) : CDynamicObject(info)
{
	CContra();
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
			this->m_vy += this->m_a * deltaTime;
			this->m_pos.y += this->m_vy * deltaTime;
		}
		else
		{
			////Neu nhay den do cao cuc dai, gia toc doi chieu
			this->m_elapseTimeChangeFrame = 0.14f;
			//if(this->m_currentJump == 0)
			//	this->m_currentJump = m_pos.y;
			this->m_vy += this->m_a * deltaTime;
			this->m_pos.y += this->m_vy * deltaTime;
		}
	}
	else
	{
		//this->m_vy = -this->m_vyDefault;
		//this->m_vy += this->m_a * deltaTime;
		//this->m_pos.y += this->m_vy * deltaTime;
	}
	if(this->m_stateCurrent == ON_GROUND::IS_STANDING)
	{
		this->m_vx = 0;
	}
	if(this->m_isMoveLeft)
	{
		if (this->m_vx < 0)
		{	
			this->m_pos.x += int(this->m_vx * deltaTime);
		}
	}else if(this->m_isMoveRight)
	{
		if (this->m_vx > 0)
		{
			this->m_pos.x += int(this->m_vx * deltaTime);
		}
	}
	if(this->m_pos.x > 250)
	{
		CCamera::GetInstance()->Update(this->m_pos.x - 250, 0);
	}
#pragma endregion
}

void CContra::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_SPRITE_KHI_BAN
	if(this->m_isShooting) //dang ban
	{
		this->m_waitChangeSprite += deltaTime;
		if(this->m_waitChangeSprite > 0.3)
		{
			this->m_isShooting = false;
			this->m_waitChangeSprite = 0.0f;
		}
	}
#pragma endregion

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
				if(this->m_isShooting)
				{
					this->m_startFrame = 52;
					this->m_endFrame = 53;
				}
				else
				{
					this->m_startFrame = 52;
					this->m_endFrame = 52;
				}
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
				if(this->m_isShooting)
				{
					//this->m_currentFrame = 31;
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
				if(this->m_isShooting)
				{
					//this->m_currentFrame = 3;
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
				this->m_startFrame = 49;
				this->m_endFrame = 50;
				break;
			}
		case UNDER_WATER::IS_LYING_UNDER_WATER:
			{
				this->m_startFrame = 48;
				this->m_endFrame = 48;
				break;
			}
		case UNDER_WATER::IS_STANDING_UNDER_WATER:
			{
				if(this->m_isShooting)
				{
					this->m_stateCurrent =  UNDER_WATER::IS_SHOOTING_UNDER_WATER_NORMAL;
					/*this->m_startFrame = 42;
					this->m_endFrame = 45;
					this->m_increase = 3;*/
				}
				else
				{
					this->m_startFrame = 49;
					this->m_endFrame = 50;
				}
				break;
			}
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_NORMAL:
			{
				if(this->m_isShooting)
				{
					this->m_startFrame = 42;
					this->m_endFrame = 45;
					this->m_increase = 3;
				}
				else
				{
					this->m_startFrame = 42;
					this->m_endFrame = 42;
					this->m_increase = 0;
				}
				break;
			}
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_UP:
			{
				if(this->m_isShooting)
				{
					this->m_startFrame = 43;
					this->m_endFrame = 46;
					this->m_increase = 3;
				}
				else
				{
					this->m_startFrame = 43;
					this->m_endFrame = 43;
					this->m_increase = 0;
				}
				break;
			}
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_DIAGONAL_UP:
			{
				if(this->m_isShooting)
				{
					this->m_startFrame = 44;
					this->m_endFrame = 47;
					this->m_increase = 3;
				}
				else
				{
					this->m_startFrame = 44;
					this->m_endFrame = 44;
					this->m_increase = 0;
				}
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
	if(!(m_isUnderWater && this->m_isShooting))
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
			this->m_elapseTimeChangeFrame = 0.14f;
		}
		//Neu dang nam va phim down duoc giu
		//if(!(this->m_stateCurrent == ON_GROUND::IS_LYING && CInput::GetInstance()->IsKeyDown(DIK_DOWN)) && this->m_stateCurrent != ON_GROUND::IS_FALL)
		//{
			if(!this->m_isUnderWater)
			{
				if(this->m_stateCurrent == ON_GROUND::IS_LYING && !CInput::GetInstance()->IsKeyDown(DIK_DOWN))
				{
					this->m_pos.y += 20;
					this->m_elapseTimeChangeFrame = 0.0f;
				}
				this->m_stateCurrent = ON_GROUND::IS_STANDING;
			}
			else
			{
				if(!this->m_isShooting)
					this->m_stateCurrent = UNDER_WATER::IS_STANDING_UNDER_WATER;
			}
		//}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_BAN__
	this->m_waitForShoot += deltaTime;
	if(m_keyDown == DIK_C)
	{
		if(this->m_waitForShoot > 0.4f)
		{
			this->m_isShoot = true;
			this->m_isShooting = true;
			this->m_waitForShoot = 0.0f;
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_NHAY__
	if(m_keyDown == DIK_X)
	{
		//if(this->m_stateCurrent != ON_GROUND::IS_LYING && this->m_stateCurrent != ON_GROUND::IS_FALL)
		if(!this->m_isUnderWater)
		{
			if(!CInput::GetInstance()->IsKeyDown(DIK_DOWN) || this->m_stateCurrent == ON_GROUND::IS_JUMPING)
			{
				this->m_stateCurrent = ON_GROUND::IS_JUMPING;
				//Duoc phep nhay
				if(!this->m_isJumping)
				{
					this->m_isJumping = true;
					this->m_vy = this->m_vyDefault;
				}
			}
			else
			{
				this->m_elapseTimeChangeFrame = 0.0f;
				this->m_stateCurrent = ON_GROUND::IS_FALL;
				//Duoc phep nhay
				if(!this->m_isJumping)
				{
					this->m_pos.y -= 20;
					this->m_isJumping = true;
					this->m_vy = 0;
				}
			}
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_LEN__

	if(CInput::GetInstance()->IsKeyDown(DIK_UP))
	{
		this->m_stateShoot = SHOOT::IS_UP;
		if(this->m_isUnderWater)
		{
			if(this->m_isShoot) //Day vi tri cua box len
			{
				this->m_stateCurrent = UNDER_WATER::IS_SHOOTING_UNDER_WATER_UP;
			}
		}
		else
		{
			if(this->m_keyDown == DIK_X || this->m_isJumping)
			{
				//Chuyen sang trang thai nhay
				if(this->m_stateCurrent != ON_GROUND::IS_FALL)
				{
					this->m_stateCurrent = ON_GROUND::IS_JUMPING;
				}
				else
				{
					this->m_stateCurrent = ON_GROUND::IS_FALL;
				}
			}
			else
			{
				this->m_stateCurrent = ON_GROUND::IS_SHOOTING_UP;
			}
		}
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_XUONG__
	if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->m_stateShoot = SHOOT::IS_NORMAL;
		if(this->m_isUnderWater)
		{
			this->m_stateCurrent = UNDER_WATER::IS_LYING_UNDER_WATER;
		}
		else
		{
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
			//this->m_stateCurrent = ON_GROUND::IS_JUMPING;
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
					//Neu trang thai truoc do la nhay pos.y +=22
					if(this->m_stateCurrent == ON_GROUND::IS_LYING && (this->m_keyDown == DIK_LEFT || this->m_keyDown == DIK_RIGHT))
					{
						this->m_elapseTimeChangeFrame = 0.0f;
						this->m_pos.y += 22;
					}
					this->m_stateShoot = SHOOT::IS_DIAGONAL_DOWN;
					this->m_stateCurrent = ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN;
				}
				else if(this->m_keyDown == DIK_X)
				{
					//Nhay
					this->m_stateCurrent = ON_GROUND::IS_JUMPING;
				}else if(this->m_keyDown == DIK_C || this->m_isShooting)
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
				if(this->m_isShooting) //Neu la dang ban
				{
					if(CInput::GetInstance()->IsKeyDown(DIK_UP))
					{
						//Ban cheo len
						this->m_stateShoot = SHOOT::IS_DIAGONAL_UP;
						//this->m_elapseTimeChangeFrame = 0.0f;
						//this->m_pos.y += 26;
						this->m_stateCurrent = UNDER_WATER::IS_SHOOTING_UNDER_WATER_DIAGONAL_UP;
					}
					else if(this->m_keyDown == DIK_C)
					{
						this->m_stateCurrent = UNDER_WATER::IS_SHOOTING_UNDER_WATER_NORMAL;
					}
				}
				else if(CInput::GetInstance()->IsKeyDown(DIK_DOWN))
					{
						//Chuyen sang trang thai lan, khong di chuyen
						this->m_stateCurrent = UNDER_WATER::IS_LYING_UNDER_WATER;
						this->m_vx = 0;
					}
				else
				{
					this->m_stateCurrent = UNDER_WATER::IS_JOGGING_UNDER_WATER;
				}
			}
		}
	}
#pragma endregion

#pragma region NHAN NUT_DAU_DAN
	if (CInput::GetInstance()->IsKeyDown(DIK_N))
	{
		this->m_typeBullet = BULLET_TYPE::BULLET_N;
	}
	else if (CInput::GetInstance()->IsKeyDown(DIK_M))
	{
		this->m_typeBullet = BULLET_TYPE::BULLET_M;
	}
	else if (CInput::GetInstance()->IsKeyDown(DIK_S))
	{
		this->m_typeBullet = BULLET_TYPE::BULLET_S;
	}
	else if (CInput::GetInstance()->IsKeyDown(DIK_F))
	{
		this->m_typeBullet = BULLET_TYPE::BULLET_F;
	}
	else if (CInput::GetInstance()->IsKeyDown(DIK_L))
	{
		this->m_typeBullet = BULLET_TYPE::BULLET_L;
	}
#pragma endregion
}
//Kiem tra co tao ra dan hay ko, sau nay add vao quadtree no se tu dong di chuyen
#pragma region KHOI_TAO_DAU_DAN
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

	//Thiet lap vi tri cua dau dan .../pos = posContra + Offset 
	//Neu con tra o tren bo
#pragma region _BAN DAN TREN BO
		D3DXVECTOR2 offset;
		if(!this->m_isUnderWater)
		{
			switch(this->m_stateCurrent)
			{
			case ON_GROUND::IS_LYING:
				{
					switch (this->m_typeBullet)
					{
					case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 0.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 0.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 50.0f;
								offset.y = 0.0f;
							}
							else{
								offset.x = -50.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 85.0f;
								offset.y = 0.0f;
							}
							else{
								offset.x = -85.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 10.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 10.0f;
							}
							break;
					}
					break;
				}
			case ON_GROUND::IS_FALL: case ON_GROUND::IS_JOGGING : case ON_GROUND::IS_SHOOTING_NORMAL: case ON_GROUND::IS_STANDING:
				{
					switch (this->m_typeBullet)
					{
						case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = 20.0f;
								offset.y = 8.0f;
							}
							else{
								offset.x = -20.0f;
								offset.y = 8.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -0.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 50.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -50.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 85.0f;
								offset.y = 0.0f;
							}
							else{
								offset.x = -85.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 10.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 10.0f;
							}
							break;
					}
					break;
				}
			case ON_GROUND::IS_SHOOTING_UP:
				{
				switch (this->m_typeBullet)
					{
						case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = -3.0f;
								offset.y = 50.0f;
							}
							else{
								offset.x = 3.0f;
								offset.y = 50.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 7.0f;
								offset.y = 40.0f;
							}
							else{
								offset.x = -7.0f;
								offset.y = 40.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 0.0f;
								offset.y = 50.0f;
							}
							else{
								offset.x = 0.0f;
								offset.y = 50.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 5.0f;
								offset.y = 75.0f;
							}
							else{
								offset.x = -7.0f;
								offset.y = 75.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 0.0f;
								offset.y = 40.0f;
							}
							else{
								offset.x = 0.0f;
								offset.y = 40.0f;
							}
							break;
					}
					break;
				}
			case ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN:
				{
					switch (this->m_typeBullet)
					{
						case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 40.0f;
								offset.y = -35.0f;
							}
							else{
								offset.x = -80.0f;
								offset.y = 0.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 65.0f;
								offset.y = -45.0f;
							}
							else{
								offset.x = -65.0f;
								offset.y = -45.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
					}
					break;
				}
			case ON_GROUND::IS_SHOOTING_DIAGONAL_UP:
				{
				switch (this->m_typeBullet)
					{
						case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = 20.0f;
								offset.y = 25.0f;
							}
							else{
								offset.x = -20.0f;
								offset.y = 25.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 25.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 25.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 50.0f;
								offset.y = 30.0f;
							}
							else{
								offset.x = -50.0f;
								offset.y = 20.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 55.0f;
								offset.y = 45.0f;
							}
							else{
								offset.x = -55.0f;
								offset.y = 45.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = 30.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = 30.0f;
							}
							break;
					}
					
					break;
				}
			case ON_GROUND::IS_JUMPING:
				{
				switch (this->m_typeBullet)
					{
						case BULLET_TYPE::BULLET_M:
							if (!this->m_left){
								offset.x = -10.0f;
								offset.y = 10.0f;
							}
							else{
								offset.x = 10.0f;
								offset.y = 10.0f;
							}
							break;
						case BULLET_TYPE::BULLET_N:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_F:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_L:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
						case BULLET_TYPE::BULLET_S:
							if (!this->m_left){
								offset.x = 25.0f;
								offset.y = -15.0f;
							}
							else{
								offset.x = -25.0f;
								offset.y = -15.0f;
							}
							break;
					}
					break;
				}
			}
		}
		#pragma endregion
#pragma region _BAN DAN DUOI NUOC
		//Trung them cho nay
		else
		{
			offset.x = 0;
			offset.y = 0;
		}
#pragma endregion

		CBullet* bullet;
		switch (this->m_typeBullet)
		{
			case BULLET_TYPE::BULLET_M:
				bullet = new CBullet_M(rotation, this->m_pos, offset, this->m_left);
				bullet->m_isContra = true;
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bullet);
				//this->m_listBullet.push_back(bullet);
				break;
			case BULLET_TYPE::BULLET_N:
				if (this->m_isShoot)
				{
					if (m_bulletCount > 2)
					{
						this->m_bulletCount = 0;
						this->m_isShoot = false;
					}
					else{
						bullet = new CBullet_N(rotation, this->m_pos, offset, this->m_left);
						bullet->m_isContra = true;
						CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bullet);
						m_bulletCount++;
					}
				}
				break;
			case BULLET_TYPE::BULLET_F:
				bullet = new CBullet_F(rotation, this->m_pos, offset, this->m_left);
				bullet->m_isContra = true;
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bullet);
				break;
			case BULLET_TYPE::BULLET_L:
				bullet = new CBullet_L(rotation, this->m_pos, offset, this->m_left);
				bullet->m_isContra = true;
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bullet);
				break;
			case BULLET_TYPE::BULLET_S:
				//Them dan S.
				CBullet_S* bulletS = new CBullet_S(rotation, this->m_pos, offset, this->m_left);
				bulletS->m_isContra = true;
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bulletS->m_bullet_1);
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bulletS->m_bullet_2);
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bulletS->m_bullet_3);
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bulletS->m_bullet_4);
				CPoolingObject::GetInstance()->m_listBulletOfObject.push_back(bulletS->m_bullet_5);
				break;
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
		if(pos.x > __SCREEN_WIDTH || pos.x < 0 || pos.y > __SCREEN_HEIGHT || pos.y < 0)
		{
			delete this->m_listBullet.at(i);
			this->m_listBullet.erase(this->m_listBullet.begin() + i);
		}
		
	}

	if (this->m_listBullet.empty())
	{
		this->m_isShoot = true;
	}

}
#pragma endregion
void CContra::Update(float deltaTime)
{
	this->InputUpdate(deltaTime);
	this->SetFrame(deltaTime);
	this->ChangeFrame(deltaTime);
	this->MoveUpdate(deltaTime);
	this->BulletUpdate(deltaTime);
}

void CContra::Update(float deltaTime, std::vector<CGameObject*> listObjectCollision)
{

}

void CContra::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
#pragma region XU_LY_VA_CHAM
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;
	//Kiem tra va cham voi ground
	bool checkColWithGround = false;
	//Kiem tra va cham voi water
	bool checkColWithWater = false;
	for (std::vector<CGameObject*>::iterator it = listObjectCollision->begin(); it != listObjectCollision->end(); it++)
	{
		CGameObject* obj = *it;
		//Lay thoi gian va cham
		//Neu doi tuong la ground va dang va cham
		if(obj->GetIDType() == 15)
		{
			timeCollision = CCollision::GetInstance()->Collision(CContra::GetInstance(), obj, normalX, normalY, moveX, moveY, deltaTime);
			if((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
			{
				if(normalY > 0)
				{

#pragma region VA CHAM MAT DAT

					/*else */if(obj->GetID() == 1 && !checkColWithGround)
					{
						checkColWithGround = true;
						this->m_isUnderWater = false;
						if( timeCollision == 2.0f)
						{
							if(this->m_vy <= 0)
							{
								if(this->m_stateCurrent == ON_GROUND::IS_JUMPING)
								{
									if(this->m_vy < -165)
									{
										this->m_pos.y += 20;
										this->m_elapseTimeChangeFrame = 0.0f;
										this->m_isJumping = false;
										this->m_currentFrame = 0;
										this->m_stateCurrent = ON_GROUND::IS_STANDING;
									}
								}
								else if(this->m_stateCurrent == ON_GROUND::IS_LYING)
								{
									//this->m_pos.y += 20;
									this->m_elapseTimeChangeFrame = 0.0f;
								}
								else
								{
									this->m_isJumping = false;
									this->m_pos.y += moveY;
									this->m_vy = 0;
								}
							}
							if(this->m_stateCurrent == ON_GROUND::IS_FALL)
							{
								this->m_stateCurrent = ON_GROUND::IS_STANDING;
								this->m_isJumping = false;
							}

						}else{
							//if(this->m_vy != 0)
							//{
							if(this->m_stateCurrent == ON_GROUND::IS_JUMPING && this->m_vy < 0)
							{

								this->m_pos.y += 22;
								this->m_elapseTimeChangeFrame = 0.0f;
								this->m_currentFrame = 0;
								if(this->m_keyDown != DIK_DOWN)
									this->m_stateCurrent = ON_GROUND::IS_STANDING;
								else
									this->m_stateCurrent = ON_GROUND::IS_LYING;
								this->m_isJumping = false;
							}
						
							//	this->m_isJumping = false;
							//	this->m_pos.y += (this->m_vy /** timeCollision*/) * deltaTime;
							//	this->m_vy = 0;
							//}
						}
					}
#pragma endregion
#pragma region VA CHAM MAT NUOC
					/*else */if(!checkColWithWater && obj->GetID() == 2 && !checkColWithGround)
					{
						//O duoi nuoc khong the nhay
						checkColWithWater = true;
						this->m_isUnderWater = true;
						this->m_isJumping = false;
						if( timeCollision == 2.0f)
						{
							if(this->m_vy <= 0)
							{
								if(this->m_stateCurrent == UNDER_WATER::IS_LYING_UNDER_WATER)
								{
									//this->m_pos.y += 20;
									this->m_pos.y += moveY;
									this->m_vy = 0;
									//this->m_elapseTimeChangeFrame = 0.0f;
								}
								else
								{
									this->m_pos.y += moveY;
									this->m_vy = 0;
								}
							}
						}
						else
						{
							this->m_pos.y += -1;
						}
					}
#pragma endregion 
#pragma region DANG VA CHAM VOI NUOC VA CHUYEN LEN MAT DAT
					if((checkColWithWater || this->m_stateCurrent > 19) && checkColWithGround) //Neu dang va cham voi mat nuoc
					{
						this->m_isUnderWater = false;
						this->m_pos.y += 10;
						if(this->m_left)
						{
							this->m_pos.x -= 10;
						}
						else
						{
							this->m_pos.x += 10;
						}
						this->m_stateCurrent = ON_GROUND::IS_JOGGING;
					}
#pragma endregion
				}
#pragma region VA CHAM VOI DOI TUONG SINH ENEMY
				if(obj->GetID() == 3)
				{
					
				}
#pragma endregion

			}
		}
	}
	if(!checkColWithGround && !checkColWithWater)
	{
		if(this->m_isUnderWater)
		{
			//this->m_isUnderWater = false;
			this->m_pos.y -= 10;
			//this->m_stateCurrent = ON_GROUND::IS_FALL;
			//this->m_isJumping = true;
		}
		else
		{
			if(this->m_stateCurrent != ON_GROUND::IS_JUMPING)
			{
				if(this->m_stateCurrent == ON_GROUND::IS_LYING)
				{
					this->m_pos.y -= 15;
					this->m_currentFrame = 52;
					//this->m_stateCurrent = ON_GROUND::IS_STANDING;
					this->m_isJumping = false;
				}
				else
				{
					this->m_stateCurrent = ON_GROUND::IS_FALL;
					this->m_isJumping = true;
				}										
			}
		}
	}
}
	
RECT* CContra::GetRectRS()
{
	return this->UpdateRectResource(m_height, m_width);
}

RECT* CContra::GetBound()
{
	return nullptr;
}

Box CContra::GetBox()
{
	//return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
	if(!this->m_isUnderWater)
	{
		switch (this->m_stateCurrent)
		{
		case ON_GROUND::IS_FALL:
		case ON_GROUND::IS_JOGGING:
		case ON_GROUND::IS_SHOOTING_DIAGONAL_DOWN:
		case ON_GROUND::IS_SHOOTING_NORMAL:
		case ON_GROUND::IS_SHOOTING_DIAGONAL_UP:
		case ON_GROUND::IS_STANDING:
		case ON_GROUND::IS_SHOOTING_UP:
			{
				return Box(this->m_pos.x, this->m_pos.y - 10, this->m_width - 45, this->m_height - 20, this->m_vx, this->m_vy);
			}
		case ON_GROUND::IS_JUMPING:
			{
				return Box(this->m_pos.x, this->m_pos.y, this->m_width - 40, this->m_height - 55, this->m_vx, this->m_vy);
			}
		case ON_GROUND::IS_LYING:
			{
				return Box(this->m_pos.x, this->m_pos.y - 5, this->m_width, this->m_height - 65, this->m_vx, this->m_vy);
			}
		
		default:
			{
				break;
			}
		}
	}
	else
	{
		//return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
		switch (this->m_stateCurrent)
		{
		case UNDER_WATER::IS_JOGGING_UNDER_WATER:
		case UNDER_WATER::IS_LYING_UNDER_WATER:
		case UNDER_WATER::IS_STANDING_UNDER_WATER:
			{
				return Box(this->m_pos.x, this->m_pos.y - 5, this->m_width - 40, this->m_height - 60, this->m_vx, this->m_vy);
			}
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_DIAGONAL_UP:
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_UP:
			{
				return Box(this->m_pos.x, this->m_pos.y - 17, this->m_width - 40, this->m_height - 64, this->m_vx, this->m_vy);
			}
		case UNDER_WATER::IS_SHOOTING_UNDER_WATER_NORMAL:
			{
				return Box(this->m_pos.x, this->m_pos.y - 17, this->m_width - 40, this->m_height - 62, this->m_vx, this->m_vy);
			}
		default:
			return Box(this->m_pos.x, this->m_pos.y, this->m_width - 40, this->m_height - 50, this->m_vx, this->m_vy);
			break;
		}
	}
}