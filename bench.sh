#!/usr/bin/env bash
num=$1
case=100

count=1
sum=0
best=1000000
worst=0
while [ $count -lt $(($case + 1)) ]; do
  arg=$(ruby -e "puts (0...$num).to_a.shuffle.join(' ')")
  line=$(./push_swap $arg | wc -l)
  printf "%03s/% 3s: %s\n" $count $case $line
  sum=$(($sum + $line))
  if [ $line -lt $best ]; then
    best=$line
  fi
  if [ $line -gt $worst ]; then
    worst=$line
  fi
  count=$(($count + 1))
done
echo   "num    : $num"
echo   "case   : $case"
echo   "avg    : $(($sum / $(($count - 1))))"
printf "best   : %s\n" $best
printf "worst  : %s\n" $worst
