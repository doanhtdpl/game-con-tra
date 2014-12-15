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

	this->effect = new CEnemyEffect(D3DXVECTOR2(100, 100));
	this->effect1 = new CExplosionEffect(D3DXVECTOR2(500, 100));
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
	CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//CLoadGameObject::GetInstance()->Draw();
	//Testing
	sObj->Update(deltaTime);
	nobj->Update(deltaTime);
	wobj->Update(deltaTime);
	wseObj->Update(deltaTime);
	if (wseObj->IsAlive()){
		wseObj->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}
	if (wseObj->item != NULL){
		wseObj->item->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}

	weObj->Update(deltaTime);
	if (weObj->IsAlive()){
		weObj->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}
	if (weObj->item != NULL){
		weObj->item->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}

	effect->Update(deltaTime);
	effect1->Update(deltaTime);
}

void CStateGamePlay::Render()
{
	
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	
	CDrawObject::GetInstance()->Draw(sObj);
	CDrawObject::GetInstance()->Draw(nobj);
	CDrawObject::GetInstance()->Draw(wobj);
	if (wseObj->IsAlive()){
		CDrawObject::GetInstance()->Draw(wseObj);
	}
	if (wseObj->effect != NULL){
		CDrawObject::GetInstance()->Draw(wseObj->effect);
	}
	if (wseObj->item != NULL){
		CDrawObject::GetInstance()->Draw(wseObj->item);
	}

	if (weObj->IsAlive()){
		CDrawObject::GetInstance()->Draw(weObj);
	}
	if (weObj->effect != NULL){
		CDrawObject::GetInstance()->Draw(weObj->effect);
	}
	if (weObj->item != NULL){
		CDrawObject::GetInstance()->Draw(weObj->item);
	}

	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
}
void CStateGamePlay::Destroy()
{

}