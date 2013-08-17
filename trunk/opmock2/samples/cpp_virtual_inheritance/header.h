#ifndef HEADER_H_
#define HEADER_H_

class Father
{
	public:
	virtual int doSomething() = 0;

    // I will generate an implementation/mock for this pure virtual constructor
    // because otherwise I can't link. When mocking, I must use the mock
    // for the base abstract class as I don't do vtable dispatching in opmock.
	virtual ~Father() = 0;
	//virtual ~Father();
};

class Son : public Father
{
	public:
	virtual int doSomething();
};

#endif
