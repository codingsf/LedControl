#!/bin/bash
#developer: Kuksov Pavel
#mail: aimed.fire@gmail.com

message="$CLIENT_ID"
for (( i = 0; i < ${#commandString[@]}; i++ )); do
	message="$message ${commandString[i]}"
done

echo "$message" >$SERVER_PIPE

while [[ 1 ]]; do
	if [[ -e $READ_PIPE ]]; then
		break
	fi
done

read answer <$READ_PIPE
echo $answer
