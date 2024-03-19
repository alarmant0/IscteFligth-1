#!/bin/bash
. /home/so/utils/bin/so_define_colours.sh
appname=${0##*/}
(($# < 1)) && \
    echo -e "${COLOUR_LIGHTGREEN}$appname: ${COLOUR_NONE}Utility to compile a C program, generate .exe file, and debug it (with arguments)" && \
    echo -e "${COLOUR_YELLOW}SYNTAX: ${COLOUR_LIGHTGREEN}$appname ${COLOUR_LIGHTCYAN}<file>.c [<exec_arg1> <exec_arg2> ...]${COLOUR_NONE}" && \
    echo && exit 1
filePath=$1
extension="${filePath##*.}"
filename="${filePath%.*}"
so_compile-generate-exe.sh $filePath && \
    shift && \
    echo -e "${COLOUR_LIGHTGREEN}$appname: ${COLOUR_YELLOW}Debugging file ${COLOUR_LIGHTCYAN}./$filename.exe${COLOUR_YELLOW} on gdb with arguments ${COLOUR_LIGHTCYAN}[$@]${COLOUR_NONE}" && \
    gdb -q -ex 'break main' -ex 'info b' -ex 'set print pretty on' -ex=r --args ./$filename.exe "$@"
