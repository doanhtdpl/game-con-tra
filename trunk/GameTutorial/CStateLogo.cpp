#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"
#include "CDevice.h"

CStateLogo::CStateLogo()
{
	this->sprite = new CSprite();
	this->texture = new CTexture*[2];
	this->contra = new CContra*[6];
	for (int i = 0; i < 6; i++)
	{
		this->contra[i] = new CContra();
	}
	this->simon = new CSimon*[6];
	for (int i = 0; i < 6; i++)
	{
		this->simon[i] = new CSimon();
	}

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
	texture[0]->LoadImage(__CONTRA_PATH__, D3DCOLOR_XRGB(255,0,255));
	texture[1]->LoadImage(__SIMON_PATH__, D3DCOLOR_XRGB(255,0,255));
	m_count = 0;
	//

}

int temp = 1;
float timeDelay = 0.0f;
void CStateLogo::Update(float deltaTime)
{
	timeDelay += deltaTime;
	if(temp < 12)
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

		if(i % 2 == 0)
		{
			if(i > 5)
			{
				this->simon[i - 6]->Update(deltaTime);
			}
			else
				this->simon[i]->Update(deltaTime);
		}
		else
		{
			if(i > 5)
			{
				this->contra[i - 6]->Update(deltaTime);
			}
			else
				this->contra[i]->Update(deltaTime);
		}
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
					CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
					if(i % 2 == 0)
					{
						if(i > 5)
						{
							//simon
							D3DVECTOR pos1;
							pos1.x = this->simon[i - 6]->GetPos().x;
							pos1.y = this->simon[i - 6]->GetPos().y;
							pos1.z = 0.0f;
							//ve simon
							if(!this->simon[i - 6]->m_left)
								sprite->drawFlipX(texture[1], this->simon[i - 6]->GetRectRS(), pos1, D3DCOLOR_XRGB(255,255,225), true);
							else
								sprite->draw(texture[1], this->simon[i - 6]->GetRectRS(), pos1, D3DCOLOR_XRGB(255,255,225), true);
						}
						else
						{
							//simon
							D3DVECTOR pos1;
							pos1.x = this->simon[i]->GetPos().x;
							pos1.y = this->simon[i]->GetPos().y;
							pos1.z = 0.0f;
							//ve simon
							if(!this->simon[i]->m_left)
								sprite->drawFlipX(texture[1], this->simon[i]->GetRectRS(), pos1, D3DCOLOR_XRGB(255,255,225), true);
							else
								sprite->draw(texture[1], this->simon[i]->GetRectRS(), pos1, D3DCOLOR_XRGB(255,255,225), true);
						}
						
					}
					else
					{
						if(i > 5)
						{
							D3DVECTOR pos;
							pos.x = this->contra[i - 6]->GetPos().x;
							pos.y = this->contra[i - 6]->GetPos().y;
							pos.z = 0.0f;
							if(this->contra[i - 6]->m_left)
								sprite->drawFlipX(texture[0], this->contra[i - 6]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
							else
								sprite->draw(texture[0], this->contra[i - 6]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
						}
						else
						{
							D3DVECTOR pos;
							pos.x = this->contra[i]->GetPos().x;
							pos.y = this->contra[i]->GetPos().y;
							pos.z = 0.0f;
							if(this->contra[i]->m_left)
								sprite->drawFlipX(texture[0], this->contra[i]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
							else
								sprite->draw(texture[0], this->contra[i]->GetRectRS(), pos, D3DCOLOR_XRGB(255,255,225), true);
						}
					}
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