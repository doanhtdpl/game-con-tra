#include "CFileConfig.h"

CFileConfig::CFileConfig()
{

}

float CFileConfig::Sin(float angle){
	float i = (float)PI;
	int r = (angle / i)*180;
	switch (r)
	{
	case 0:
		return 0;
	case 30:
		return 1 / 2;
	case 45:
		return sqrt(2) / 2;
	case 60:
		return sqrt(3) / 2;
	case 90:
		return sqrt(4) / 2;
	case 120:
		return sqrt(3) / 2;
	case 135:
		return sqrt(2) / 2;
	case 150:
		return 1 / 2;
	case 180:
		return 0;
	case 210:
		return -1 / 2;
	case 225:
		return -sqrt(2) / 2;
	case 240:
		return -sqrt(3) / 2;
	case 270:
		return -1;
	case 300:
		return -sqrt(3) / 2;
	case 315:
		return -sqrt(2) / 2;
	case 330:
		return -1 / 2;
	case 360:
		return 0;
	}
}

float CFileConfig::Cos(float angle){
	return this->Sin((PI / 2) - angle);
}

float CFileConfig::Tan(float angle){
	return this->Sin(angle) / this->Cos(angle);
}

float CFileConfig::Cot(float angle){
	return this->Tan((PI / 2) - angle);
}

CFileConfig::~CFileConfig()
{

}