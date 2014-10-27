#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CLoadBackGround.h"
#include "CLoadGameObject.h"
#include "CDrawObject.h"
#include "CCollision.h"

CStateLogo::CStateLogo()
{
	this->hideObj = new CHidenObject();
	this->sObj = new CSoldier();
}

CStateLogo::~CStateLogo()
{

}

void CStateLogo::Init()	
{
	CCamera::GetInstance()->Update(CContra::GetInstance()->GetPos().x - 400, 0.0f);
	CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
	CLoadBackGround::GetInstance()->ChangeBackGround(10);
	CLoadGameObject::GetInstance()->LoadReSourceFromFile();
	CLoadGameObject::GetInstance()->ChangeMap(10);
	//Test collision
	isCollision = false;
	increse = 0.0f;
}

void CStateLogo::Update(float deltaTime)
{
	CLoadGameObject::GetInstance()->Update();
	sObj->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
	//CContra::GetInstance()->HandleCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//Vi du ve va cham giua hai doi tuong
	/*first = CContra::GetInstance()->GetBox();
	second = hideObj->GetBox();
	broadphaseBox = CCollision::GetInstance()->GetSweptBroadphaseBox(first, deltaTime);*/
	//if(CCollision::GetInstance()->AABBCheck(broadphaseBox, second))
	//{
	//	float normalx, normaly;
	//	collisiontime = CCollision::GetInstance()->SweptAABB(first, second, normalx, normaly, deltaTime);
	//	//first.x += first.vx * collisiontime;
	//	//first.y += first.vy * collisiontime;
	//	if (collisiontime < 1.0f && collisiontime > 0.0f)
	//	{
	//		if(collisiontime <= deltaTime)
	//		{
	//			CContra::GetInstance()->SetPosY(CContra::GetInstance()->GetPosY() - 400 * collisiontime); 
	//		}
	//		else
	//		{
	//			CContra::GetInstance()->SetPosY(CContra::GetInstance()->GetPosY() - 400 * deltaTime);
	//		}
	//		//CContra::GetInstance()->SetVelocityY(0);
	//	}
	//}
	//else
	//{
	//	CContra::GetInstance()->SetPosY(CContra::GetInstance()->GetPosY() - 400 * deltaTime);
	//}
}

void CStateLogo::Render()
{
	CLoadGameObject::GetInstance()->Draw();
	CLoadBackGround::GetInstance()->Draw();
	for (int i = 0; i < CContra::GetInstance()->m_listBullet.size(); i++)
	{
		CDrawObject::GetInstance()->Draw(CContra::GetInstance()->m_listBullet[i]);
	}
	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
	CDrawObject::GetInstance()->Draw(hideObj);
	CDrawObject::GetInstance()->Draw(sObj);
}
void CStateLogo::Destroy()
{

}