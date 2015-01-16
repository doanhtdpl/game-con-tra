#include "CStateMenu.h"	
#include <iostream>
#include "CDrawObject.h"
#include "CContra.h"
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

	//if (CContra::GetInstance()->m_isGameOver)
	//{
	//	this->scoreScense = new CScoreScense();
	//	this->scoreScense->SetPos(D3DXVECTOR2(this->scoreScense->GetWidth(), this->scoreScense->GetHeight() / 2));
	//}
	
}

void CStateMenu::Update(float detaTime)
{
	this->mainMenu->Update(detaTime);
	if (CContra::GetInstance()->m_isGameOver)
	{
		this->scoreScense->Update(detaTime);
	}
}

void CStateMenu::Render()
{
	CDrawObject::GetInstance()->Draw(this->mainMenu);
	if (CContra::GetInstance()->m_isGameOver)
	{
		CDrawObject::GetInstance()->Draw(this->scoreScense);
	}
}

void CStateMenu::Destroy()
{
}