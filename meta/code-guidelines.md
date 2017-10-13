# Code Guidelines

## General
GAMMA E., HELM R., JOHNSON R., VLISSIDES J. M.: Design Patterns: *Elements of Reusable Object-oriented Software*, 1st Edition, Addison-Wesley Longman Publishing Co., 1995.

GREGORY J.: *Game Engine Architecture*, 2nd Edition, A K Peters/CRC Press, 2014.

MEYERS S.: *Effective C++, 3th Edition*, Addison-Wesley Professional, 2005.

MEYERS S.: *Effective Modern C++*, 1st Edition, O'Reilly Media, 2004.

## Specific

### Built-in types
Prefer the defined types (`memory\types.hpp`) and `size_t` over non-typedefed built-in types.

### const
Always use `const` (member method, method return argument, method input arguments, local variables) if applicable.
Always use `const` for return by value of non-built-in types to avoid assignment (and its side effects).

### Explicit constructors
Prefer making **all** (non-default, non-copy, non-move) constructors `explicit` (independent of the number of arguments).

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

### Prefixes
* Use the prefix `g_` for global variables (C++ and HLSL).
* Use the prefix `m_` for member variables (C++ only).
* Use the prefix `s_` for class member variables.

### `new`, `new[]`, `delete`, `delete[]`
* Do not use `new`, `new[]`, `delete`, `delete[]`.
* Use `MakeUnique` for assigning to `UniquePtr`.
* Use `MakeShared` for assigning to `SharedPtr` in case the data does not require custom allocaters.
* Use `MakeAllocatedShared` for assigning to `SharedPtr` in case the data requires custom allocaters (i.e. inherits `AlignedData`).

### Smart pointers
* Use `SharedPtr`, `UniquePtr` and `ComPtr` (`memory\memory.hpp`) to express ownership.
* Use `WeakPtr` (for `SharedPtr`), raw pointer (for `UniquePtr` and `ComPtr`) to express usage without ownership.

### `static_cast`
Always use `static_cast` for type conversion between built-in types.
