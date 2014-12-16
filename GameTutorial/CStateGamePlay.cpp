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
	this->br = new CBridge();
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

	br->Update(deltaTime);
	if (br->IsAlive()){
		br->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}
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
	
	if (br->IsAlive())
		CDrawObject::GetInstance()->Draw(br);
	if (br->effect != NULL && br->effect->IsAlive()){
		CDrawObject::GetInstance()->Draw(br->effect);
	}
	//if (br->effect1 != NULL){
	//	CDrawObject::GetInstance()->Draw(br->effect1);
	//}
	//if (br->effect2 != NULL){
	//	CDrawObject::GetInstance()->Draw(br->effect2);
	//}

	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
}
void CStateGamePlay::Destroy()
{

}