# CppLib

Libraries written in C++ for academic purpose. 

## Organization

Each library has its own development branch and a respective `define` macro name.

1. DataStructures: branch `dev-ds`, with headers identified by `CPPLIB_DATASTRUCTURES_{filename}_H`

## Global Definitions

There are some defines used globally across the library files, as control flags to alter the compilated source code. All of them have names like `CPPLIB_{explanation}_F` (notice the *F* suffix), and they are detailed below:

- `CPPLIB_ABS_INC_PATH_F`: controls which type of file path the headers use at include directives. Without this flag, the includes point to the installed library as `<CppLib/{module}/{file}.h>` and are more readable. With this flag, includes are like `"../../{module}/header/{file}.h"`. Only use this flag when the library are not installed, or when using another version instead of the installed one.

- `CPPLIB_DEBUG_MODE_F` (not implemented yet): when defined, enables some output messages inside the class methods.

- `CPPLIB_NO_CHECKS_F` (not implemented yet): remove the class verifications, like _is this pointer valid?_ or _is the container allocated?_. Normally, these checks avoids incorrect behaviors, as invalid data access, but can be a little redundant. Just use this flag if all validations are already handled outside the class.

## Code Tips

As I discovery new features and good practices of C++ programming language, I will write them down here to anyone who want to learn C++, or is just trying to understand my codes. If something that is write here is incorrect, feel free to contact me and I will update the notes below :)

- **inline functions**: the `inline` specifier tells the compiler to expand the body of the respective function whenever it is called, if the cost-benefit were worthwhile. The reason to declare a function as `inline` is to reduce the overhead of function calls, as the content of an inline function is copied in the place of the function call.

- **const member functions**: the `const` specifier in a member function means that it cannot modificate the non-static data members of call any non-const member function. In practice, the `const` specifier create a read-only member function, and allow some compiler optimizations.
