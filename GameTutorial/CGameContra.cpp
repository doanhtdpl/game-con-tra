#include "CGameContra.h"
#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CDevice.h"


CGameContra::CGameContra()
{

}

void CGameContra::Init()
{
	CView::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDerect3D();
	CStateManagement::GetInstance()->ChangeState(new CStateLogo());
}

void CGameContra::Destroy()
{

}