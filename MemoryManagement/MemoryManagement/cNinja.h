#pragma once

#include <string>

class cNinja
{
public:
	cNinja();
	~cNinja();
//	void* operator new(size_t size);
	std::string name;
	float age;
	double health;
	void Attack(void);
};
