#!/bin/bash
###############################################################################
## ISCTE-IUL: Sistemas Operativos
##
## Este módulo destina-se a definir macros de I/O utilitárias.
## Não deverá ser alterado nem submetido com o trabalho.
##
## Nome do Módulo: so_utils.sh
## @author Carlos Coutinho
## Descrição/Explicação do Módulo:
##     Macros para impressão de mensagens de DEBUG, SUCESSO e ERRO
##     Se a variável de ambiente SO_HIDE_COLOURS estiver definida, não mostra cores
##     Se a variável de ambiente SO_HIDE_DEBUG estiver definida, não mostra mensagens de debug
##
## SYNTAX: ". /home/so/utils/bin/so_utils.sh" [disable-colours|enable-colours]
## @param $1: If disable-colours, set SO_HIDE_COLOURS=1;
##            If enable-colours, unset SO_HIDE_COLOURS
##            If not passed, maintains the SO_HIDE_COLOURS setting
###############################################################################

# SO_HIDE_DEBUG=1                   ## Uncomment this line to hide all @DEBUG statements
# SO_HIDE_COLOURS=1                 ## Uncomment this line to disable all escape colouring
. /home/so/utils/bin/so_define_colours.sh "$@"

###############################################################################
## Escreve uma mensagem de DEBUG apenas se SO_HIDE_DEBUG não estiver definida.
## SYNTAX: so_debug [<opcional 1>] [<opcional 2>] ... [<opcional n>]
## Esta macro NÃO CAUSA TERMINAÇÃO do programa que o invoca e retorna 0.
##
## @param $1..n: Informações que se pretende que sejam apresentadas
###############################################################################
so_debug () {
    [ -n "$SO_HIDE_DEBUG" ] && return
    echo -ne "${COLOUR_BACK_FAINT_GRAY}@DEBUG {Ln:$(caller)}${COLOUR_GRAY}" && for arg in "$@"; do echo -ne " [$arg]"; done; echo -e "${COLOUR_NONE}"
}

###############################################################################
## Escreve uma mensagem de SUCESSO, deve ser usado
## em todas as mensagens "positivas" (de SUCESSO) que a aplicação mostra.
## SYNTAX: so_success <passo> [<opcional 1>] [<opcional 2>] ... [<opcional n>]
## Esta macro NÃO CAUSA TERMINAÇÃO do programa que o invoca e retorna 0.
##
## @param $1: passo - Passo do enunciado que está a ser avaliado
## @param $2..n: Informações adicionais que sejam pedidas no passo avaliado
###############################################################################
so_success () {
    (($# < 1)) && echo -e "${COLOUR_LIGHTRED}SYNTAX: so_success <passo> [<opcional 1>] [<opcional 2>] ... [<opcional n>]${COLOUR_NONE}" && return
    echo -ne "${COLOUR_BACK_GREEN}@SUCCESS"
    [ -n "$1" ] && echo -ne " {$1}"
    echo -ne "${COLOUR_GREEN}" && shift && for arg in "$@"; do echo -ne " [$arg]"; done; echo -e "${COLOUR_NONE}"
}

###############################################################################
## Escreve uma mensagem de ERRO, deve ser usado
## em todas as mensagens "negativas" (de falha) que a aplicação mostra.
## SYNTAX: so_error <passo> [<opcional 1>] [<opcional 2>] ... [<opcional n>]
## Esta macro NÃO CAUSA TERMINAÇÃO do programa que o invoca e retorna 0.
##
## @param $1: passo - Passo do enunciado que está a ser avaliado
## @param $2..n: Informações adicionais que sejam pedidas no passo avaliado
###############################################################################
so_error () {
    (($# < 1)) && echo -e "${COLOUR_LIGHTRED}SYNTAX: so_error <passo> [<opcional 1>] [<opcional 2>] ... [<opcional n>]${COLOUR_NONE}" && return
    echo -ne "${COLOUR_BACK_BOLD_RED}@ERROR"
    [ -n "$1" ] && echo -ne " {$1}"
    echo -ne "${COLOUR_RED}" && shift && for arg in "$@"; do echo -ne " [$arg]"; done; echo -e "${COLOUR_NONE}"
}

###############################################################################
## Faz com que todos os comandos seguintes sejam (ou não) pausados até o
## utilizador pressionar qualquer tecla
## SYNTAX: so_pause_on_all_commands: This macro pauses before running each of the next script lines until you press any key (slowly running each script line)
## SYNTAX: so_debug_on_all_commands: This macro shows the script text of the next lines, stopping before running each of them so you can DEBUG information until you enter an empty line
## SYNTAX: so_undo_pause_on_all_commands: This macro releases the pausing before running every next script lines
###############################################################################
_____debug_____ () {
    echo -e "${COLOUR_BACK_FAINT_GRAY}{Ln:$(caller)}:${COLOUR_GRAY} $BASH_COMMAND${COLOUR_YELLOW}";
    while read -rep "@SO debug mode (enter command, or ENTER to continue)> " _so_debug_command; do
        if [ -n "$_so_debug_command" ]; then
            eval "$_so_debug_command";
        else
            echo -ne "${COLOUR_NONE}"
            break;
        fi;
    done
}
so_pause_on_all_commands () {
    trap "read -rsn 1" DEBUG
}
so_pause_debug_on_all_commands () {
    trap _____debug_____ DEBUG
}
so_release_pause_on_all_commands () {
    trap "" DEBUG
}

###############################################################################
## Função "interna", que em caso de exceção, mostra o texto
## "SO: Script exception" e indica o script e a linha onde a exceção ocorreu.
## SYNTAX: so_catch_all_errors
###############################################################################
_____so_handle_error_____ () {
    so_error "SO: Script exception" "Error occurred on Ln:$(caller)"
    exit 1
}
so_catch_all_errors () {
    trap _____so_handle_error_____ ERR
}

so_show_source_line () {
    set -v
}