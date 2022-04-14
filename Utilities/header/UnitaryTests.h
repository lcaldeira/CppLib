#ifndef CPPLIB_UTILITIES_UNITARYTESTS_H
#define CPPLIB_UTILITIES_UNITARYTESTS_H

#include <iostream>
#include <sstream>

#ifndef CPPLIB_ABS_INC_PATH_F
#include <CppLib/Utilities/Macros.h>
#else
#include "Macros.h"
#endif


/*==================================================== 
 *		Automated test:
 *	
 *	Defines the module's name and path at compilation
 *	to automaticaly imports it. Also, write the test
 *	routines using MODULE macro instead of explicitly
 *	informs the typename.
 *====================================================*/
#ifdef MODULE

	// default header file
	#ifndef INCFILE
	#define INCFILE 				MODULE
	#endif

	// default header path
	#ifndef INCPATH
	#define INCPATH 				.
	#endif

	// include module
	#ifndef IGNORE_DYN_INC
	#include DYNAMIC_HEADER(INCPATH, INCFILE)
	#endif
	
	#ifdef SCOPE
	using namespace SCOPE;
	#endif

#endif

namespace UnitaryTests
{
	enum Categories : char {
		BFNC = 1<<0,		// basic functionalities
		EFNC = 1<<1,		// extra functionalities
		CODE = 1<<2,		// constructor and destructor behaviors
		TPCT = 1<<3,		// type castings
		MEML = 1<<4,		// memory leaks
		PRLL = 1<<5,		// parallelism
	};

	enum Results : char {
		Success='x',		// the tested module was approved
		Failure=' ',		// the tested module was repproved
		AlmostFailure='-',	// the tested module was almost completely repproved
		AlmostSuccess='=',	// the tested module was almost completely approved
		Absent='o',			// the feature/test is not implemented
		Unknown='?',		// the test result was inconclusive
		Valgrind='v',		// the results must be check with valgrind
	};
	
	// sample class of a routine of unitary tests
	template<typename Type>
	class TestRoutine 
	{
	private:
		int reportedSuccesses = 0;
		int reportedTests = 0;
		const char* headerbar = 
			"====================================================================";
		
		std::string indent = "";
		
		std::string removeTabs(std::string str){
			for(size_t i=0; i < str.length(); i++)
				if(str[i] == '\t') {
					str.replace(i,1,4,' ');
					i += 3;
				}
			return str;
		}
		
		void setIndentString(std::string str) {
			int logpage_len = ((std::string) headerbar).length();
			indent = removeTabs(str).substr(0, logpage_len);
		}
		
		void limitedPrint(std::string msg) {
			msg = removeTabs(msg);
			
			int logpage_len = ((std::string) headerbar).length();
			int message_len = msg.length();
			int indent_len = this->indent.length();
			int idx;
			
			do {
				if(message_len <= logpage_len) {
					std::cout << msg << "\n";
					message_len = 0;
				}
				else {
					idx = logpage_len;
					
					while(idx-- > indent_len)
						if(msg[idx] == ' ')
							break;
					
					idx = (idx > indent_len ? idx+1 : logpage_len - indent_len);
					
					std::cout << msg.substr(0, idx) << "\n" << indent;
					msg = msg.substr(idx, message_len);
					message_len = msg.length();
				}
				
			} while(message_len > 0);
		}
	protected:
		void additionalLabels()  {
			// put here another result labels
		}
		
		const void sectionTitle(std::string title) {
			title = " " + removeTabs(title) + " ";
			size_t logpage_len = ((std::string) headerbar).length();
			
			if(title.length() >= logpage_len-4) {
				// break in more lines
				
			}
			
			size_t margin_len = (int)(0.5 + (logpage_len - title.length())/2.0);
			auto margin_bar = std::string(margin_len, ' ');
			auto section_bar = margin_bar + std::string(title.length(), '-');
			
			limitedPrint(section_bar);
			limitedPrint(margin_bar + title);
			limitedPrint(section_bar);
			
		}
		
		const void log(Results res, const char* log_message) {
			std::stringstream ss;
			ss << "[" << (char) res << "]  " << log_message;
			setIndentString("\t\t");
			limitedPrint(ss.str());
			
			if(res == Success)
				reportedSuccesses++;
			if(res != Absent)
				reportedTests++;
		}
		
