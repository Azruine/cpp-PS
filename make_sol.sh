#!/bin/bash

PROBLEM_NAME=$1
PROBLEM_FOLDER=$2

if [ -z "$PROBLEM_NAME" ] || [ -z "$PROBLEM_FOLDER" ]; then
    echo "Usage: $0 <problem_name> <problem_folder>"
    exit 1
fi

case "$PROBLEM_FOLDER" in
    1)
        echo "Setting target folder to baekjoon"
        TARGET_FOLDER="baekjoon"
        PROBLEM_NAME=$(printf "%05d" "$PROBLEM_NAME")
        ;;
    2)
        echo "Setting target folder to programmers"
        TARGET_FOLDER="programmers"
        ;;
    3)
        echo "Setting target folder to leetcode"
        TARGET_FOLDER="leetcode"
        PROBLEM_NAME=$(printf "%04d" "$PROBLEM_NAME")
        ;;
    *)
        echo "Invalid problem_folder value. Use 1 for baekjoon, 2 for programmers, or 3 for leetcode."
        exit 1
        ;;
esac

if [ ! -d "./src/solved/$TARGET_FOLDER" ]; then
    echo "Folder $TARGET_FOLDER does not exist"
    exit 1
fi

touch ./src/solved/$TARGET_FOLDER/$PROBLEM_NAME.cpp
touch ./src/solved/$TARGET_FOLDER/$PROBLEM_NAME.md

cat ./src/temp.cpp > ./src/solved/$TARGET_FOLDER/$PROBLEM_NAME.cpp
echo "# $PROBLEM_NAME. [](./$PROBLEM_NAME.cpp)" > ./src/solved/$TARGET_FOLDER/$PROBLEM_NAME.md
