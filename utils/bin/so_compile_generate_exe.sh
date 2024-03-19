#!/bin/bash
. /home/so/utils/bin/so_define_colours.sh
appname=${0##*/}
(($# < 1)) && \
    echo -e "${COLOUR_LIGHTGREEN}$appname: ${COLOUR_NONE}Utility to compile a C program and generate the corresponding .exe file with the same name" && \
    echo -e "${COLOUR_YELLOW}SYNTAX: ${COLOUR_LIGHTGREEN}$appname ${COLOUR_LIGHTCYAN}<file>.c [<file2.c> <file3.c> ...]${COLOUR_NONE}" && \
    echo && exit 1
filePath=$1
extension="${filePath##*.}"
[[ $extension != "c" ]] && echo -e "${COLOUR_LIGHTRED}ERROR: Filename $filePath must have extension .c${COLOUR_NONE}" && echo && exit 1
filename="${filePath%.*}"
echo -e "${COLOUR_LIGHTGREEN}$appname: ${COLOUR_YELLOW}Compiling file(s) ${COLOUR_LIGHTCYAN}$@${COLOUR_YELLOW} using gcc -g. The output file will be ${COLOUR_LIGHTCYAN}$filename.exe${COLOUR_NONE}"
gcc -g -o "$filename.exe" $@
