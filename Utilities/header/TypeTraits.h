#ifndef CPPLIB_UTILITIES_TYPETRAITS_H
#define CPPLIB_UTILITIES_TYPETRAITS_H

#include <type_traits>

namespace TypeTraits
{
	template<typename Type>
	using isFundamental = std::enable_if_t<std::is_fundamental<Type>::value>;
	
	template<typename Type>
	using isntFundamental = std::enable_if_t<!std::is_fundamental<Type>::value>;
	
	template<class Base, class Derived>
	using isBaseOf = std::enable_if_t<std::is_base_of<Base, Derived>::value>;
	
	template<class TypeA, class TypeB>
	using isConvertible = std::enable_if_t<std::is_convertible<TypeA,TypeB>::value>;
	
	template<class TypeA, class TypeB>
	using isntConvertible = std::enable_if_t<!std::is_convertible<TypeA,TypeB>::value>;
	
	template<class Type>
	using isPrintable = std::enable_if_t<
		std::is_fundamental<Type>::value || 
		std::is_convertible<Type,std::string>::value || 
		std::is_assignable<Type,std::string>::value>;
	
	template<class Type>
	using isntPrintable = std::enable_if_t<
		!std::is_fundamental<Type>::value && 
		!std::is_convertible<Type,std::string>::value && 
		!std::is_assignable<Type,std::string>::value>;
}

#endif
