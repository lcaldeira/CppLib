#!/bin/bash

SOURCE_PATH=$(pwd)
TARGET_PATH=/usr/include/CppLib

mkdir -p $TARGET_PATH

for MODULE in */header
do
	SHORTCUT=$(echo $MODULE | cut -d/ -f1)
	rm -f "$TARGET_PATH/$SHORTCUT"
	ln -s "$SOURCE_PATH/$MODULE"	"$TARGET_PATH/$SHORTCUT"
done
