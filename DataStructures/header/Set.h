#ifndef CPPLIB_DATASTRUCTURES_SET_H
#define CPPLIB_DATASTRUCTURES_SET_H

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/DataStructures/Vector.h>
#include <CppLib/DataStructures/List.h>
#else
#include "Vector.h"
#include "List.h"
#endif

namespace DataStructures
{
	template<typename Type, template<typename> class TypeC = List, 
				isBaseOf<Sequence<Type>,TypeC<Type>>* = nullptr>
	class Set : protected TypeC<Type>
	{
	public:
		//construtor e destrutor
		Set() : TypeC<Type>(){}
		
		Set(size_t init_cap) : TypeC<Type>(init_cap){}
		
		template<template<typename> class Tc>
		Set(const Set<Type,Tc>& s) : Set(s.getSize())
		{
			for(int i=0; i < s.getSize(); i++)
				TypeC<Type>::pushBack(s.get(i));
		}
		
		Set(const TypeC<Type>& s) : Set(s.getSize())
		{
			for(int i=0; i < s.getSize(); i++)
				this->add(s.get(i));
		}
		
		template<template<typename> class Tc>
		Set<Type,TypeC>& operator=(Set<Type,Tc> s)
		{
			this->clear();
			for(int i=0; i < s.getSize(); i++)
				TypeC<Type>::pushBack(s.get(i));
			return (*this);
		}
		
		Set<Type,TypeC>& operator=(const TypeC<Type>& s)
		{
			this->clear();
			for(int i=0; i < s.getSize(); i++)
				this->add(s.get(i));
			return (*this);
		}
		
		//~Set(){ this->~TypeC<Type>(); }
		
		//busca e verificação
		inline bool isAllocated() const { return TypeC<Type>::isAllocated(); }
		inline bool isEmpty() const { return TypeC<Type>::isEmpty(); }
		inline size_t getSize() const { return TypeC<Type>::getSize(); }
		inline size_t indexOf(Type value) const { return TypeC<Type>::indexOf(value); }
		inline bool contains(Type value) const { return TypeC<Type>::contains(value); }
		
		template<typename T=Type>
		decltype(auto) operator==(Set<T>& s)
		{
			size_t size = this->getSize();
			if(size != s.getSize())
				return false;
			for(size_t i=0; i<size; i++)
				if(!s.contains(this->get(i)))
					return false;
			return true;
		}
		
		template<typename T=Type>
		decltype(auto) operator!=(Set<T>& s)
		{ return !(this->operator==(s)); }
		
		//acesso e manipulação
		inline Type get(size_t index) const { return TypeC<Type>::get(index); }
		
		void set(Type value, size_t index)
		{
			size_t idx = this->indexOf(value);
			if(!TypeC<Type>::isValidIndex(idx))
				TypeC<Type>::insert(value, index);
			else if(index != idx)
				TypeC<Type>::swap(index, idx);
		}
		
		void add(Type value)
		{
			if(!this->contains(value))
				TypeC<Type>::pushBack(value);
		}
		
		void remove(Type value)
		{
			size_t idx = TypeC<Type>::indexOf(value);
			if(TypeC<Type>::isValidIndex(idx))
				TypeC<Type>::erase(idx);
		}
		
		inline void clear(){ TypeC<Type>::clear(); }
		
		//operações de conjunto
		template<typename T, template<typename> class Tc1, template<typename> class Tc2>
		friend Set<T> operator+(Set<T,Tc1> s1, Set<T,Tc2> s2);
		
		template<typename T, template<typename> class Tc1, template<typename> class Tc2>
		friend Set<T> operator-(Set<T,Tc1> s1, Set<T,Tc2> s2);
		
		template<typename T, template<typename> class Tc1, template<typename> class Tc2>
		friend Set<T> operator^(Set<T,Tc1> s1, Set<T,Tc2> s2);
		
		template<template<typename> class Tc>
		void unionWith(Set<Type,Tc> s)
		{
			for(size_t i=0; i < s.getSize(); i++)
				this->add(s.get(i));
		}
		template<template<typename> class Tc>
		void diffWith(Set<Type,Tc> s)
		{
			for(size_t i=0; i < s.getSize(); i++)
				this->remove(s.get(i));
		}
		template<template<typename> class Tc>
		void intersecWith(Set<Type,Tc> s)
		{
			for(size_t i=0; i < this->getSize(); i++)
				if(!s.contains(this->get(i)))
				{
					TypeC<Type>::erase(i);
					i--;
				}
		}
		
		//conversão para texto
		inline std::string strFormat(char c='{') const { return TypeC<Type>::strFormat(c); }
		inline void print(){ std::cout << TypeC<Type>::strFormat('{') << '\n'; }
		operator std::string() const { return TypeC<Type>::strFormat('{'); }
		
		template<class T>
		friend std::ostream& operator<<(std::ostream& ost, Set<T>& c);
	};
	
	template<typename T, template<typename> class Tc1, template<typename> class Tc2>
	Set<T> operator+(Set<T,Tc1> s1, Set<T,Tc2> s2)
	{
		size_t l1 = s1.getSize();
		size_t l2 = s2.getSize();
		Set<T> s = Set<T>(l1+l2);
		
		for(size_t i=0; i < l1; i++)
			s.add(s1.get(i));
		for(size_t i=0; i < l2; i++)
			s.add(s2.get(i));
		return s;
	}
	
	template<typename T, template<typename> class Tc1, template<typename> class Tc2>
	Set<T> operator-(Set<T,Tc1> s1, Set<T,Tc2> s2)
	{
		size_t l1 = s1.getSize();
		Set<T> s = Set<T>(l1);
		
		for(size_t i=0; i < l1; i++)
			if(!s2.contains(s1.get(i)))
				s.add(s1.get(i));
		return s;
	}
	
	template<typename T, template<typename> class Tc1, template<typename> class Tc2>
	Set<T> operator^(Set<T,Tc1> s1, Set<T,Tc2> s2)
	{
		size_t l1 = s1.getSize();
		Set<T> s = Set<T>(l1);
		
		for(size_t i=0; i < l1; i++)
			if(s2.contains(s1.get(i)))
				s.add(s1.get(i));
		return s;
		
		
	}

	template<typename Type>
	std::ostream& operator<<(std::ostream& ost, Set<Type>& s)
	{
		ost << s.strFormat();
		return ost;
	}
}
#endif
