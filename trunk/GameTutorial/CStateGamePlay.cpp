#include "CStateManagement.h"
#include "CStateGamePlay.h"	
#include "CStateMenu.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CLoadBackGround.h"
#include "CLoadGameObject.h"
#include "CDrawObject.h"
#include "CCollision.h"

CStateGamePlay::CStateGamePlay()
{
	this->sObj = new CSoldier();
	this->nobj = new CSniper();
	this->wobj = new CWallTurret();
	this->weObj = new CWeapon();
	this->wseObj = new CSWeapon();
}

CStateGamePlay::~CStateGamePlay()
{

}

void CStateGamePlay::Init()	
{
	//CCamera::GetInstance()->Update(CContra::GetInstance()->GetPos().x - 400, 0.0f);
	CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
	CLoadBackGround::GetInstance()->ChangeBackGround(10);
	CLoadGameObject::GetInstance()->LoadReSourceFromFile();
	CLoadGameObject::GetInstance()->ChangeMap(10);
	//Test collision
	isCollision = false;
	increse = 0.0f;
}

void CStateGamePlay::Update(float deltaTime)
{
	CLoadGameObject::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
	//CLoadGameObject::GetInstance()->Draw();
	CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//Testing
	sObj->Update(deltaTime);
	nobj->Update(deltaTime);
	wobj->Update(deltaTime);
	weObj->Update(deltaTime);
	wseObj->Update(deltaTime);
}

void CStateGamePlay::Render()
{
	
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	for (int i = 0; i < CContra::GetInstance()->m_listBullet.size(); i++)
	{
		CDrawObject::GetInstance()->Draw(CContra::GetInstance()->m_listBullet[i]);
	}
	for (int i = 0; i < nobj->m_listBullet.size(); i++)
	{
		CDrawObject::GetInstance()->Draw(nobj->m_listBullet[i]);
	}
	for (int i = 0; i < wobj->m_listBullet.size(); i++)
	{
		CDrawObject::GetInstance()->Draw(wobj->m_listBullet[i]);
	}
	CDrawObject::GetInstance()->Draw(sObj);
	CDrawObject::GetInstance()->Draw(nobj);
	CDrawObject::GetInstance()->Draw(wobj);
	CDrawObject::GetInstance()->Draw(weObj);
	CDrawObject::GetInstance()->Draw(wseObj);
	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
}
void CStateGamePlay::Destroy()
{

}