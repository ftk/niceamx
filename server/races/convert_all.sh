#!/bin/bash
rm -f races.txt

for i in `ls *.race`
do
  base="${i%\.*}"
  race="${base}.txt"
  raced="${base}_d.txt"
  echo $i $race $raced
  ./convert.sh < $i > $race 2> $raced
  echo $base >> races.txt
done
