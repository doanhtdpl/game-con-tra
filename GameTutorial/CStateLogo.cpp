#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture();
}

CStateLogo::~CStateLogo()
{

}

void CStateLogo::Init()	
{
	
	m_count = 0;
	//

}

void CStateLogo::Update()
{
	m_count ++;
	if(m_count > 10)
	{
		CStateManagement::GetInstance()->ChangeState(new CStateMenu());
	}
}

void CStateLogo::Render()
{
	//std::cout<<"Logo update lan "<<m_count;
	D3DVECTOR pos;
	pos.x = 50.0f;
	pos.y = 50.0f;
	pos.z = 0.0f;
	texture->LoadImage("E:\\SEMESTER_7\\Nhap mon game\\Game Contra\\GameContra\\Debug\\FireBomb.png", D3DCOLOR_XRGB(255,0,255));
	if(CDevice::s_d3ddv->BeginScene())
	{
		CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
		RECT rec;
		rec.left = 0;
		rec.right = rec.left + texture->GetUmageWidth();
		rec.bottom = 0;
		rec.top = rec.bottom - texture->GetImageHeight();
		sprite->draw(texture, NULL, pos, D3DCOLOR_XRGB(255,255,225), true);
		CDevice::s_spriteHandle->End();
		CDevice::s_d3ddv->EndScene();
	}

	//CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(255,255,255));
	CDevice::s_d3ddv->Present(NULL,NULL,NULL,NULL);
}
void CStateLogo::Destroy()
{

}