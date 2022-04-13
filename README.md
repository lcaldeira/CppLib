# CppLib

Libraries written in C++ for academic purpose. 

## Organization

Each library has its own development branch.

1. DataStructures: branch `dev-ds`

## Code Tips

As I discovery new features and good practices of C++ programming language, I will write them down here to anyone who want to learn C++, or is just trying to understand my codes. If something that is write here is incorrect, feel free to contact me and I will update the notes below :)

- **inline functions**: the `inline` specifier tells the compiler to expand the body of the respective function whenever it is called, if the cost-benefit were worthwhile. The reason to declare a function as `inline` is to reduce the overhead of function calls, as the content of an inline function is copied in the place of the function call.

- **const member functions**: the `const` specifier in a member function means that it cannot modificate the non-static data members of call any non-const member function. In practice, the `const` specifier create a read-only member function, and allow some compiler optimizations.
