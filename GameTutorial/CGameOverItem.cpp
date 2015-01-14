#include "CGameOverItem.h"
#include "CCamera.h"


CGameOverItem::CGameOverItem(void)
{
	this->Init();
}

void CGameOverItem::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_imageCurr = new CTexture();
	this->m_imageCurr->LoadImageFromFile(__Game_Over_Item__, NULL);
	this->m_drawImg = new CSprite();
	//
	this->m_timeDelay = 3.0f;
}
void CGameOverItem::LoadAllTextureFromFile()
{
}

void CGameOverItem::Update(float deltaTime)
{
	D3DXVECTOR3 cameraPos = CCamera::GetInstance()->GetCameraPos();
	this->m_pos.x = cameraPos.x + 10;
	this->m_pos.y = cameraPos.y - 20;
	this->m_pos.z = 0;
}

void CGameOverItem::Draw()
{
	RECT rectRS;
	D3DXVECTOR3 posObj(this->m_pos.x, this->m_pos.y, 0);
	D3DXVECTOR3 posObjAfterTransform = CCamera::GetInstance()->GetPointTransform(posObj.x, posObj.y);

	rectRS.left = 0;
	rectRS.right = rectRS.left + 95;
	rectRS.top = 0;
	rectRS.bottom = rectRS.top + 49;

	this->m_drawImg->draw(this->m_imageCurr, &rectRS, posObjAfterTransform, D3DCOLOR_XRGB(255, 255, 225), false);
}
void CGameOverItem::SetPos(D3DXVECTOR3 pos)
{
	this->m_pos.x = pos.x;
	this->m_pos.y = pos.y;
	this->m_pos.z = pos.z;
}
CGameOverItem::~CGameOverItem()
{

}