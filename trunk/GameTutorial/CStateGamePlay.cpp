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
	ManageAudio::GetInstance()->playSound(TypeAudio::AUDIO_BACKGROUND_STATE_1);
	//Tinh--> gameover item
	this->m_gameOverItem = new CGameOverItem();
	//Tinh --> man hinh diem
	this->m_scoreScense = new CScoreScense();
}

void CStateGamePlay::Update(float deltaTime)
{
	if (!CContra::GetInstance()->m_isGameOver)//Tinh test 14/1
	{
		CLoadGameObject::GetInstance()->Update(deltaTime);
		CContra::GetInstance()->Update(deltaTime);
		CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		CLoadBackGround::GetInstance()->Update(deltaTime);

	}
	else
	{
		//Sau do cho 1 thoi gian ve man hinh diem
		if (this->m_gameOverItem->m_timeDelay <= 0 && !this->m_isGameOverred)
		{
			this->m_gameOverItem->m_timeDelay = 0.80f;
			//Load man hinh diem so len
			this->m_isGameOverred = true;
		}
		else
			this->m_gameOverItem->m_timeDelay -= deltaTime;
		if (this->m_isGameOverred)
			this->m_scoreScense->Update(deltaTime);
	}
	//Van update binh thuong cac doi tuong pooling
	if (!CContra::GetInstance()->m_isGameOver)//Tinh test 14/1
		CPoolingObject::GetInstance()->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
}

void CStateGamePlay::Render()
{
	CLoadBackGround::GetInstance()->Draw();
	//
	if (!CContra::GetInstance()->m_isGameOver)//Tinh test 14/1
	{
		CLoadGameObject::GetInstance()->Draw();
		//Draw Object
		//CDrawObject::GetInstance()->Draw(CContra::GetInstance());
		if (CContra::GetInstance()->m_isHided)
		{
			CDrawObject::GetInstance()->Draw(CContra::GetInstance(), D3DCOLOR_ARGB(127, 255, 255, 255));
		}
		else
		{
			CDrawObject::GetInstance()->Draw(CContra::GetInstance(), D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// Draw Pooling Object
		CPoolingObject::GetInstance()->Draw();
	}
	else
	{
		//Tinh-> ve game over item
		this->m_gameOverItem->Draw();

		if (this->m_isGameOverred)
		{
			///Ve man hinh diem
			D3DXVECTOR3 cameraPos = CCamera::GetInstance()->GetCameraPos();
			this->m_scoreScense->SetPos(D3DXVECTOR2(cameraPos.x + this->m_scoreScense->GetWidth() / 2, cameraPos.y - this->m_scoreScense->GetHeight() / 2));
			//
			this->m_scoreScense->InitScore(89712315);
			this->m_scoreScense->InitNameStage(CMenuGame::m_mapId);
			this->m_scoreScense->Draw();
		}
	}
	//
	CLifeItem::GetInstance()->Draw();
}

void CStateGamePlay::Destroy()
{

}