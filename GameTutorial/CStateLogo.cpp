#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture();
	this->contra = new CContra*[6];
	for (int i = 0; i < 6; i++)
	{
		this->contra[i] = new CContra();
	}
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

int temp = 1;
float timeDelay = 0.0f;
void CStateLogo::Update(float deltaTime)
{
	timeDelay += deltaTime;
	if(temp < 6)
	{
		if(timeDelay > 2.5f)
		{
			timeDelay = 0.0f;
				temp++;
		}
	}
	//temp = 4;
	for (int i = 0; i < temp; i++)
	{
		this->contra[i]->Update(deltaTime);
	}
	
	m_count ++;
	//if(m_count > 10)
	//{
	//	CStateManagement::GetInstance()->ChangeState(new CStateMenu());
	//}
}

void CStateLogo::Render()
{
	//std::cout<<"Logo update lan "<<m_count;
	CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(0,0,0));

		if(CDevice::s_d3ddv->BeginScene())
		{
			for (int i = 0; i < temp; i++)
			{
				D3DVECTOR pos;
				pos.x = this->contra[i]->GetPos().x;
				pos.y = this->contra[i]->GetPos().y;
				pos.z = 0.0f;
					CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
					if(this->contra[i]->m_left)
						sprite->drawFlipX(texture, this->contra[i]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
					else
						sprite->draw(texture, this->contra[i]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
					CDevice::s_spriteHandle->End();
					CDevice::s_d3ddv->EndScene();
			}
		}



	//CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(255,255,255));
	CDevice::s_d3ddv->Present(NULL,NULL,NULL,NULL);
}
void CStateLogo::Destroy()
{

}