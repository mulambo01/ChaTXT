#!/bin/bash

echo -n "Enter the desired nickname: "
read NICK
echo -n "Enter the desired password: "
read PASS

pass=$(echo -n $PASS | md5sum)
pass=$(echo -n ${pass:0:32} | md5sum)
pass=${pass:0:32}

echo "The string below, need to be appended in the pass.txt file. Pass it to the administrator:"
echo $NICK@$pass@
