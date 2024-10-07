#pragma once
#include <string>

class cAxe
{
public:
	cAxe();
	~cAxe();
	float size;
	std::string type;
	bool bIsBattleAxe;
	void Chop(void);
};