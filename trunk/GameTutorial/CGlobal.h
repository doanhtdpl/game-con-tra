#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#pragma once
#include <vector>
#include <string>
#include "d3d9.h"
#include "d3dx9.h"
#include <iostream>
#include <Windows.h>

using namespace std;

//extern HWND e_hWND = nullptr;
//extern HINSTANCE e_hInstance = nullptr;

#define __FRAME_RATE 60
#define __SCREEN_WIDTH  800
#define __SCREEN_HEIGHT 600
#define __CLASS_NAME "Contra"

typedef unsigned long long __UINT64;
typedef long long		   __INT64;
typedef int 			   __INT32;
typedef unsigned int	   __UINT32;
typedef signed short	   __INT16;
typedef unsigned short	   __UINT16;
typedef signed char		   __INT8;
typedef unsigned char	   __UINT8;

#endif // !__CGLOBAL_H__
