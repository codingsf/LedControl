#!/bin/bash

showHelp () {
	echo "Usage: led_control_client -n <server name>"
	echo "  -h - show this text"
	echo "  -n - server name (required parameter), e.g. led_control_client -n led1"
}

showUsage () {
	echo "this help text"
}

if [[ -z "$1" ]] ; then
	showHelp
	exit 0
fi

while [[ 1 ]]; do
	if [[ "$1" = "-n" ]]; then
		shift; serverName="$1"
	elif [[ "$1" = "-h" ]]; then
		showHelp
	elif [[ -z "$1" ]]; then
		break
	else 
		echo "Unknown key" 1>&2
	fi
	shift
done

if [[ -z "$serverName" ]]; then
	echo "server name not defined" 1>&2
	exit 1
fi

#блок объявления глобальных переменных
readonly PIPE_PREFIX="/tmp/"
readonly SH_PREFIX="./"
readonly SH_SUFFIX=".sh"
readonly SEP=" "
readonly SERVER_PIPE=$PIPE_PREFIX$serverName
readonly READ_PIPE=$PIPE_PREFIX"pid"$$
readonly CLIENT_ID="pid$$"

#если канал сервера не задан, то делать нечего
if  [[ ! -e $SERVER_PIPE ]]; then
	echo "server with fifo $SERVER_PIPE not exist" 1>&2
	exit 1
fi

#основной цикл. Обработка пользовательского ввода
while read -p "> " line; do
	commandString=(${line//${SEP}/ })
	if [[ ${commandString[0]} = "quit" ]]; then
		exit 0
	elif [[ ${commandString[0]} = "usage" ]]; then
		showUsage
	elif [[ -e $SH_PREFIX${commandString[0]}$SH_SUFFIX ]]; then
		subcommand="$SH_PREFIX${commandString[0]}$SH_SUFFIX"
		. $subcommand
	else
		echo "unknown command"
	fi
done

exit 0
