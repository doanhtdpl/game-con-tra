﻿#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#pragma once
#include <vector>
#include <string>
#include "d3d9.h"
#include "d3dx9.h"
#include <iostream>
#include <Windows.h>
#include <hash_map>
#include <sstream>
#include <math.h>

using namespace std;

//extern HWND e_hWND = nullptr;
//extern HINSTANCE e_hInstance = nullptr;

#define __FRAME_RATE 60
#define __SCREEN_WIDTH  640
#define __SCREEN_HEIGHT 480
#define __CLASS_NAME "Contra"
#define __CLASS_NAME__(x) #x

typedef unsigned long long __UINT64;
typedef long long		   __INT64;
typedef int 			   __INT32;
typedef unsigned int	   __UINT32;
typedef signed short	   __INT16;
typedef unsigned short	   __UINT16;
typedef signed char		   __INT8;
typedef unsigned char	   __UINT8;

#define __OBJECT_PATH__ "..\\Resource\\File\\Object\\ObjectPath.csv"
#define __SIMON_PATH__  "..\\Resource\\simon.png"
#define __BULLET_PATH__ "..\\Resource\\Bullet.png"
#define __CONTRA_PATH__ "..\\Resource\\Contra\\Sprite\\contra.PNG"

#define PI atan(1.0)*4
//#define PI 3.141592653589793
//#define PI boost::math::constants::pi<double>()

#endif // !__CGLOBAL_H__

struct Box
{
	Box()
	{
		x = y = 0;
		w = h = 0;
		vx = vy = 0;
	}

	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	Box(D3DXVECTOR2 pos, float _w, float _h, float _vx, float _vy)
	{
		x = pos.x;
		y = pos.y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	Box(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = 0.0f;
		vy = 0.0f;
	}

	// position of top-left corner
	float x, y;

	// dimensions
	float w, h;

	// velocity
	float vx, vy;
};