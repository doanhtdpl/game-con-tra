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

CStateGamePlay::CStateGamePlay(int mapId)
{
	this->m_mapId = mapId;
}

CStateGamePlay::~CStateGamePlay()
{

}

void CStateGamePlay::Init()	
{
	//CCamera::GetInstance()->Update(CContra::GetInstance()->GetPos().x - 400, 0.0f);
	CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
	CLoadGameObject::GetInstance()->LoadReSourceFromFile();
	//Tinh
	CLoadBackGround::GetInstance()->ChangeBackGround(this->m_mapId);
	CLoadGameObject::GetInstance()->ChangeMap(this->m_mapId);
	
	// Khoi tao enemy effect
	CPoolingObject::GetInstance()->CreateEnemyEffect(30);
	CPoolingObject::GetInstance()->CreateExplosionEffect(30);
	CPoolingObject::GetInstance()->CreateBulletEffect(40);
	CPoolingObject::GetInstance()->CreateBulletItem(20);

	// Tinh
	switch (this->m_mapId)
	{
	case 10:
	{
			   CPoolingObject::GetInstance()->CreateSoliderObject(10);
			   break;
	}
	case 11:
	{
			   CPoolingObject::GetInstance()->CreateSoliderShootObject(10);
			   CPoolingObject::GetInstance()->CreateBigStone(10);
			   break;
	}
	case 12:
	{
			   CPoolingObject::GetInstance()->CreateSoliderShootObject(10);
			   CPoolingObject::GetInstance()->CreateCapsuleBoss(20);
			   CPoolingObject::GetInstance()->CreateBulletLaze(10);
			   break;
	}
	}
	//TT
	CPoolingObject::GetInstance()->CreateWeapon(15);
	//Load Audio
	//ManageAudio::GetInstance()->playSound(TypeAudio::AUDIO_BACKGROUND_STATE_1);
}

void CStateGamePlay::Update(float deltaTime)
{
	CLoadGameObject::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
	CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	CPoolingObject::GetInstance()->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
	CLoadBackGround::GetInstance()->Update(deltaTime);
}

void CStateGamePlay::Render()
{
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	//Draw Object
	CDrawObject::GetInstance()->Draw(CContra::GetInstance());
	// Draw Pooling Object
	CPoolingObject::GetInstance()->Draw();
	///
}
void CStateGamePlay::Destroy()
{

}