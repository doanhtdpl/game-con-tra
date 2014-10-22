#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CLoadBackGround.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture*[3];
	this->simon = new CSimon();
	for (int i = 0; i < 3; i++)
	{
		this->texture[i] = new CTexture();
	}
}

CStateLogo::~CStateLogo()
{

}

void CStateLogo::Init()	
{
	CLoadBackGround::GetInstance()->LoadAllResourceFromFile();
	CLoadBackGround::GetInstance()->ChangeBackGround(10);
	texture[0]->LoadImageFromFile(__CONTRA_PATH__, D3DCOLOR_XRGB(255,0,255));
	texture[1]->LoadImageFromFile(__SIMON_PATH__, D3DCOLOR_XRGB(255,0,255));
	texture[2]->LoadImageFromFile(__BULLET_PATH__, D3DCOLOR_XRGB(255,0,255));
	m_count = 0;

}

void CStateLogo::Update(float deltaTime)
{
	//this->simon->Update(deltaTime);
	CContra::GetInstance()->Update(deltaTime);
}

void CStateLogo::Render()
{
	D3DVECTOR posOfContra;
	posOfContra.x = CContra::GetInstance()->GetPos().x;
	posOfContra.y = CContra::GetInstance()->GetPos().y;
	posOfContra = CCamera::GetInstance()->GetPointTransform(posOfContra.x, posOfContra.y);
	//Draw simon
	CLoadBackGround::GetInstance()->Draw();
	for (int i = 0; i < CContra::GetInstance()->m_listBullet.size(); i++)
	{
		D3DXVECTOR3 pos;
		pos.x = CContra::GetInstance()->m_listBullet.at(i)->GetPos().x;
		pos.y = CContra::GetInstance()->m_listBullet.at(i)->GetPos().y;
		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		sprite->draw(texture[2], CContra::GetInstance()->m_listBullet.at(i)->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
	}
	if(CContra::GetInstance()->m_left)
		sprite->drawFlipX(texture[0], CContra::GetInstance()->GetRectRS(), posOfContra, D3DCOLOR_XRGB(255,255,225), true);
	else
		sprite->draw(texture[0], CContra::GetInstance()->GetRectRS(), posOfContra, D3DCOLOR_XRGB(255,255,225), true);
}
void CStateLogo::Destroy()
{

}