#!/bin/bash
read line
read line
echo $line | awk '{print $1}' >&2
read line
echo $line >&2
read line
echo $line >&2
while read line
do
  echo $line >&1
done
