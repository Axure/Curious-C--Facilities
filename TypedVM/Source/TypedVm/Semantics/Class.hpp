//
// Created by lluvi on 2016/3/17.
//

#ifndef TYPEDVM_CLASS_HPP
#define TYPEDVM_CLASS_HPP

#include <deque>

#include "Type.hpp"
namespace TypedVm {
namespace Semantics {
/**
 *
 */
class Class: public Type {
 TYPEDVM_SCOPE_NOTE("Related types", private)
  std::deque<Class> parentClasses_;
};
}
}
#endif //TYPEDVM_CLASS_HPP
