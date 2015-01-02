#include "CSubArm.h"

CSubArm::CSubArm()
{
	this->Init();
}


CSubArm::~CSubArm()
{
	
}

void CSubArm::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_idType = 17; 
	this->m_idImage = 0;
	this->m_isALive = false;
	this->m_isAnimatedSprite = true;
	this->m_width = 32.0f;//56.0f; //78
	this->m_height = 32.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(200.0f, 200.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = -700.0f;
	this->m_canJump = true;
	this->m_jumpMax = 40.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 50.0f;
	this->m_vyDefault = 50.0f;
	this->m_vx = 0;//this->m_vxDefault;
	this->m_vy = -this->m_vyDefault;
	this->m_left = false;
	//
	//this->m_armType = SUB_ARM_TYPE::SUB_ARM_COMPONENT;
	this->m_angleDefault = 0.08f;
	this->m_curveCurr = 0.0f;
	this->m_rotation = PI/4;
	this->m_angle = 0;
	this->m_radian = 0.0f;
	this->m_posCenter = D3DXVECTOR2(0.0f, 0.0f);
	switch (this->m_armType)
	{
	case SUB_ARM_TYPE::SUB_ARM_FIRST:
		{
			this->m_id = 8;
			break;
		}
	case SUB_ARM_TYPE::SUB_ARM_COMPONENT:
		{
			this->m_id = 7;
			break;
		}
	default:
		this->m_id = 8;
		break;
	}
	this->m_waitForHandAppear = 0.0f;
}

void CSubArm::Update(float deltaTime)
{
	this->m_waitForHandAppear += deltaTime;
	if(this->m_waitForHandAppear > this->WaitForAppear)
	{
		this->m_isALive = true;
	}
	//this->MoveUpdate(deltaTime);
}

void CSubArm::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{

}

void CSubArm::MoveUpdate(float deltaTime)
{
	//this->Move(20 ,deltaTime);
	this->Move(PI/4, D3DXVECTOR2(0,0), D3DXVECTOR2(100,0), deltaTime);
}

bool CSubArm::Move(D3DXVECTOR2 posCenter, float radian, double angleStart, double angleEnd, float deltaTime)
{
	bool direction = false;
	if(this->m_angle > angleEnd|| this->m_angle < angleStart)
	{
		this->m_angleDefault = -this->m_angleDefault;
		direction = true;
	}
	this->m_angle -= this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
	return direction;
}

bool CSubArm::Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, double angleStart, double angleEnd, float deltaTime)
{
	bool direction = false;
	this->m_angleDefault = (this->m_angleDefault > 0) ? vecAngle : -vecAngle;
	if(this->m_angle > angleEnd|| this->m_angle < angleStart)
	{
		this->m_angleDefault = -this->m_angleDefault;
		direction = true;
	}
	this->m_angle -= this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
	return direction;
}

void CSubArm::Move(D3DXVECTOR2 posCenter, float radian, bool direction, float deltaTime)
{
	if(direction)
	{
		this->m_angleDefault = -this->m_angleDefault;
	}
	this->m_angle -= this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
}

bool CSubArm::Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, double angleStart, double angleEnd, bool direction, float deltaTime)
{
	this->m_angleDefault = (this->m_angleDefault > 0) ? vecAngle : -vecAngle;
	bool direction1 = false;
	if(direction)
	{
		this->m_angleDefault = -this->m_angleDefault;
		this->m_angle = (this->m_angleDefault > 0) ? angleEnd : angleStart;
		direction1 = true;
	}
	this->m_angle -= this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
	return direction1;
}

bool CSubArm::Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, bool direction, float deltaTime)
{
	this->m_angleDefault = (this->m_angleDefault > 0) ? vecAngle : -vecAngle;
	bool direction1 = false;
	if(direction)
	{
		this->m_angleDefault = -this->m_angleDefault;
		direction1 = true;
	}
	this->m_angle -= this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
	return direction1;
}

void CSubArm::Move(D3DXVECTOR2 posCenter, float radian, double vecAngle, float deltaTime)
{
	this->m_angleDefault = (this->m_angleDefault > 0) ? vecAngle : -vecAngle;
	this->m_angle += this->m_angleDefault;
	this->m_radian = radian;
	this->m_posCenter = posCenter;
	this->m_pos.x = this->m_posCenter.x +  int(this->m_radian * std::cos(this->m_angle));
	this->m_pos.y = this->m_posCenter.y + int(this->m_radian * std::sin(this->m_angle));
}

void CSubArm::Move(float rotation, D3DXVECTOR2 posStart, D3DXVECTOR2 posEnd, float deltaTime)
{
	this->m_rotation = rotation;
	this->m_vx = this->m_vxDefault * sin(this->m_rotation);
	this->m_vy = this->m_vyDefault * cos(this->m_rotation);
	if(this->m_posCenter.x == 0 && this->m_posCenter.y == 0)
	{
		this->m_posCenter = posStart;
	}
	//tu trai qua phai
	if(posStart.x < posEnd.x && this->m_pos.x < posEnd.x)
	{
		this->m_posCenter.x += this->m_vx * deltaTime;
		this->m_posCenter.y += this->m_vy * deltaTime;
	}
	else if(posStart.x > posEnd.x && this->m_pos.x > posEnd.x)
	{
		this->m_posCenter.x -= this->m_vx * deltaTime;
		this->m_posCenter.y += this->m_vy * deltaTime;
	}
	this->m_pos.x = this->m_posCenter.x;
	this->m_pos.y = this->m_posCenter.y;
}

RECT* CSubArm::GetRectRS()
{
	RECT* rs = new RECT();
	rs->left = 0;
	rs->right = this->m_width;
	rs->top = 0;
	rs->bottom = this->m_height;
	return rs;
}

Box CSubArm::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}