#!/bin/bash

args=("$@");

cd ${args[0]}
#echo `/usr/bin/sudo ${args[1]} -project`
#echo `/usr/bin/sudo ${args[1]}`
#echo `/usr/bin/sudo ${args[2]}`

echo `${args[1]} -project`
echo `${args[1]}`
echo `${args[2]}`

