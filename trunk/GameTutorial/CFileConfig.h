#ifndef __CFILE_CONFIG_H__
#define __CFILE_CONFIG_H__

#include "CSingleton.h"
#include "CGlobal.h"


class CFileConfig : public CSingleton<CFileConfig>
{
	friend class CSingleton<CFileConfig>;
public:
	~CFileConfig();
	float Sin(float angle);
	float Cos(float angle);
	float Tan(float angle);
	float Cot(float angle);
protected:
	CFileConfig();
private:
	float 
};

#endif // !__CFILE_CONFIG_H__
