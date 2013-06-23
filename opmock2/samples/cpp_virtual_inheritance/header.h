#ifndef HEADER_H_
#define HEADER_H_

class Father
{
	public:
	virtual int doSomething() = 0;
	virtual ~Father() = 0;
	//virtual ~Father();
};

class Son : public Father
{
	public:
	virtual int doSomething();
};

#endif
