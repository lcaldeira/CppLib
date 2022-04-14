/*
 *		clear && g++ evaluator_template.cpp -o eval -DMODULE=Vector && ./eval
 */
#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/Utilities/Macros.h>
#else
#include "../../Utilities/header/Macros.h"
#endif

#define INCPATH		routines
#include DYNAMIC_HEADER(INCPATH, MODULE)

using namespace std;

int main() {

	auto tester = TestRoutineDS();
	tester.run();
	tester.showScore();
	
	return 0;
}
