#!/bin/bash
#This bash script will launch n philisopers. Where n is a user provided argument.
#chmod +x launch-philosophers.sh

program=$0
seats=$1
position=$2

if [ $# -ne 2 ] ; then 
   echo "not enough args provided"
   exit 1
fi

count=1
while [ ${count} -le ${position} ] ; do
      ./${program} ${seats} ${count} &
      echo "PID of philosopher#${count} is: " $!
      count=$(( $count + 1 ))
done