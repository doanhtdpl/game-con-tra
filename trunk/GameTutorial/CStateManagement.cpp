#include "CStateManagement.h"
#include "CDevice.h"

/*CStateManagement* CStateManagement::m_instante = nullptr;

CStateManagement* CStateManagement::GetInstance()
{
	if(m_instante == nullptr)
	{
		m_instante = new CStateManagement();
	}
	return m_instante;
}

*/


void CStateManagement::Update(bool isUpdate, float deltaTime)
{
	if(this->m_pCurrent != this->m_pNext)
	{
		if(this->m_pCurrent)
		{
			this->m_pCurrent->Destroy();
			delete this->m_pCurrent;
		}
		if(this->m_pNext)
		{
			this->m_pNext->Init();
		}
		this->m_pCurrent = this->m_pNext;
	}
	if(m_pCurrent)
	{
		if(!isUpdate)
		{
			this->m_pCurrent->Update(deltaTime);
		}
		CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(0,0,0));
		if(CDevice::s_d3ddv->BeginScene())
		{
			CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
			this->m_pCurrent->Render();
			CDevice::s_spriteHandle->End();
			CDevice::s_d3ddv->EndScene();
		}
		CDevice::s_d3ddv->Present(NULL,NULL,NULL,NULL);
	}
}

void CStateManagement::ChangeState(CState* state)
{
	this->m_pNext = state;
}