#include "CWeapon.h"
#include "CCollision.h"
#include "CContra.h"
#include "CDrawObject.h"

CWeapon::CWeapon(void)
{
	this->Init();
}

CWeapon::CWeapon(const std::vector<int>& info)
{
	this->Init();//
	if (!info.empty())
	{
		this->m_id = info.at(0) % 1000;
		this->m_idType = info.at(0) / 1000;
		this->m_pos = D3DXVECTOR2(info.at(1), info.at(2));
		this->m_width = info.at(3);
		this->m_height = info.at(4);
	}
}

void CWeapon::Init()
{
	//Khoi tao cac thong so cua doi tuong
	this->m_id = 2;
	this->m_idType = 20;
	this->m_idImage = 0;
	this->m_isALive = true;
	this->m_isAnimatedSprite = true;
	this->m_width = 54.0f;//56.0f; //78
	this->m_height = 30.0f; //88.0f; //84
	this->m_pos = D3DXVECTOR2(100.0f, 200.0f);
	//Khoi tao cac thong so di chuyen
	this->m_isJumping = false;
	this->m_isMoveLeft = false;
	this->m_isMoveRight = true;
	this->m_a = 700.0f;
	this->m_canJump = false;
	this->m_jumpMax = 0.0f;
	//this->m_currentJump = 0.0f;
	this->m_vxDefault = 180.0f;
	this->m_vyDefault = 100.0f;
	this->m_vx = this->m_vxDefault;
	this->m_vy = this->m_vyDefault;
	this->m_left = false;
	this->m_angle = 0;
}

void CWeapon::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	if (this->effect != NULL){
		this->effect->Update(deltaTime);
		if (!this->effect->IsAlive()){
			delete this->effect;
			this->effect = NULL;
		}
	}

	if (this->item != NULL){
		this->item->Update(deltaTime);
	}
}

void CWeapon::Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision)
{

}

void CWeapon::OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision)
{
#pragma region XU_LY_VA_CHAM
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	//Sắp va chạm > 0 và < 1
	//Hai Box Giao Nhau (Đã va chạm rồi) = 2 và moveX, moveY (độ lún)
	timeCollision = CCollision::GetInstance()->Collision(this, CContra::GetInstance(), normalX, normalY, moveX, moveY, deltaTime);
	if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2.0f)
	{
		//trên - xuống normalY = 1
		//Trái phải normalX = -1
		// ==0 ko va chạm theo Y, X	
		if (this->effect == NULL){
			this->effect = new CExplosionEffect(this->GetPos());
		}

		if (this->item == NULL){
			this->item = new CBulletItem(this->GetPos());
		}
	}

#pragma endregion 
}

void CWeapon::MoveUpdate(float deltaTime)
{
	this->m_angle += 4.0 * deltaTime;
	//this->m_vx += this->m_a  * deltaTime;
	//this->m_vy += this->m_a * deltaTime * sin(this->m_angle);
	this->m_pos.x += this->m_vx * deltaTime;
	this->m_pos.y += 5.0f * sin(this->m_angle);
}
RECT* CWeapon::GetBound()
{
	return nullptr;
}

RECT* CWeapon::GetRectRS()
{
	RECT* rs = new RECT();
	rs->left = 0;
	rs->right = this->m_width;
	rs->top = 0;
	rs->bottom = this->m_height;
	return rs;
}

Box CWeapon::GetBox()
{
	return Box(this->m_pos.x, this->m_pos.y, this->m_width, this->m_height, this->m_vx, this->m_vy);
}

CWeapon::~CWeapon()
{

}