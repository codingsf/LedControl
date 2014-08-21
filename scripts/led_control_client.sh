#!/bin/bash
#основной скрипт клиента
#здесь происходит обработка пользовательского ввода и передача управления в скрипт реализующий конкретную команду
#для скриптов, реализующих конкретную команду, данные скрит представляяет все необходимые данные:
#SERVER_PIPE - канал сервера
#READ_PIPE - канал откуда необходимо читать ответы сервера
#CLIENT_ID - ID клиента
#commandString - массив, в котором аргумент c индексом 0 передает команду, а все последующие - аргументы
#developer: Kuksov Pavel
#mail: aimed.fire@gmail.com

showHelp () {
	echo "Usage: led_control_client -n <server name>"
	echo "  -h - show this text"
	echo "  -n - server name (required parameter), e.g. led_control_client -n led1"
}

showUsage () {
	echo "support commands:"
	echo " - set-led-state <on|off>"
	echo " - get-led-state"
	echo " - set-led-color <red|green|blue>"
	echo " - get-led-color"
	echo " - set-led-rate <0|1|2|3|4|5>"
	echo " - get-led-rate"
	echo " - quit"
	echo " - usage"

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
