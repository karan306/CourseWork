#!/bin/bash

python3 encoder.py $1 $3 > mdp.txt
python3 value_iteration.py mdp.txt > policy.txt
python3 decoder.py $1 policy.txt $3 > foo.txt
# python visualize.py $1 $2
# python visualize.py $1 foo.txt 