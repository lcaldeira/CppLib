#!/bin/bash

SOURCE_PATH=$(pwd)
TARGET_PATH=/usr/include/CppLib

mkdir -p $TARGET_PATH

for MODULE_PATH in */header
do
	SHORTCUT=$(echo $MODULE_PATH | cut -d/ -f1)
	rm -f "$TARGET_PATH/$SHORTCUT"
	ln -s "$SOURCE_PATH/$MODULE_PATH"	"$TARGET_PATH/$SHORTCUT"
done
