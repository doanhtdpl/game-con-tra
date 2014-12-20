#ifndef __CCONTRA_H__
#define __CCONTRA_H__
#pragma once
#include "CDynamicObject.h"
#include "CAnimation.h"
#include "CBullet.h"
#include "CSingleton.h"
#include "CBulletM.h"
#include "CBulletF.h"
#include "CBulletL.h"
#include "CBulletM.h"
#include "CBulletN.h"
#include "CBulletS.h"


enum ON_GROUND
{
	IS_STANDING = 10,
	IS_JOGGING = 11,
	IS_JUMPING = 12,
	IS_LYING = 13,
	IS_FALL = 14,
	IS_SHOOTING_UP = 15,
	IS_SHOOTING_NORMAL = 16,
	IS_SHOOTING_DIAGONAL_UP = 17,
	IS_SHOOTING_DIAGONAL_DOWN = 18,
	IS_DIE = 19
};

enum UNDER_WATER
{
	IS_STANDING_UNDER_WATER = 20,
	IS_LYING_UNDER_WATER = 21,
	IS_JOGGING_UNDER_WATER = 22,
	IS_DIE_UNDER_WATER = 23,
	IS_SHOOTING_UNDER_WATER_UP = 24,
	IS_SHOOTING_UNDER_WATER_NORMAL = 25,
	IS_SHOOTING_UNDER_WATER_DIAGONAL_UP = 26
};

//enum BULLET_TYPE{
//	BULLET_N = 0,
//	BULLET_M = 1,
//	BULLET_F = 2,
//	BULLET_L = 3,
//	BULLET_S = 4
//};

//enum SHOOT
//{
//	IS_NORMAL,
//	IS_UP,
//	IS_DOWN,
//	IS_DIAGONAL_UP,
//	IS_DIAGONAL_DOWN
//};

class CContra : public CDynamicObject, public  CAnimation, public CSingleton<CContra>
{
	friend class CSingleton<CContra>;
public:
	CContra(void);
	CContra(const std::vector<int>& info);
	~CContra();
	std::string ClassName(){ return __CLASS_NAME__(CContra);};
	virtual void MoveUpdate(float deltaTime);
	//void ChangeFrame(float deltaTime);
	void InputUpdate(float deltaTime);
	int GetShootState(){return m_stateShoot;};
	int GetStateCurrent(){return m_stateCurrent;};
	bool GetLocation(){return m_isUnderWater;}; //Neu con tra o duoi nuoc tra ve  true, nguoc lai tra ve false
	void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	void BulletUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	void SetVelocityY(float vy){this->m_vy = vy;};
	RECT* GetBound();
	Box GetBox();
	RECT* GetRectRS();
protected:
	void SetFrame(float deltaTime);
	//int m_startFrame; //Frame bat dau
	//int m_endFrame; //Frame ket thuc
	bool m_isUnderWater; // Dang o duoi nuoc
	bool m_isShoot; // Duoc phep ban
	bool m_isShooting; //Dang ban
	int m_stateCurrent; // Trang thai hien tai
	int m_stateShoot; // Huong ban
	int m_keyDown; //Luu phim vua duoc nhan
	int m_keyUp; //Luu phim vua duoc tha
	//Bien quan ly vien dan hien tai
	float m_waitForShoot; //Quan ly thoi gian cho ban
	float m_waitChangeSprite; //Quan ly thoi gia cho chuyen sprite
	//
	//Tam thoi dung mot vector de giu cac vien dan

	int m_typeBullet; 
	int m_bulletCount; //So luong vien dan da ban ra
//Nhung tham so dung de test
public:
	float m_currentFall; // Do cao hien tai
	float m_currentJump;//
public:
	void SetTypeBullet(int _typeBullet){this->m_typeBullet = _typeBullet;};
	void SetPosY(float posY){this->m_pos.y = posY;};
	float GetPosY(){return this->m_pos.y;};

};

#endif // !__CCONTRA_H__
