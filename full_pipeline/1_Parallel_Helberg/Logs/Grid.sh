#!/bin/csh

set echo

./Profiling.sh

./Extract.exe

find . -name "time" -exec rm '{}' ';'

cat Grid.txt
