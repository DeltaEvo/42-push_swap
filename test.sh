#!/usr/bin/env bash

ARG=`ruby -e "puts (0..$1).to_a.shuffle.join(' ')"`

echo $ARG
./push_swap $ARG | tee last.log | ./checker $ARG
