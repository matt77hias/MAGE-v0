
### Explicit constructors
Make **all** (non-default, non-copy, non-move) constructors `explicit` (independent of the number of arguments).  

### Implicitly defined member methods
Do not use implicitly defined (i.e. compiler generated) member methods. Always declare and define (with `= default`/`= delete` if possible) the following member methods:
* Default Constructor (if and only if this is the only constructor in the `class`/`struct`)
* Destructor
* Copy Constructor
* Move Constructor
* Copy Assignment Operator
* Move Assignment Operator

Note that Move Constructors make sense in nearly all situations (except in case of reference member variables). So prefer `= default` over `= delete`.

### Member initializer lists
Enumerate all member variables in the initializer list of constructors in order.

### Smart pointers
Use `SharedPtr`, `UniquePtr` and `ComPtr` (`memory\memory.hpp`) to express ownership. Use `WeakPtr` (for `SharedPtr`), raw pointer (for `UniquePtr` and `ComPtr`) to express usage without ownership.
