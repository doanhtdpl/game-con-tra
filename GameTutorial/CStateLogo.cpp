#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture();
	this->contra = new CContra();
}

CStateLogo::~CStateLogo()
{

}

void CStateLogo::Init()	
{
	texture->LoadImage(__CONTRA_PATH__, D3DCOLOR_XRGB(255,0,255));
	m_count = 0;
	//

}

void CStateLogo::Update(float deltaTime)
{
	this->contra->Update(deltaTime);
	m_count ++;
	//if(m_count > 10)
	//{
	//	CStateManagement::GetInstance()->ChangeState(new CStateMenu());
	//}
}

void CStateLogo::Render()
{
	//std::cout<<"Logo update lan "<<m_count;
	D3DVECTOR pos;
	pos.x = this->contra->GetPos().x;
	pos.y = this->contra->GetPos().y;
	pos.z = 0.0f;
	CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(0,0,0));
	if(CDevice::s_d3ddv->BeginScene())
	{
		CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->draw(texture, this->contra->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), false);
		CDevice::s_spriteHandle->End();
		CDevice::s_d3ddv->EndScene();
	}

	//CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(255,255,255));
	CDevice::s_d3ddv->Present(NULL,NULL,NULL,NULL);
}
void CStateLogo::Destroy()
{

}