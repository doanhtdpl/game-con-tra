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

	// Init life //TT
	for (int i = 0; i < CContra::GetInstance()->m_countAlive; i++)
	{
		CLifeItem* lifeItem = new CLifeItem();
		lifeItem->SetAlive(true);
		this->m_listLifeItem.push_back(lifeItem);
	}
	//Tinh--> gameover item
	this->m_gameOverItem = new CGameOverItem();

}

void CStateGamePlay::Update(float deltaTime)
{
	if (!CContra::GetInstance()->m_isGameOver)//Tinh test 14/1
	{
		CLoadGameObject::GetInstance()->Update(deltaTime);
		CContra::GetInstance()->Update(deltaTime);
		CContra::GetInstance()->OnCollision(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
		CLoadBackGround::GetInstance()->Update(deltaTime);

		//TT
		//Cap nhat giam item mang theo mang contra //Tinh
		if (CContra::GetInstance()->m_countAlive < this->m_listLifeItem.size())
		{
			int count = this->m_listLifeItem.size() - CContra::GetInstance()->m_countAlive;
			if (count > 0)
			{
				for (std::vector<CLifeItem*>::iterator it = this->m_listLifeItem.end() - 1; it != this->m_listLifeItem.begin(); --it)
				{
					if (count != 0)
					{
						CLifeItem* obj = *it;
						obj->SetAlive(false);
						count--;
					}
				}
			}
		}
		for (std::vector<CLifeItem*>::iterator it = this->m_listLifeItem.begin(); it != this->m_listLifeItem.end(); ++it)
		{
			CLifeItem* obj = *it;
			obj->Update(deltaTime);
		}
	}
	else
	{
		////Sau do cho 1 thoi gian ve man hinh diem
		//if (this->m_gameOverItem->m_timeDelay <= 0)
		//{
		//	this->m_gameOverItem->m_timeDelay = 3.0f;
		//	//Load man hinh diem so len
		//	
		//}
		//this->m_gameOverItem->m_timeDelay -= deltaTime;
	}
	//Van update binh thuong cac doi tuong pooling
	CPoolingObject::GetInstance()->Update(deltaTime, CLoadGameObject::GetInstance()->GetListGameObjectOnScreen());
}

void CStateGamePlay::Render()
{
	CLoadBackGround::GetInstance()->Draw();
	CLoadGameObject::GetInstance()->Draw();
	//Draw Object
	if (!CContra::GetInstance()->m_isGameOver)//Tinh test 14/1
		CDrawObject::GetInstance()->Draw(CContra::GetInstance());
	// Draw Pooling Object
	CPoolingObject::GetInstance()->Draw();
	///

	//TT
	int i = 0;
	if (CContra::GetInstance()->m_countAlive > 0)
	{
		for (std::vector<CLifeItem*>::iterator it = this->m_listLifeItem.begin(); it != this->m_listLifeItem.end(); ++it)
		{
			CLifeItem* obj = *it;
			D3DXVECTOR3 pos = obj->GetPos();
			pos.x = pos.x + 25 * i;
			obj->SetPos(pos);
			i++;
			if (i > CContra::GetInstance()->m_countAlive)
			{
				i = 0;
			}
			obj->Draw();
		}
	}

	//Tinh->game over item
	if (CContra::GetInstance()->m_isGameOver)
	{
		D3DXVECTOR3 cameraPos = CCamera::GetInstance()->GetCameraPos();
		D3DXVECTOR3 posGameOverItem = D3DXVECTOR3(posGameOverItem.x = cameraPos.x + 10, posGameOverItem.y = cameraPos.y - 10, posGameOverItem.z = 0);
		this->m_gameOverItem->SetPos(posGameOverItem);
		this->m_gameOverItem->Draw(); 
	}
}

void CStateGamePlay::Destroy()
{

}