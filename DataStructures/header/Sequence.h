#ifndef CPPLIB_DATASTRUCTURES_SEQUENCE_H
#define CPPLIB_DATASTRUCTURES_SEQUENCE_H

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/DataStructures/Container.h>
#else
#include "Container.h"
#endif

namespace DataStructures
{
	template<class Type>
	class Sequence : public Container<Type>
	{
	public:
		//busca e verificação
		virtual size_t findNext(Type value, size_t idx) const = 0;
		virtual inline size_t indexOf(Type value) const { return findNext(value,0); }
		virtual inline bool contains(Type value) const { return ~indexOf(value); }
		virtual inline bool isValidIndex(size_t idx) const { return (idx != ~0 && idx < this->getSize()); }
		
		//acesso e manipulação
		virtual Type& operator[](size_t index) const = 0;
		
		virtual inline Type get(size_t index) const { return *this->at(index); }
		virtual inline void set(Type value, size_t index){ *this->at(index) = value; }
		virtual void insert(Type value, size_t index) = 0;
		virtual Type erase(size_t index) = 0;
		
		virtual void swap(size_t index1, size_t index2)
		{
			Type value = this->get(index1);
			this->set(this->get(index2), index1);
			this->set(value, index2);
		}

		virtual void reverse()
		{
			size_t size = this->getSize();
			for(size_t i=0; i < (size-1)/2; i++)
				this->swap(i, size-i-1);
		}
		
		virtual void clear() = 0;
		
		//virtual void replace(Type v_old, Type v_new) = 0;
		//virtual void remove(Type value) = 0;
		//virtual void splice() = 0;
		//virtual void count() = 0;
		//virtual void sort() = 0;
		//virtual void shuffle() = 0;
	};
}
#endif
