#include "CBossArm.h"
#include "CDrawObject.h"

CBossArm::CBossArm()
{
	this->Init();
}

CBossArm::~CBossArm()
{
	this->m_pos = D3DXVECTOR2(0,0);

}

void CBossArm::Init()
{
	this->m_isChangeDirection = false;
	this->m_timeCurr = 0.0f;
	this->subArms = new CSubArm*[5];
	for (int i = 0; i < 5; i++)
	{
		this->subArms[i] = new CSubArm();
		if(i == 4)
			this->subArms[i]->SetArmType(SUB_ARM_TYPE::SUB_ARM_FIRST);
		else
			this->subArms[i]->SetArmType(SUB_ARM_TYPE::SUB_ARM_COMPONENT);
		this->subArms[i]->Init();
		this->subArms[i]->WaitForAppear = (5 -i)* 0.9;
	}


}

void CBossArm::Update(float deltaTime)
{
	for (int i = 0; i < 5; i++)
	{
		this->subArms[i]->Update(deltaTime);
	}
	this->MoveUpdate(deltaTime);
}

void CBossArm::Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{

}

void CBossArm::MoveUpdate(float deltaTime)
{
#pragma region TRANG THAI THANG DUNG
	for (int i = 0; i < 5; i++)
	{
		if(this->subArms[i]->IsAlive())
			this->subArms[i]->Move(PI/4, D3DXVECTOR2(90, 90), D3DXVECTOR2(90 + (i + 1)*22*sqrt(2), 90), deltaTime);
	}

#pragma endregion
#pragma region TRANG THAI DUA LEN DUA XUONG
	if(this->subArms[0]->IsAlive())
	{
		bool direction = this->subArms[1]->Move(this->subArms[0]->GetPos(), 22*sqrt(2) + 6, 0.07, -2*PI/3, 2*PI/3, deltaTime);
		//Neu cua dau doi dau
		//if(direction || (!direction && this->m_isChangeDirection))
		//{
		//	this->m_isChangeDirection = true;
		//	//this->m_isChangeDirection = direction;
		//	this->m_timeCurr += deltaTime;
		//	if(this->m_timeCurr > 2.0f)
		//	{
		//		//bool direction3 = this->subArms[2]->Move(this->subArms[1]->GetPos(), 22*sqrt(2), 0.02, true, deltaTime);
		//		this->m_timeCurr = 0;
		//		this->m_isChangeDirection = false;
		//	}
		//	else
		//	{
		//		this->subArms[1]->Move(this->subArms[0]->GetPos(), 22*sqrt(2), 0.00, -2*PI/3, 2*PI/3, deltaTime);
		//	}
		//}
		//else
		//{
		bool direction1 = this->subArms[2]->Move(this->subArms[1]->GetPos(), 22*sqrt(2)+ 6, 0.04, direction, deltaTime);
		//}
		bool direction2 = this->subArms[3]->Move(this->subArms[2]->GetPos(), 22*sqrt(2) + 6, 0.02, direction1, deltaTime);
		this->subArms[4]->Move(this->subArms[3]->GetPos(), 22*sqrt(2) + 6, 0.04, direction2, deltaTime);
		for (int i = 2; i < 5; i++)
		{
			//this->subArms[i]->Move(D3DXVECTOR2(90 + 22*sqrt(2), 90 + 22*sqrt(2)), i*22*sqrt(2), 0.08 - i*0.008/* - i*0.01*/, -7*PI/12 + (i - 1)*PI/20, PI/2, deltaTime);
		}
	}
#pragma endregion


}

void CBossArm::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if(this->subArms[i]->IsAlive())
			CDrawObject::GetInstance()->Draw(this->subArms[i]);
	}
}

void CBossArm::Move(float curve, float deltaTime)
{

}

RECT* CBossArm::GetRectRS()
{
	RECT* rs = new RECT();
	rs->left = 0;
	rs->right = this->m_width;
	rs->top = 0;
	rs->bottom = this->m_height;
	return rs;
}

Box CBossArm::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}