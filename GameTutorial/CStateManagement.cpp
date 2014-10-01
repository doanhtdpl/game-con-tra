#include "CStateManagement.h"

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
			this->m_pCurrent->Update();
		}
		this->m_pCurrent->Render();
	}
}

void CStateManagement::ChangeState(CState* state)
{
	this->m_pNext = state;
}