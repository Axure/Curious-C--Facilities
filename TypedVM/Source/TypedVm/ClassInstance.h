//
// Created by lluvi on 2016/3/17.
//

#ifndef TYPEDVM_CLASSINSTANCE_H
#define TYPEDVM_CLASSINSTANCE_H
#include "Semantics/Class.hpp"

namespace TypedVm {
/**
 *
 */
class ClassInstance {
 TYPEDVM_SCOPE_NOTE("Type", private)
  Class &class_;
 TYPEDVM_SCOPE_NOTE("Constructor", public)
  ClassInstance(Class& class__);
};
}

#endif //TYPEDVM_CLASSINSTANCE_H
