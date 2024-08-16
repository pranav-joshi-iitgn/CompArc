#!/bin/bash
echo "Integers" > Q2O.txt
for (( n=6; n<=10; n++ ))
do
gcc "Q2I2to$n.c" -o executable;
{ time ./executable >> Q2O.txt ; } 2>> "Q2O.txt";
done
echo "" >> Q2O.txt ;
echo "Doubles" >> Q2O.txt ;
for (( n=6; n<=10; n++ ))
do
gcc "Q2D2to$n.c" -o executable;
{ time ./executable >> Q2O.txt ; } 2>> "Q2O.txt";
done