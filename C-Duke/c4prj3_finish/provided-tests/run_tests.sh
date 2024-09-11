#!/bin/bash

for testfile in test*.txt; do
  ../poker "$testfile" 10000
done

# create .sh file to automatic deal with many test cases
# store all output results in answers_tests.txt
# diff answers2.txt or answers3.txt with the standard answers.txt
# don't be worry about the result, please read the assignemnt instruction
# there are some difference of output digits which are acceptable.