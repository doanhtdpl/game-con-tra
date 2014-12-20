#include "CStateManagement.h"
#include "CStateGamePlay.h"	
#include "CStateMenu.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CLoadBackGround.h"
#include "CLoadGameObject.h"
#include "CDrawObject.h"
#include "CCollision.h"
#include "CPoolingObject.h"
#include "CManageAudio.h"

CStateGamePlay::CStateGamePlay()
{
	this->sObj = new CSoldier();
	this->sObj->SetAlive(true);
	//this->br = new CBridge();
	//this->nobj = new CSniper();
	//this->wobj = new CWallTurret();
	this->weObj = new CWeapon();
	//this->wseObj = new CSWeapon();
	//
	//this->defCannonObj = new CDefenseCannon();
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

	// Khoi tao enemy effect
	CPoolingObject::GetInstance()->CreateEnemyEffect(15);
	CPoolingObject::GetInstance()->CreateExplosionEffect(15);
	CPoolingObject::GetInstance()->CreateBulletItem(3);
	CPoolingObject::GetInstance()->CreateSoliderObject(10);
	//Load Audio
	ManageAudio::GetInstance()->playSound(TypeAudio::AUDIO_BACKGROUND_STATE_1);
}

void CStateGamePlay::Update(float deltaTime)
{
	CLoadGameObject::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	CLoadGameObject::GetInstance()->Draw();
	////Testing
	sObj->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//nobj->Update(deltaTime);
	//wobj->Update(deltaTime);
	//wseObj->Update(deltaTime);
	//if (wseObj->IsAlive()){
	//	wseObj->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//}
	//if (wseObj->item != NULL){
	//	wseObj->item->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	//}

	weObj->Update(deltaTime);
	if (weObj->IsAlive()){
		weObj->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}

	CPoolingObject::GetInstance()->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());

	/*br->Update(deltaTime);
	if (br->IsAlive()){
		br->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	}*/
}

void CStateGamePlay::Render()
{
	
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	
	if(sObj->IsAlive())
		CDrawObject::GetInstance()->Draw(sObj);
	/*CDrawObject::GetInstance()->Draw(nobj);
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
	*/
	if (weObj->IsAlive()){
		CDrawObject::GetInstance()->Draw(weObj);
	}/*
	if (weObj->effect != NULL){
		CDrawObject::GetInstance()->Draw(weObj->effect);
	}
	if (weObj->item != NULL){
		CDrawObject::GetInstance()->Draw(weObj->item);
	}
	*/
	/*if (br->IsAlive())
		CDrawObject::GetInstance()->Draw(br);*/

	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
	// Draw enemy effect
	CPoolingObject::GetInstance()->Draw();
}
void CStateGamePlay::Destroy()
{

}