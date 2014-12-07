#ifndef __CFILE_CONFIG_H__
#define __CFILE_CONFIG_H__

#include "CGlobal.h"
#include "CSingleton.h"

enum VALUE_OF_ANGLE
{
	SIN = 0,
	COS = 1, 
	TAN = 2,
	COSTAN = 3
};
class CFileConfig : CSingleton<CFileConfig>
{
	friend class CSingleton<CFileConfig>;
private:
	float listCosValue[17];
	float listSinValue[17];
	float* listTanValue;
	float* listCosTagValue;
protected:
	CFileConfig();
	void SetValue();
public:
	float Cos(double angle);
	float Sin(double angle);
	float Tan(double angle);
	float CosTg(double angle);
};

#endif // !__CFILE_CONFIG_H__
