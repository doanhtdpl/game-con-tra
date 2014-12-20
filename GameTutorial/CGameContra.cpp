#include "CGameContra.h"
#include "CStateManagement.h"
#include "CStateGamePlay.h"	
#include "CDevice.h"
#include "CInput.h"
#include "CManagementTexture.h"
#include "CManageAudio.h"

CGameContra::CGameContra()
{

}

void CGameContra::Init()
{
	CView::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDerect3D();
	CInput::GetInstance()->InitInput(CView::m_hInstance);
	CInput::GetInstance()->InitKeyboard(CView::m_hwndWindow);
	CStateManagement::GetInstance()->ChangeState(new CStateGamePlay());
	CManagementTexture::GetInstance()->LoadAllResourceFromFile(__OBJECT_PATH__);

	//Audio
	ManageAudio::GetInstance()->init_DirectSound(CView::m_hwndWindow);
	ManageAudio::GetInstance()->readFileAudio();
}

void CGameContra::Destroy()
{

}

void CGameContra::ProcessInput()
{
	CInput::GetInstance()->ProcessKeyboard();
	CInput::GetInstance()->Update();
}