#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos - Parte 1
##
## Este módulo destina-se a realizar operações de I/O utilitárias.
## Não deverá ser alterado nem submetido com o trabalho.
##
## Nome do Módulo: error.sh
## Descrição/Explicação do Módulo:
##    Mensagens de ERRO para cada alínea dos scripts
##    SYNTAX: error <alínea> [<opcional 1>] [<opcional 2>] ... [<opcional n>]
##    Este script não causa terminação do script que o invoca e retorna 0
##
## @param $1: Alínea - Alínea do enunciado que levou ao erro
## @param $2..n: Informações adicionais que sejam pedidas na respetiva alínea
###############################################################################

. /home/so/reference/so_utils.sh
so_error "$@"