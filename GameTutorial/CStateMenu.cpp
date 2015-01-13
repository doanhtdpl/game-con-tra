#include "CStateMenu.h"	
#include <iostream>
#include "CDrawObject.h"
CStateMenu::CStateMenu()
{

}

CStateMenu::~CStateMenu()
{

}

void CStateMenu::Init()	
{
	this->mainMenu = new CMenuGame();
	this->mainMenu->SetPos(D3DXVECTOR2(this->mainMenu->GetWidth(), this->mainMenu->GetHeight() / 2));
}

void CStateMenu::Update(float detaTime)
{
	this->mainMenu->Update(detaTime);
}

void CStateMenu::Render()
{
	CDrawObject::GetInstance()->Draw(this->mainMenu);
}
void CStateMenu::Destroy()
{
}