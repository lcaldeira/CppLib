#ifndef CPPLIB_DATASTRUCTURES_SIMPLEGRAPH_H
#define CPPLIB_DATASTRUCTURES_SIMPLEGRAPH_H

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/DataStructures/Vector.h>
#include <CppLib/DataStructures/List.h>
#else
#include "Vector.h"
#include "List.h"
#endif

namespace DataStructures
{
	template<class Type>
	class SimpleGraph : public Container<Type>
	{
	protected:
		Vector<Type> *vertex;			//vetor de vértices
		Vector<List<Type>*> *relation;	//vetor de listas (relações)
	
		Type* at(size_t index) const { return &(*vertex)[index]; }
		
		void resize(size_t new_size)
		{
			size_t size = this->getSize();
			
			if(new_size == 0 || new_size == size)
				return;
			
			vertex->resize(new_size);
			relation->resize(new_size);
		}
	public:
		SimpleGraph()
		{
			vertex = nullptr;
			relation = nullptr;
		}
		
		SimpleGraph(size_t init_cap)
		{
			if(init_cap==0)
				throw;
			
			vertex = new Vector<Type>(init_cap);
			relation = new Vector<List<Type>*>(init_cap);
		}
		
		SimpleGraph(const SimpleGraph<Type>& g) : SimpleGraph<Type>(g.countVertices())
		{
			size_t size = g.countVertices();
			Vector<Type> v;
			//inserindo vértices
			for(size_t i=0; i < size; i++)
			{
				vertex->pushBack(g.getVertex(i));
				relation->pushBack(new List<Type>());
			}
			//inserindo arestas
			for(size_t i=0; i < size; i++)
			{
				v = g.neighborsOf((*vertex)[i]);
				while(!v.isEmpty())
					(*relation)[i]->pushBack(v.popBack());
			}
		}
		
		~SimpleGraph<Type>()
		{
			if(vertex != nullptr)
			{
				delete vertex;
				vertex = nullptr;
			}
			if(relation != nullptr)
			{
				for(size_t i=0; i < relation->getSize(); i++)
					delete (*relation)[i];
				delete relation;
				relation = nullptr;
			}
		}
		
		SimpleGraph<Type> operator=(SimpleGraph<Type> g)
		{
			this->~SimpleGraph<Type>();
			
			size_t size = g.countVertices();
			vertex = new Vector<Type>(size);
			relation = new Vector<List<Type>*>(size);
			Vector<Type> v;
			
			//inserindo vértices
			for(size_t i=0; i < size; i++)
			{
				vertex->pushBack(g.getVertex(i));
				relation->pushBack(new List<Type>());
			}
			//inserindo arestas
			for(size_t i=0; i < size; i++)
			{
				v = g.neighborsOf((*vertex)[i]);
				while(!v.isEmpty())
					(*relation)[i]->pushBack(v.popBack());
			}
			return *this;
		}
		
		//busca e verificação
		bool isAllocated() const { return (this->vertex != nullptr && this->relation != nullptr); }
		size_t indexOf(Type v) const { return vertex->indexOf(v); }
		inline bool contains(Type v) const { return (indexOf(v) >= 0); }
		bool contains(Type v1, Type v2) const 
		{
			size_t idx1 = indexOf(v1);
			return (idx1 >= 0 ? (*relation)[idx1]->contains(v2) : false);
		}
		
		inline size_t getSize() const { return countVertices() + countEdges(); }
		inline size_t countVertices() const { return vertex->getSize(); }
		size_t countEdges() const 
		{
			size_t qt = 0;
			size_t size = vertex->getSize();
			
			for(size_t i=0; i<size; i++)
				for(size_t j=0; j<size; j++)
					qt += (*relation)[i]->getSize();
			return qt/2;
		}
		
		size_t degreeOf(Type v) const 
		{
			int idx = vertex->indexOf(v);
			return (vertex->isValidIndex(idx) ? (*relation)[idx]->getSize() : 0);
		}
		
