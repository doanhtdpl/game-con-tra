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
}

CStateGamePlay::~CStateGamePlay()
{

}

void CStateGamePlay::Init()	
{
	//CCamera::GetInstance()->Update(CContra::GetInstance()->GetPos().x - 400, 0.0f);
	CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
	CLoadBackGround::GetInstance()->ChangeBackGround(12);
	CLoadGameObject::GetInstance()->LoadReSourceFromFile();
	CLoadGameObject::GetInstance()->ChangeMap(12);

	// Khoi tao enemy effect
	CPoolingObject::GetInstance()->CreateEnemyEffect(15);
	CPoolingObject::GetInstance()->CreateExplosionEffect(15);
	CPoolingObject::GetInstance()->CreateBulletItem(10);
	CPoolingObject::GetInstance()->CreateSoliderObject(10);
	CPoolingObject::GetInstance()->CreateSoliderShootObject(10);
	CPoolingObject::GetInstance()->CreateBigStone(10);
	CPoolingObject::GetInstance()->CreateCapsuleBoss(10);
	CPoolingObject::GetInstance()->CreateBulletLaze(10);
	// TT
	CPoolingObject::GetInstance()->CreateWeapon(15);
	//Load Audio
	//ManageAudio::GetInstance()->playSound(TypeAudio::AUDIO_BACKGROUND_STATE_1);
}

void CStateGamePlay::Update(float deltaTime)
{
	CLoadGameObject::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	CLoadGameObject::GetInstance()->Draw();
	CPoolingObject::GetInstance()->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	CLoadBackGround::GetInstance()->Update(deltaTime);
}

void CStateGamePlay::Render()
{
	
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	//if(CContra::GetInstance()->IsAlive())
	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
	// Draw enemy effect
	CPoolingObject::GetInstance()->Draw();
}
void CStateGamePlay::Destroy()
{

}