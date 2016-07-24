//
// Created by axurez on 12.03.2016.
//

#ifndef TYPEDVM_TYPEDVM_H
#define TYPEDVM_TYPEDVM_H
#include "Macros.h"
namespace TypedVm {
/**
 * @class TypedVm
 *
 * The class for the TypeScript virtual machine.
 *
 *
 */
class TypedVm {
 TYPEDVM_SCOPE_NOTE("", private)

 TYPEDVM_SCOPE_NOTE("Constructors and destructor", public)
  TypedVm() TYPEDVM_NOEXCEPT;
  ~TypedVm();
};
}

#endif //TYPEDVM_TYPEDVM_H
