#include "CCamera.h"

CCamera::CCamera()
{
	m_pos.x = 0;
	m_pos.y = 400;
	m_pos.z = 0;
	D3DXMatrixIdentity(&m_matrixTransform);
	m_matrixTransform._22 = -1;
}

CCamera::~CCamera()
{

}

void CCamera::Update(float x, float deltaTime)
{
		m_pos.x += x;
}

D3DXVECTOR3 CCamera::GetPointTransform(float x, float y)
{
	m_matrixTransform._41 = -m_pos.x;
	m_matrixTransform._42 = m_pos.y;
	D3DXVECTOR3 posCurr(x,y,0);
	D3DXVECTOR4 posResult;
	D3DXVec3Transform(&posResult, &posCurr, &m_matrixTransform);
	return D3DXVECTOR3(posResult.x, posResult.y, posResult.z);
}