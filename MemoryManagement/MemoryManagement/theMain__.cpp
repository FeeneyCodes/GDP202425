
#include "cNinja.h"
#include <iostream>

// Also never do this!
void* operator new(size_t size)
{
//	cout << "New operator overloading " << endl;
	void* p = malloc(size);
	return p;
}

int main__()
{
	cNinja* a = new cNinja();

	// NEVER do this!!
//	cNinja* b = (cNinja*)malloc(sizeof(cNinja));

//	b->name = "Fred";
//	b->Attack();
	

	return 0;
}
