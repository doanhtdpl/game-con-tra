#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CLoadBackGround.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture*[2];
	this->contra = new CContra();
	this->simon = new CSimon();
	for (int i = 0; i < 2; i++)
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
	m_count = 0;

}

void CStateLogo::Update(float deltaTime)
{
	//this->simon->Update(deltaTime);
	this->contra->Update(deltaTime);
}

void CStateLogo::Render()
{
	D3DVECTOR posOfContra;
	posOfContra.x = this->contra->GetPos().x;
	posOfContra.y = this->contra->GetPos().y;
	posOfContra = CCamera::GetInstance()->GetPointTransform(posOfContra.x, posOfContra.y);
	//Draw simon
	CLoadBackGround::GetInstance()->Draw();
	if(this->contra->m_left)
		sprite->drawFlipX(texture[0], this->contra->GetRectRS(), posOfContra, D3DCOLOR_XRGB(255,255,225), true);
	else
		sprite->draw(texture[0], this->contra->GetRectRS(), posOfContra, D3DCOLOR_XRGB(255,255,225), true);
}
void CStateLogo::Destroy()
{

}