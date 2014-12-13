#include "CWallTurret.h"
#include "CContra.h"
#include <math.h>
#include "CCamera.h"

CWallTurret::CWallTurret(void)
{
	this->Init();
}
	
CWallTurret::CWallTurret(const std::vector<int>& info)
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

void CWallTurret::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 11; 
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 64.0f;//56.0f; //78
	this->m_height = 64.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(1100.0f, 200.0f);
	this->m_left = false;

	//Khoi tao cac thong so chuyen doi sprite
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.20f;
	this->m_increase = 1;
	this->m_totalFrame = 42;
	this->m_column = 6;
	//
	this->m_isShoot = true;
	this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL;
	//Test
	this->m_bulletCount = 0;
	this->m_timeDelay = 0.25f;

	this->m_IsCre = false;
	this->m_direction = false;
	this->m_totalCurr = 0;
	this->m_oldangle = -1;

	this->m_allowShoot = true;
}

void CWallTurret::Update(float deltaTime)
{
	this->SetFrame();
	this->ChangeFrame(deltaTime);
	this->BulletUpdate(deltaTime);
}

void CWallTurret::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CWallTurret::BulletUpdate(float deltaTime)
{
#pragma region THIET LAP GOC BAN
	D3DXVECTOR2 posContra = CContra::GetInstance()->GetPos();
	float spaceX = posContra.x - this->m_pos.x; //Khoang cach Contra va Object theo X la canh ke^` cua goc ban
	float spaceY = posContra.y - this->m_pos.y; //Khoang cach Contra va Object theo Y la canh do^i cua goc ban
	double shootAngleNormal = PI / 6; //Goc Ban
	double angle = 0.0f; //Goc @
	int temp = 0;
	if (spaceX != 0)
	{
		angle = atan(spaceY / abs(spaceX));
		angle = (angle / shootAngleNormal) * shootAngleNormal;
		if (spaceX < 0) //Chuyen doi goc
		{
			if (spaceY > 0)
			{
				angle = PI - angle;
			}
			else
			{
				angle = -PI + abs(angle);
			}
		}
		//Gan gia tri
		//(angle * m_oldangle >= 0) ? abs(abs(angle) - abs(m_oldangle)) : 
		this->m_space = abs(angle - m_oldangle);
		//Neu khoang cach > 2PI, k cach min = 2PI - space
		this->m_space = (this->m_space > PI) ? 2*PI - this->m_space : this->m_space;
		if (m_oldangle == -1 || this->m_space == 0)//|| this->m_space / shootAngleNormal == 0) //Gan gia tri cho m_oldangle
		{
			this->m_oldangle = angle;
		}
		else
		{
			if (angle  * m_oldangle > 0)
			{
				if (angle < m_oldangle)
				{
					temp = -1;
					//m_oldangle -= shootAngleNormal;
				}
				else
				{
					temp = 1;
					//m_oldangle += shootAngleNormal;
				}
			}
			else
			{
				if (spaceX > 0)
				{
					if (m_oldangle > 0 && angle < 0)
					{
						temp = -1;
						//m_oldangle -= shootAngleNormal;
					}
					else
					{
						temp = 1;
						//m_oldangle += shootAngleNormal;
					}
				}
				else
				{
					if (m_oldangle > 0 && angle < 0)
					{
						temp = 1;
						//m_oldangle -= shootAngleNormal;
					}
					else
					{
						temp = -1;
						//m_oldangle += shootAngleNormal;
					}
				}

			}
			if (temp != 0)
			{
				this->m_timeDelay += deltaTime;
				if(this->m_timeDelay >	1.2f)
				{
					if (this->m_totalCurr < this->m_space)
					{
						this->m_totalCurr += shootAngleNormal;
						m_oldangle += temp*shootAngleNormal;
				
					}
					else
					{
						this->m_oldangle = angle;
						this->m_totalCurr = 0;
					}
					this->m_timeDelay = 0;
				}
			}
		}
	}
	else
	{
		if (spaceY < 0)
		{
			angle = PI / 2;
		}
		else
		{
			angle = -PI / 2;
		}
	}
#pragma endregion

#pragma region THIET LAP TRANG THAI BAN
	if(this->m_isShoot)
	{		
		double temp = m_oldangle;
		if (m_oldangle <= PI / 2 && m_oldangle >= -PI / 2){
			this->m_direction = true;
		}
		else{
			this->m_direction = false;
		}

		temp = (temp < 0) ? 2 * PI + temp : temp;
		int tempdiv = int(temp / shootAngleNormal);
		tempdiv = ((temp - tempdiv*shootAngleNormal) > shootAngleNormal / 2) ? ++tempdiv : tempdiv;
		//if (tempdiv != 0 && tempdiv != 3 && tempdiv != 6 && tempdiv != 9) //
		//	temp = (int(temp / shootAngleNormal) + 1) * shootAngleNormal;
		//else
		temp = (int(tempdiv)) * shootAngleNormal;

		switch(tempdiv)
		{
		case 0: case 6:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL;
				break;
			}
		case 1: case 5:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X;
				break;
			}
		case 2: case 4:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X;
				break;
			}
		case 3:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP;
				break;
			}
		case 7: case 11: 
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X;
				break;
			}
		case 8: case 10:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X;
				break;
			}
		case 9:
			{
				this->m_stateCurrent = WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN;
				break;
			}
		}
