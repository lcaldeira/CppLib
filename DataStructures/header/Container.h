#ifndef CPPLIB_DATASTRUCTURES_CONTAINER_H
#define CPPLIB_DATASTRUCTURES_CONTAINER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdint>
#include <initializer_list>

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/Utilities/TypeTraits.h>
#else
#include "../../Utilities/header/TypeTraits.h"
#endif

namespace DataStructures
{
	using namespace TypeTraits;
	
	template<typename Type>
	using init_list = std::initializer_list<Type>;
	
	template<typename Type>
	class Container
	{
	protected:
		virtual Type* at(size_t index) const = 0;
	public:
		//construtor and destrutor that should be implemented
		/*
			Class() {}	// default constructor
			Class(Args ...) {}	// parameterized constructor
			Class(const Class& C) {} // copy constructor
			Class& operator=(const Class& C) {} // copy assignment
			friend Class& operator&=(Class& C1, Class& C2) {} // reference assignment
			virtual ~Class() {} // destructor
		*/
		
		//busca e verificação
		virtual size_t getSize() const = 0;
		virtual bool isEmpty() const { return !this->getSize(); }
		virtual bool isAllocated() const = 0;
		virtual bool contains(Type value) const = 0;
		
		template<typename T=Type>
		decltype(auto) operator==(Container<T>& c)
		{
			size_t size = this->getSize();
			if(size != c.getSize())
				return false;
			for(size_t i=0; i<size; i++)
				if(*this->at(i) != *c.at(i))
					return false;
			return true;
		}
		
		template<typename T=Type>
		inline decltype(auto) operator!=(Container<T>& c)
		{
			return !(this->operator==(c));
		}
		
		/*auto operator==(Container<T>& c) -> decltype(*this == 
		{
			//static_assert(std::is_fundamental<Type>::value, "Fundamental type required.");
			size_t size = this->getSize();
			if(size != c.getSize())
				return false;
			for(size_t i=0; i<size; i++)
				if(*this->at(i) != *c.at(i))
					return false;
			return true;
		}
		
		bool operator!=(Container<Type>& c){ return !(this->operator==(c)); }*/
		
		//conversão para texto		
		virtual inline std::string strFormat(char c=' ') const { return "{-}"; }
		virtual inline void print() const { std::cout << (this->strFormat()) << '\n'; }
		virtual inline operator std::string() const { return this->strFormat(); }
		
		template<class T>
		friend std::ostream& operator<<(std::ostream& ost, Container<T>& c);
	};

	template<typename Type, template<typename> class TypeC, 
				isBaseOf<Container<Type>,TypeC<Type>>* = nullptr>
	std::ostream& operator<<(std::ostream& ost, TypeC<Type>& c)
	{
		ost << c.strFormat();
		return ost;
	}
}
#endif
