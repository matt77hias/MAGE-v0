# Code Guidelines

## General
* Erich Gamma, Richard Helm, Ralph Johnson & John M. Vlissides: Design Patterns *Elements of Reusable Object-Oriented Software*
* Scott Meyers: Effective C++ (3th edition)
* Scott Meyers: Effective Modern C++

## Specific

### const
Always use `const` (member method, method return argument, method input arguments, local variables) if applicable.
Always use `const` for return by value of non-built-in types to avoid assignment (and its side effects).

### Explicit constructors
Make **all** (non-default, non-copy, non-move) constructors `explicit` (independent of the number of arguments).

Prefer inheritance with explicit constructors over typedefs to force explicit type conversion between aliases.

### Implicitly defined member methods
Do not use implicitly defined (i.e. compiler generated) member methods. Always declare and define (with `= default`/`= delete` if possible) the following member methods:
* Default Constructor (if and only if this is the only constructor in the `class`/`struct`)
* Destructor
* Copy Constructor
* Move Constructor
* Copy Assignment Operator
* Move Assignment Operator

Note that Move Constructors make sense in nearly all situations. So prefer `= default` over `= delete`.

### Member initializer lists
Enumerate all member variables in the initializer list of constructors in order.

### Smart pointers
Use `SharedPtr`, `UniquePtr` and `ComPtr` (`memory\memory.hpp`) to express ownership.
Use `WeakPtr` (for `SharedPtr`), raw pointer (for `UniquePtr` and `ComPtr`) to express usage without ownership.

### `static_cast`
Always use `static_cast` for type conversion between built-in types.

### `<stdint.h>`
Prefer `(u)intX_t` and `size_t` over non-typedefed built-in types.
