#define IGNORE_DYN_INC
#include <CppLib/DataStructures/Vector.h>
#include <CppLib/Utilities/UnitaryTests.h>

using namespace DataStructures;
using namespace UnitaryTests;

typedef TestRoutine<Vector<void>> TestRoutineDS;
typedef Vector<int> 			TestTypeBasic;
typedef Vector<std::string>		TestTypeString;
typedef Vector<TestTypeBasic> 	TestTypeCompound;

// specialization of "TestRoutine<>" template
template<>
void TestRoutineDS::run(char flag){
	
	if(flag & BFNC){
		sectionTitle("Basic Functionalities");
		auto v1 = TestTypeBasic();	//	front -> {} <- back
		
		// insert(), pushFront(), pushBack()
		//-------------------------------------------------
		v1.pushFront(2);			//	{2}
		v1.pushFront(1);			//	{1,2}
		v1.pushBack(4);				//	{1,2,4}
		v1.insert(3,2);				//	{1,2,3,4}
		v1.pushFront(0);			//	{0,1,2,3,4}
		
		if(v1.getSize()==5 && v1[0]==0 && v1[1]==1 && v1[2]==2 && v1[3]==3 && v1[4]==4)
			log(Success, DEBUG_MSG("insert operation validated"));
		else 
			log(Failure, DEBUG_MSG("insert operation isn't working"));
		
		// erase(), popFront(), popBack()
		//-------------------------------------------------
		v1.popFront();				//	{1,2,3,4}
		v1.popBack();				//	{1,2,3}
		v1.erase(1);				//	{1,3}
		
		if(v1.getSize()==2 && v1[0]==1 && v1[1]==3)
			log(Success, DEBUG_MSG("erase operation validated"));
		else 
			log(Failure, DEBUG_MSG("erase operation isn't working"));
		
		// comparisons
		//-------------------------------------------------
		auto v2 = TestTypeBasic();
		v2.pushFront(1);
		v2.pushBack(3);
		
		auto v3 = TestTypeBasic();
		v3.pushFront(1);
		v3.pushFront(2);
		v3.pushBack(3);
		
		auto v4 = TestTypeBasic();
		v3.pushFront(4);
		v3.pushFront(2);
		
		auto v5 = TestTypeBasic();
		
		if(v1==v2 && v1!=v3 && v1!=v4 &&v1!=v5)
			log(Success, DEBUG_MSG("comparisons (eq and neq) are working"));
		else 
			log(Failure, DEBUG_MSG("comparisons (eq and neq) aren't working"));
		
		// getSize(), getCapacity()
		//-------------------------------------------------
		if(v1.getSize()==2 && v1.getCapacity()>=2)
			log(Success, DEBUG_MSG("size and capacity getters working"));
		else 
			log(Failure, DEBUG_MSG("size and capacity getters aren't working"));
		
		
		// clear()
		//-------------------------------------------------
		v1.clear();
		if(v1.getSize()==0)
			log(Success, DEBUG_MSG("clear operation is working"));
		else
			log(Failure, DEBUG_MSG("clear operation is not working"));
		
	}
	if(flag & EFNC){
		sectionTitle("Extra Functionalities");
		auto v1 = TestTypeBasic();
		
		// resize()
		//-------------------------------------------------
		v1.resize(12);
		if(v1.getCapacity()==12 && v1.getSize()==0)
			log(Success, DEBUG_MSG("resize operation is working"));
		else
			log(Failure, DEBUG_MSG("resize operation is not working"));
		
		// fill()
		//-------------------------------------------------
		v1.fill(5);
		if(v1.getCapacity()==12 && v1.getSize()==12){
			bool flag = true;
			for(int i=0; i<v1.getSize(); i++)
				if(v1[i] != 5) {
					flag = false;
					break;
				}
			if(flag)
				log(Success, DEBUG_MSG("fill operation is working"));
			else
				log(AlmostFailure, DEBUG_MSG("fill operation is not completely working"));
		}
		else
			log(Failure, DEBUG_MSG("fill operation is not working"));
		
		// shrink()
		//-------------------------------------------------
		int size = v1.getSize();
		v1.popBack();
		v1.popBack();
		v1.shrink();
		if(v1.getSize()==v1.getCapacity() && v1.getSize()==size-2)
			log(Success, DEBUG_MSG("shrink operation is working"));
		else
			log(Failure, DEBUG_MSG("shrink operation is not working"));
	}
	
	if(flag & CODE){
		sectionTitle("Constructor and Destructor");
		log(Absent, DEBUG_MSG("tests not implemented yet"));
		
		/*
		try {
			TestTypeBasic v1 = {3,2,1};
			
			// constructor by initializer list
			//-------------------------------------------------
			if(v1.getSize()==3 && v1[0]==3 && v1[1]==2 && v1[2]==1)
				log(Success, DEBUG_MSG("constructor by initializer list is working"));
			else
				log(Failure, DEBUG_MSG("constructor by initializer list is not working"));
		catch(...) {
				log(Unknown, DEBUG_MSG("constructor by initializer list cannot be tested"));
		}*/
	}
}

/*
{
private:
	Vector<int> *ptr_vi;
	Vector<std::string> *ptr_vs;
	Vector<Vector<int>> *ptr_vv;
};*/
