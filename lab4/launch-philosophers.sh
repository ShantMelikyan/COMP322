#!/bin/bash
#This bash script will launch multiple philisopers.
#to compile: chmod +x launch-philosophers.sh
#to run: ./launch-philosophers.sh [seats] [position]
#to kill a philosopher use another command line and command: kill -15 [pid]

SEATS=$1
program=./dining-p
POSITION=$2

count=1
while [ ${count} -le ${POSITION} ] ; do
      ${program} ${SEATS} ${count} &
      echo "Philosopher [${count}]'s is PID:" $!
      count=$(( $count + 1 ))
done

