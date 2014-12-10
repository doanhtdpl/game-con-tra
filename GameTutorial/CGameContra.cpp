#include "CGameContra.h"
#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CDevice.h"
#include "CInput.h"
#include "CManagementTexture.h"

CGameContra::CGameContra()
{

}

void CGameContra::Init()
{
	CView::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDirect3D();
	CInput::GetInstance()->InitInput(CView::m_hInstance);
	CInput::GetInstance()->InitKeyboard(CView::m_hwndWindow);
	CStateManagement::GetInstance()->ChangeState(new CStateLogo());
	CManagementTexture::GetInstance()->LoadAllResourceFromFile(__OBJECT_PATH__);
}

void CGameContra::Destroy()
{

}

void CGameContra::ProcessInput()
{
	CInput::GetInstance()->ProcessKeyboard();
	CInput::GetInstance()->Update();
}