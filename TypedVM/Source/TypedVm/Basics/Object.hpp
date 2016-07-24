//
// Created by lluvi on 2016/3/17.
//

#ifndef TYPEDVM_OBJECT_HPP
#define TYPEDVM_OBJECT_HPP
#include "../Macros.h"
namespace TypedVm {
namespace Basics {
using THandle = int;
class Object {
 TYPEDVM_SCOPE_NOTE("Constructors", public)
  Object();
 TYPEDVM_SCOPE_NOTE("Destructor", public)
  ~Object();
};
}
}

#endif //TYPEDVM_OBJECT_HPP
