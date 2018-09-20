# Code Guidelines

## Table of contents
* [General](#SS-General)
* [Specific](#SS-Specific)
* [Style](#SS-Style)
* [Tools](#SS-Tools)

## <a name="SS-General"></a>General

GAMMA E., HELM R., JOHNSON R., VLISSIDES J. M.: Design Patterns: *Elements of Reusable Object-oriented Software*, 1st Edition, Addison-Wesley Longman Publishing Co., 1995.

GREGORY J.: *Game Engine Architecture*, 2nd Edition, A K Peters/CRC Press, 2014.

KARPOV A.: [*The Ultimate Question of Programming, Refactoring, and Everything*](https://www.viva64.com/en/b/0391/), 2016.

KAYARI: [*C++ Antipatterns*](http://kayari.org/cxx/antipatterns.html), s.d.

MEYERS S.: *Effective C++, 3th Edition*, Addison-Wesley Professional, 2005.

MEYERS S.: *Effective Modern C++*, 1st Edition, O'Reilly Media, 2004.

STROUSTRUP B., SUTTER H.: [*C++ Core Guidelines*](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md), 2018.

## <a name="SS-Specific"></a>Specific

### Built-in types
Prefer the defined types (`utils\type\types.hpp`) and `std::size_t` over non-typedefed built-in types.

### Constness
* Always use `const` (member method, method return argument, method input arguments, local variables) if applicable.
* Always use `const` for return by value of non-built-in types to avoid assignment (and its side effects). C++17's *Guaranteed Copy Elision* will avoid invoking the copy constructor or copy assignment operator.

### Constructor and destructor definitions
Put all constructors and destructors of non-template base and child classes in the `.cpp` file.

### Excplicit constructors
Prefer `explicit` (non-default, non-copy, non-move) constructors (independent of the number of arguments).

Prefer inheritance with `explicit` child constructors over typedefs to force explicit type conversion between aliases.

### Implicitly defined member methods
Do not use implicitly defined (i.e. compiler generated) member methods. Always declare and define (with `= default`/`= delete` if possible) the following member methods:
* Default constructor (if and only if this is the only constructor in the `class`/`struct`)
* Destructor
* Copy and move constructor
* Copy and move assignment operator

Note that Move Constructors make sense in nearly all situations. So prefer `= default` over `= delete`.

Give deleted member methods the access modifier you would (*hypothetically*) give them if they would not be deleted:
* Copy and move assignment operators will be `public` in concrete and abstract classes *for most cases*.
* Copy and move constructors will be `public` in concrete classes *for most cases*.
* Copy and move constructors will be `protected` in abstract classes *for most cases*.
* Copy and move constructors will be `private` in concrete `final` classes that can only be instantiated by `friends` *for most cases*.

In all cases, an announcement is made to the appropriate users of a class instead of all users of a class.

### Member initializer lists
Enumerate all member variables in the initializer list of constructors in order.

### `new`, `new[]`, `delete`, `delete[]`
* Do not use `new`, `new[]`, `delete`, `delete[]`.
* Use `MakeUnique` for assigning to `UniquePtr`.
* Use `MakeShared` for assigning to `SharedPtr` in case the data does not require custom allocaters.
* Use `MakeAllocatedShared` for assigning to `SharedPtr` in case the data requires custom allocaters and/or deallocation needs to happen as early as possible.

### Smart pointers
* Use `SharedPtr`, `UniquePtr` and `ComPtr` (`memory\memory.hpp`) to express ownership.
* Use `WeakPtr` (for `SharedPtr`), raw pointer (for `UniquePtr` and `ComPtr`) to express usage without ownership.

### Type casting
Always use `static_cast` for type conversion between built-in types (as opposed to C style casts).

### Zero initialization
Do not use `ZeroMemory`, use `= {}` instead. (Though, `SecureZeroMemory` may be used).

## <a name="SS-Style"></a>Style

### File extensions
* Use `.hpp` for C++ header files.
* Use `.tpp` for C++ header files containing template definitions.
* Use `.cpp` for C++ source files.
* Use `.hlsl` for HLSL shader files.
* Use `.hlsli` for HLSL non-shader files.

### Line width
Lines have a maximum width of 80 characters.

### Name conventions
* Use lowercase names for namespaces.
* Use lowercase names with `_` delimiters for variables.
* Use [upper camal case a.k.a. Pascal case](https://en.wikipedia.org/wiki/Camel_case) names for classes, ((class) member) methods and (class) types.
* Exceptions are allowed for STD/STL compliance.

### Trailing spaces
Remove trailing spaces (Visual Studio regex: `[^\S\r\n]+(?=\r?$)`)

### Variable prefixes
* Use the prefix `g_` for global variables (C++ and HLSL).
* Use the prefix `m_` for member variables (C++ and HLSL).
* Use the prefix `s_` for class and method member variables (C++ and HLSL).

### Yoda conditions
Use [Yoda conditions](https://en.wikipedia.org/wiki/Yoda_conditions) to avoid accidental variable assignments within conditionals.

## <a name="SS-Tools"></a>Tools

### CPU Debuggers/Profilers
* [Visual Studio 2017](https://visualstudio.microsoft.com/)

### GPU Debuggers/Profilers
* [NVIDIA Nsight Graphics](https://developer.nvidia.com/nsight-graphics)
* [NVIDIA Nsight Visual Studio Edition](https://developer.nvidia.com/nsight-visual-studio-edition)
* [RenderDoc](https://renderdoc.org/)

### Static Code Analyzers
* [PVS-Studio Analyzer](https://www.viva64.com/en/pvs-studio/) (stand-alone or Visual Studio plugin)
* [Visual Studio 2017](https://visualstudio.microsoft.com/)
