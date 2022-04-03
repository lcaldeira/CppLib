#ifndef CPPLIB_UTILITIES_MACROS_H
#define CPPLIB_UTILITIES_MACROS_H

// print token as text, serves to get the variable name
#define STRINGIFY(token) 				#token

//concatenate two tokens
#define CONCAT(token1, token2)			token1 ## token2

// identity macro function for use in macro expansions
#define IDENTITY(token)					token

// first expand firsts parameters, then apply last param
#define EXPAND_APPLY(token, func) 		func(token)
#define EXPAND_APPLY2(t1, t2, func) 	func(t1,t2)
#define EXPAND_ONLY(token)				EXPAND_APPLY(token, IDENTITY)

// shortcut to string conversion
#define TO_STR(token)					EXPAND_APPLY(token, STRINGIFY)
#define QUOTED(token)					TO_STR(token)

// constrói um nome para inclusão dinãmica no formato "#include DYNAMIC_HEADER(A,B)"
#define DYNAMIC_HEADER(path,file)	 	TO_STR(path/file.h)

// useful information when debuging
#define LINENUM()					__LINE__
#define FILENAME()					__FILE__
#define TIMESTAMP()					(__DATE__ " - " __TIME__)

// logging functions with file name and line number
#define DEBUG_MSG(msg)				("\"" __FILE__ "\" at line " EXPAND_APPLY(__LINE__, STRINGIFY) ": " msg)
#define DEBUG_MSG_SIMPLE(msg)		("At line " EXPAND_APPLY(__LINE__, STRINGIFY) ": " msg)
#define LOG_MSG(msg)				printf("%s\n", DEBUG_MSG(msg))
#define LOG_NOW()					printf("System timestamp: %s\n", TIMESTAMP())

#endif
