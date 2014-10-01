#include "CGameContra.h"
#include "CStateManagement.h"
#include "CStateLogo.h"	
#include "CDevice.h"
#include "CSprite.h"
#include "CTexture.h"

CGameContra::CGameContra()
{

}

void CGameContra::Init()
{
	CView::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDerect3D();
	//
	CTexture* sp = new CTexture();
	sp->LoadImage();
	//
	CStateManagement::GetInstance()->ChangeState(new CStateLogo());
}

void CGameContra::Destroy()
{

}