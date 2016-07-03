/*
CreatorEngine
Class CrConfig
Payne
*/

#ifndef _CREATOR_CONFIG_H
#define _CREATOR_CONFIG_H

#include <string>
#include "CrDefine.h"
#include <CrSingleton.h>

class CrConfig : public CrSingleton<CrConfig>
{
public:
	CrConfig();
	~CrConfig();

public:
	bool Init();

private:
	

};

#endif