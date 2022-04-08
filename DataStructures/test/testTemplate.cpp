/*
 *		clear && g++ evaluator_template.cpp -o eval -DMODULE=Vector && ./eval
 */
#include <CppLib/Utilities/Macros.h>
#define INCPATH		routines
#include DYNAMIC_HEADER(INCPATH, MODULE)

using namespace std;

int main() {

	auto tester = TestRoutineDS();
	tester.run();
	tester.showScore();
	
	return 0;
}
