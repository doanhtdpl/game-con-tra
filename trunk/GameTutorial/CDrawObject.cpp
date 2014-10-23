#include "CDrawObject.h"
#include "CManagementTexture.h"
#include "CTexture.h"
#include "CCamera.h"

CDrawObject::CDrawObject()
{
	this->m_draw = new CSprite();
}

void CDrawObject::Draw(CGameObject* obj)
{
	//Kiem tra doi tuong khac null
	if(obj)
	{
		//Neu doi tuong khong phai la hide object thi ve len ma hinh
		if(obj->ClassName() != __CLASS_NAME__(CDrawObject))
		{
			int typeObject = obj->GetIDType();
			int idObject = obj->GetID();
			//Kiem tra xem Id cua doi tuong no co hop le hay khong
			if(typeObject > 0)
			{
				//Lay ra resource anh cua doi tuong
				CTexture* texture = CManagementTexture::GetInstance()->GetTextureByID(idObject, typeObject);
				//Neu ton tai texture 
				if(texture && this->m_draw)
				{
					D3DXVECTOR2 posObj = obj->GetPos();
 					D3DXVECTOR3 posObjAfterTransform = CCamera::GetInstance()->GetPointTransform(posObj.x, posObj.y);
					//Ve theo huong cua Object
					if(!obj->GetDirection())
					{
						this->m_draw->draw(texture, obj->GetRectRS(), posObjAfterTransform, D3DCOLOR_XRGB(255,255,255), true);
					}else
					{
						this->m_draw->drawFlipX(texture, obj->GetRectRS(), posObjAfterTransform, D3DCOLOR_XRGB(255,255,255), true);
					}
				}
			}
		}
	}
}

CDrawObject::~CDrawObject()
{
	if(this->m_draw)
		delete this->m_draw;
}