	public:
		TestRoutine(){
			LOG_NOW();
			printf("(compilation time)\n\n%s\n", headerbar);
			
			#ifdef MODULE
			setIndentString("   ");
			std::stringstream ss;
			ss << ">> Module: \"" << TO_STR(MODULE) << "\"";
			#ifndef NO_INCLUDE
			ss << " at \"" << DYNAMIC_HEADER(INCPATH,INCFILE) << "\"";
			#endif
			limitedPrint(ss.str());
			printf("%s\n", headerbar);
			#endif
			
			setIndentString("\t\t");
			printf("Test labels:\n");
			limitedPrint("\t* get a [" + std::string(1,Success) + "] means 'succeed in the test'");
			limitedPrint("\t* get a [" + std::string(1,AlmostSuccess) + "] means 'almost complete success'");
			limitedPrint("\t* get a [" + std::string(1,AlmostFailure) + "] means 'almost complete failure'");
			limitedPrint("\t* get a [" + std::string(1,Failure) + "] means 'had a total failure'");
			limitedPrint("\t* get a [" + std::string(1,Absent) + "] means 'feature or test not present'");
			limitedPrint("\t* get a [" + std::string(1,Unknown) + "] means 'inconclusive result'");
			limitedPrint("\t* get a [" + std::string(1,Valgrind) + "] means 'check valgrind output'");
			additionalLabels();
			printf("%s\n", headerbar);
		}
		
		~TestRoutine(){
			printf("%s\n", headerbar);
		}
		
		void run(char flag = ~0){
			
			// example of using flags to control the testing pipeline
			// in this case, the basic functionalities are tested
			if(flag & BFNC) {
				sectionTitle("Basic Functionalities");
				/* 
					write 
					here 
					some 
					tests
					or
					function
					calls 
				*/
				log(Absent, DEBUG_MSG("empty test #1 results"));
			}
			//now, only the extra functionalities are tested
			if(flag & EFNC) {
				sectionTitle("Extra Functionalities");
				/* 
					write 
					here 
					more 
					tests
					or
					function
					calls  
				*/
				log(Absent, DEBUG_MSG("test #2 results with long description? no problem!"));
			}
			// this last test works for both flags "CODE" and "TPCT"
			if(flag & (CODE | TPCT)) {
				sectionTitle("Constructor and Destructor");
				/* 
					write 
					here 
					more 
					tests
					or
					function
					calls  
				*/
				log(Absent, DEBUG_MSG("final test #3 results"));
			}
		}
		
		void showScore() {
			printf("%s\n", headerbar);
			printf("Score:\n");
			setIndentString("\t");
			
			std::stringstream ss1;
			ss1 << "\t* " << reportedSuccesses << " successes out of " << reportedTests << " tests performed";
			limitedPrint(ss1.str());
			
			std::stringstream ss2;
			float percent = ((int) (1000.0 * reportedSuccesses/reportedTests)) / 10.0;
			ss2 << "\t* " << percent << "% success rate";
			limitedPrint(ss2.str()); 
		}
	};
	
	/*template<template<typename> class TypeC, 
		isBaseOf<Container<bool>,TypeC<bool>>* = nullptr>
	class DataStructureTestRoutine : public Routine<TypeC>
	{	
	public:
		// print a brief description of the test and its result
		static void writeLog(const char* log_message, EvalResult res){
			printf("[%c]\t%s\n", (char) res, desc);
		}
	public:
		Evaluator(){
			printf("============================================\n");
			printf(">> Template: \"%s<.>\"\n", TO_STR(SELECTED_DS));
			printf("============================================\n");
			printf("Test labels:\n");
			printf("  * get a [ ] means 'had a failure'\n");
			printf("  * get a [-] means 'feature not present'\n");
			printf("  * get a [x] means 'succeed on test'\n");
			printf("  * get a [v] means 'check valgrind output'\n");
			printf("============================================\n\n");
		}
		
		~Evaluator(){
			printf("\n============================================\n");
		}
		
		// pre-defined test messages
		void basicFunc(unsigned int line=0)		{ writeLog("basic functionalities", Absent, line); }
		void extraFunc(unsigned int line=0)		{ writeLog("extra functionalities", Absent, line); }
		void constrDestr(unsigned int line=0)	{ writeLog("constructor and destructor", Absent, line); }
		void stringCast(unsigned int line=0)	{ writeLog("casting to string", Absent, line); }
		void memoryLeak(unsigned int line=0)	{ writeLog("memory leak", Valgrind, line); }
		void parallelism(unsigned int line=0)	{ writeLog("parallel execution", Absent, line); }
	};*/
}

#endif