		bool operator==(SimpleGraph<Type>& g)
		{
			size_t qtV = this->countVertices();
			size_t qtE = this->countEdges();
			
			if(qtV != g.countVertices() || qtE != g.countEdges())
				return false;
			
			for(size_t i=0; i<qtV; i++)
				if(!g.contains(vertex->get(i)))
					return false;
			
			/*for(size_t i=0; i<qtV; i++)
				for(size_t j=0; j<qtV; j++)
					if(relation->get(i,j) != g.getEdge(vertex->get(i), vertex->get(j)))	
						return false;*/
			
			return true;
		}
		
		//acesso e manipulação
		Type getVertex(size_t index) const { return vertex->get(index); }
		
		void addVertex(Type v)
		{
			if(!vertex->contains(v))
			{
				vertex->pushBack(v);
				relation->pushBack(new List<Type>());
			}
		}
		
		void removeVertex(Type v)
		{
			size_t index = vertex->indexOf(v);
			if(vertex->isValidIndex(index))
			{
				vertex->erase(index);
				delete (*relation)[index];
				relation->erase(index);
				
				size_t idx0;
				for(size_t i=0; i < vertex->getSize(); i++)
				{
					idx0 = (*relation)[i]->indexOf(v);
					if(vertex->isValidIndex(idx0))
						(*relation)[i]->erase(idx0);
				}
			}
		}
		
		inline bool getEdge(Type v1, Type v2) const { return this->contains(v1,v2); }
		
		void addArrow(Type v1, Type v2)
		{
			size_t idx1 = indexOf(v1);
			if(vertex->isValidIndex(idx1))
			{
				List<Type> *adj = (*relation)[idx1];
				
				if(!adj->contains(v2))
				{
					Node<Type> *n = adj->nthNode(0);
					size_t idx2 = 0;
					
					while(!adj->isBaseNode(n) && n->value < v2)
					{
						n = n->next();
						idx2++;
					}
					
					adj->insert(v2, idx2);
				}
			}
		}
		
		inline void addEdge(Type v1, Type v2)
		{
			this->addArrow(v1, v2);
			this->addArrow(v2, v1);
		}
		
		void removeArrow(Type v1, Type v2)
		{
			size_t idx1 = indexOf(v1);
			
			if(vertex->isValidIndex(idx1))
			{
				List<Type> *adj = (*relation)[idx1];
				size_t idx2 = adj->indexOf(v2);
				
				if(adj->isValidIndex(idx2))
					adj->erase(idx2);
			}
		}
		
		inline void removeEdge(Type v1, Type v2)
		{
			this->removeArrow(v1, v2);
			this->removeArrow(v2, v1);
		}
		
		void clear()
		{
			this->vertex->clear();
			for(int i=0; i < relation->getSize(); i++)
				delete (*relation)[i];
			this->relation->clear();
		}
		
		Vector<Type> neighborsOf(Type v) const 
		{
			size_t idx = this->indexOf(v);
			if(this->vertex->isValidIndex(idx))
			{
				List<Type> *rel = (*relation)[idx];
				Node<Type> *node = rel->nthNode(0);
				Vector<Type> vec = Vector<Type>(rel->getSize());
				
				while(!rel->isBaseNode(node))
				{
					vec.pushBack(node->value);
					node = node->next();
				}
				return vec;
			}
			else
				return Vector<Type>(1);
		}
		
		template<typename T=Type, isFundamental<T>* = nullptr>
		std::string strFormat(char c=' ')
		{
			std::stringstream ss;
			Vector<size_t> vec;
			size_t size = vertex->getSize();
			
			for(int i=0; i<size; i++)
			{
				Type value = (*vertex)[i];
				ss << value << ": ";
				ss << neighborsOf(value).strFormat();
				ss << '\n';
			}
			return ss.str();
		}
		
		template<typename T=Type, isntFundamental<T>* = nullptr>
		std::string strFormat(char c=' '){ return "[]"; }
		
		operator std::string(){ return this->strFormat(); }
		virtual void print(){ std::cout << (this->strFormat()) << '\n'; }
	};
}
#endif