#pragma endregion

#pragma region KHOI TAO MOT VIEN DAN THEO HUONG
	D3DXVECTOR2 offset;
	switch(this->m_stateCurrent)
	{
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL:
		{
			if (this->m_direction){
				offset.x = this->m_width / 2;
				offset.y = 5.0f;
			}
			else{
				offset.x = this->m_width / 2;
				offset.y = 5.0f;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP:
		{
			if (this->m_direction){
				offset.x = 0;
				offset.y = this->m_height / 2;
			}
			else{
				offset.x = 0;
				offset.y = this->m_height / 2;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X:
		{
			if (this->m_direction){
				offset.y = 15.0f;
				offset.x = this->m_width / 2;
			}
			else{
				offset.x = 0;
				offset.y = 0.0f;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X:
		{
			if (this->m_direction){
				offset.y = 30.0f;
				offset.x = 0;
			}
			else{
				offset.x = 0;
				offset.y = 30.0f;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN:
		{
			if (this->m_direction){
				offset.x = -10.0f;
				offset.y = -this->m_height / 2;
			}
			else{
				offset.x = this->m_width / 2;
				offset.y = 10.0f;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X:
		{
			if (this->m_direction){
				offset.y = -10.0f;
				offset.x = this->m_width / 2;
			}
			else{
				offset.x = this->m_width / 2;
				offset.y = 10.0f;
			}			
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X:
		{
			if (this->m_direction){
				offset.y = -this->m_height / 2;
				offset.x = this->m_width / 2 - 15.0f;
			}
			else{
				offset.x = 10.0f;
				offset.y = 10.0f;
			}			
			break;
		}
	default:
		{
			break;
		}
	}
#pragma endregion

#pragma region THIET LAP TOC DO DAN
		if(m_oldangle == angle)
		{
			//Goc cua vien dan da duoc chinh san
			//Chuyen ve toa do goc phan tu 1 - 2
			temp = this->m_direction ? temp : PI - temp;
			CBullet_N* bullet = new CBullet_N(temp, this->m_pos, offset, !this->m_direction);
			m_listBullet.push_back(bullet);
			this->m_timeDelay = 0;
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
	if(this->m_listBullet.empty())
	{
		this->m_isShoot = true;
	}else
	{
		this->m_isShoot = false;
	}
#pragma endregion

}

void CWallTurret::SetFrame()
{
	//Chuyen doi frame
	int currentFrame = this->m_currentFrame;
	switch (this->m_stateCurrent)
	{
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_NORMAL:
		{
			if (this->m_direction){
				this->m_startFrame = 12;
				this->m_endFrame = 14;
			}
			else{
				this->m_startFrame = 30;
				this->m_endFrame = 32;
			}
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_UP:
	{
			this->m_startFrame = 3;
			this->m_endFrame = 5;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_X:
		{
			if (this->m_direction){
				this->m_startFrame = 9;
				this->m_endFrame = 11;
			}
			else{
				this->m_startFrame = 33;
				this->m_endFrame = 35;
			}
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_UP_2X:
		{
			if (this->m_direction){
				this->m_startFrame = 6;
				this->m_endFrame = 8;
			}
			else{
				this->m_startFrame = 0;
				this->m_endFrame = 2;
			}
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DOWN:
		{
			this->m_startFrame = 21;
			this->m_endFrame = 23;
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_X:
		{
			if (this->m_direction){
				this->m_startFrame = 15;
				this->m_endFrame = 17;
			}
			else{
				this->m_startFrame = 27;
				this->m_endFrame = 29;
			}
			break;
		}
	case WALLTURRET_SHOOT_STATE::W_IS_SHOOTING_DIAGONAL_DOWN_2X:
		{
			if (this->m_direction){
				this->m_startFrame = 18;
				this->m_endFrame = 20;
			}
			else{
				this->m_startFrame = 24;
				this->m_endFrame = 26;
			}
			break;
		}
	default:
		{
			break;
		}
	}
}

RECT* CWallTurret::GetBound()
{
	return nullptr;
}

RECT* CWallTurret::GetRectRS()
{
	return this->UpdateRectResource(this->m_height, this->m_width);
}

Box CWallTurret::GetBox()
{
	return Box();
}

CWallTurret::~CWallTurret()
{

}