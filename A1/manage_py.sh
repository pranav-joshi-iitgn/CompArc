#!/bin/bash
echo "Integers" > Q2O_py.txt
for (( n=6; n<=10; n++ ))
do
{ time (echo "int $n" | python3 Q2.py) >> Q2O_py.txt ; } 2>> "Q2O_py.txt";
done
echo "" >> Q2O_py.txt ;
echo "Floats" >> Q2O_py.txt ;
for (( n=6; n<=10; n++ ))
do
{ time (echo "float $n" | python3 Q2.py) >> Q2O_py.txt ; } 2>> "Q2O_py.txt";
done