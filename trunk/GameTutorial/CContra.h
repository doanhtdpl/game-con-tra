#ifndef __CCONTRA_H__
#define __CCONTRA_H__
#pragma once
#include "CDynamicObject.h"
#include "CAnimation.h"
#include "CBullet.h"
#include "CSingleton.h"

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
	IS_DIE_UNDER_WATER = 23
};

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
	CContra();
	~CContra();
	std::string ClassName(){ return __CLASS_NAME__(CContra);};
	virtual void MoveUpdate(float deltaTime);
	void ChangeFrame(float deltaTime);
	void InputUpdate(float deltaTime);
	int GetShootState(){return m_stateShoot;};
	int GetStateCurrent(){return m_stateCurrent;};
	bool GetLocation(){return m_isUnderWater;}; //Neu con tra o duoi nuoc tra ve  true, nguoc lai tra ve false
	void BulletUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	RECT GetRect();
	RECT* GetRectRS();
protected:
	void SetFrame();
	int m_startFrame; //Frame bat dau
	int m_endFrame; //Frame ket thuc
	bool m_isUnderWater; // Dang o duoi nuoc
	bool m_isShoot; // Duoc phep ban
	int m_stateCurrent; // Trang thai hien tai
	int m_stateShoot; // Huong ban
	int m_keyDown; //Luu phim vua duoc nhan
	int m_keyUp; //Luu phim vua duoc tha
	//Bien quan ly vien dan hien tai
	//
	//Tam thoi dung mot vector de giu cac vien dan
public:
	std::vector<CBullet*> m_listBullet;
//Nhung tham so dung de test
protected:
	float m_currentFall; // Do cao hien tai
	float m_currentJump;//

};

#endif // !__CCONTRA_H__
