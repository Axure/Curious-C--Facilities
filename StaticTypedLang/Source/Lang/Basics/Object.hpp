//
// Created by lluvi on 2016/3/18.
//

#ifndef STATICTYPEDLANG_OBJECT_HPP
#define STATICTYPEDLANG_OBJECT_HPP

#include "./Macros.hpp"
namespace STLang {
namespace Basics {
/**
 * The type of an object handle.
 */
using THandle = int;
/**
 *
 */
class Object {
 STLANG_SCOPE_NOTE("Meta data", protected)
  THandle handle_;
};
}
}


#endif //STATICTYPEDLANG_OBJECT_HPP
