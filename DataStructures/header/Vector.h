#ifndef CPPLIB_DATASTRUCTURES_VECTOR_H
#define CPPLIB_DATASTRUCTURES_VECTOR_H

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/DataStructures/Sequence.h>
#else
#include "Sequence.h"
#endif

namespace DataStructures
{
	template<class Type>
	class Vector : public Sequence<Type>
	{
	protected:
		Type* data;
		size_t size;
		size_t capacity;
		
		inline Type* at(size_t index) const override { return &(this->data[index]); }
	public:
		//construtor e destrutor
		Vector<Type>()
		{
			data = nullptr;
			size = capacity = 0;
		}
		
		Vector<Type>(size_t init_cap, size_t init_siz=0)
		{
			this->capacity = (init_cap > 0 ? init_cap : 16);
			this->size = (init_siz <= this->capacity ? init_siz : this->capacity);
			this->data = new Type[this->capacity];
		}
		
		Vector<Type>(const Vector<Type>& v) : Vector<Type>(v.getCapacity())
		{
			this->size = v.getSize();
			for(int i=0; i < this->size; i++)
				data[i] = v.get(i);
		}

		virtual ~Vector<Type>()
		{
			if(isAllocated())
			{
				delete[] this->data;
				this->data = nullptr;
			}
		}
		
		Vector<Type>& operator=(const Vector<Type>& v)
		{
			/*this->~Vector<Type>();
			this->size = v.getSize();
			this->capacity = v.getCapacity();
			this->data = new Type[this->capacity];
			
			for(int i=0; i < v.getSize(); i++)
				data[i] = v[i];
			return *this;*/
			
			if(this->capacity < v.getSize() || !isAllocated())
			{
				this->~Vector<Type>();
				this->capacity = v.getCapacity();
				this->data = new Type[this->capacity];
			}
			this->size = v.getSize();
			
			for(int i=0; i < this->size; i++)
				data[i] = v[i];
			return *this;
		}
		
		friend Vector<Type>& operator&=(Vector<Type>& v, Vector<Type>& w)
		{
			if(&v != &w)
			{
				v.~Vector<Type>();
				v.capacity &= w.capacity;
				v.size &= w.size;
				v.data = w.data;
			}
			return v;
		}

		//busca e verificação
		inline bool isAllocated() const override { return this->data != nullptr; }
		inline size_t getSize() const override { return this->size; }
		inline size_t getCapacity() const { return this->capacity; }
		
		size_t findNext(Type value, size_t idx) const override
		{
			for(size_t i=idx; i < this->size; i++)
				if(this->data[i] == value)
					return i;
			for(size_t i=0; i < idx; i++)
				if(this->data[i] == value)
					return i;
			return ~0;
		}
		
		template<typename T=Type>
		decltype(auto) operator==(Vector<T>& v)
		{
			size_t size = this->getSize();
			if(size != v.getSize())
				return false;
			for(size_t i=0; i<size; i++)
				if(this->data[i] != v[i])
					return false;
			return true;
		}
		
		template<typename T=Type>
		decltype(auto) operator!=(Vector<T>& v)
		{
			return !(this->operator==(v));
		}

		//acesso e manipulação
		inline Type& operator[](size_t index) const override { return this->data[index]; }
		
		void insert(Type value, size_t index) override
		{
			if(this->size == this->capacity)
				resize(2 * this->capacity);

			for(size_t i = this->size; i > index; i--)
				this->data[i] = this->data[i-1];

			this->data[index] = value;
			this->size++;
		}

		Type erase(size_t index) override
		{
			Type t = this->data[index];

			if(index < this->size-1)
				for(size_t i=index; i < this->size-1; i++)
					this->data[i] = this->data[i+1];

			this->size--;
			return t;
		}

		inline void pushFront(Type value) { insert(value, 0); }
		inline void pushBack(Type value) { insert(value, this->size); }
		inline Type popFront() { return erase(0); }
		inline Type popBack() { return erase(this->size-1); }
		
		void fill(Type value)
		{
			while(this->size < this->capacity)
				this->data[ this->size++ ] = value;
		}
		
		void resize(size_t new_cap)
		{
			this->capacity = (new_cap > 0 ? new_cap : 16);
			Type *old_data = this->data;
			this->data = new Type[this->capacity];

			if(this->size > this->capacity)
				this->size = this->capacity;
			
			for(size_t i=0; i < this->size; i++)
				this->data[i] = old_data[i];
			
			delete[] old_data;
		}
		
		inline void shrink(){ this->resize(this->size > 0 ? this->size : 1); }
		inline void clear() override { this->size = 0; }
		
		//conversão para texto
		template<typename T=Type, isPrintable<T>* = nullptr>
		std::string strFormat(char c=' ') const 
		{
			std::stringstream ss;
			if(c == ' ')
				for(size_t i=0; i < this->size; i++)
					ss << this->data[i] << ' ';
			if(c == '|')
				for(size_t i=0; i < this->size; i++)
					ss << this->data[i] << '\n';
			else if(c == 's')
				for(size_t i=0; i < this->size; i++)
					ss << this->data[i];
			else if(c == '[')
				ss << "[ " << strFormat() << "]";
			else if(c == '{')
				ss << "{ " << strFormat() << "}";
			else if(c == '/')
			{
				ss << "[" << this->size;
				ss << "/" << this->capacity;
				ss << "] " << strFormat();
			}
			return ss.str();
		}
		
		template<typename T=Type, isntPrintable<T>* = nullptr>
		inline std::string strFormat(char c=' ') const { return Container<Type>::strFormat(c); }
		
		inline operator std::string() const override { return this->strFormat(); }
		
		inline void print() const override { std::cout << (this->strFormat()) << '\n'; }
	};
}
#endif
