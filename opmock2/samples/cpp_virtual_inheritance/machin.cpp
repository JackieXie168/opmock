#include "header.h"
#include <iostream>

int Son::doSomething()
{
	return 777;
}

// base class implementation as it's not pure virtual
// this works, I can compile and run and the father destructor is called.
// but of course if I just mock operations in the current file, I will not get
// a default father destructor implementation.
Father::~Father()
{
	std::cout << "Father destructor" << std::endl;
}

int main()
{
	Son son;
	int res = son.doSomething();
	return 0;
}
