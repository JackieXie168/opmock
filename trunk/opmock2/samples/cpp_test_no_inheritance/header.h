#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>

#ifdef OPMOCK
#define PRIVATE public
#else
#define PRIVATE private
#endif

namespace space1
{
	class Class1
	{
	public:
		int func1(int i, int j);
		int func2(char *one, char*two);
		char func3(char *one_array[], int another);
		void funcVariadic(int a, int b, ...);
	};
	
	namespace space2
	{
		class Class2
		{
		public:
			void func3();
			char *func4(double val);
		};
	}
}

namespace space3
{
  class Class3 : public space1::space2::Class2, public space1::Class1
    {
    public:
      int attribute1;
      int func5(double machin, int bidule);
    PRIVATE:
      int shouldBePrivate(char j);
      int multiply(int a, int b);
    };
}

class ClassNoNamespace
{
public:
	void bla(int j);
	virtual int imVirtual(const char * param);
private:
	void thisIsReallyPrivate(int i);
};

#endif
