#pragma once

class iTank
{
public:
	// If this is a virtual interface, 
	// make sure that you add a virtual destructor
	virtual ~iTank() {}

	// Pure vitual method 
	// "= 0" mean there is no method
	virtual void Attack(/*another tank*/) = 0;
};
