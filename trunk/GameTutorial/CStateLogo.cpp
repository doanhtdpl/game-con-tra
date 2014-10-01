#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CStateMenu.h"

CStateLogo::CStateLogo()
{

}

CStateLogo::~CStateLogo()
{

}

void CStateLogo::Init()	
{
	m_count = 0;

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
	std::cout<<"Logo update lan "<<m_count;
}
void CStateLogo::Destroy()
{

}