#ifndef HEADER_H_
#define HEADER_H_

// additional types in differents namespaces or the same namespace
// are defined in this external headers
#include <stdio.h>
#include "inc1.hpp"
#include "inc2.hpp"
#include "inc3.hpp"

namespace space1
{
  class Class1
  {
  public:
	int functionWithStruct(myfloat par, spacejunk::Junk par2, 
			       spacejunk2::Junk2 par3, spacejunk3::Junk3 par4, myint par5);
  };
}

#endif
