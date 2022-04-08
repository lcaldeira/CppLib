#!/bin/bash

clear

for ROUTINE in routines/*.h
do
	# get module name
	MODULE=$(echo $ROUTINE | cut -d/ -f2 | cut -d. -f1)
	echo "running '$MODULE' evaluation"
	# generate executable
	g++ "testTemplate.cpp" -o "evaluators/test$MODULE" -DMODULE=$MODULE
	# run evaluation with log output
	./"evaluators/test$MODULE" >> "results/log$MODULE.txt"
done
