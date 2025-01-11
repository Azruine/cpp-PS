#!/bin/bash

PROBLEM_NAME=$1
PROBLEM_FOLDER=$2

if [ -z "$PROBLEM_NAME" ] || [ -z "$PROBLEM_FOLDER" ]; then
    echo "Usage: $0 <problem_name> <problem_folder>"
    exit 1
fi

if [ ! -d "./src/solved/$PROBLEM_FOLDER" ]; then
    echo "Folder $PROBLEM_FOLDER does not exist"
fi

touch ./src/solved/$PROBLEM_FOLDER/$PROBLEM_NAME.cpp
touch ./src/solved/$PROBLEM_FOLDER/$PROBLEM_NAME.md

cat ./src/temp.cpp > ./src/solved/$PROBLEM_FOLDER/$PROBLEM_NAME.cpp
echo "# $PROBLEM_NAME" > ./src/solved/$PROBLEM_FOLDER/$PROBLEM_NAME.md