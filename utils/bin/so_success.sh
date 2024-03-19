#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos - Parte 1
##
## Este módulo destina-se a realizar operações de I/O utilitárias.
## Não deverá ser alterado nem submetido com o trabalho.
##
## Nome do Módulo: success.sh
## Descrição/Explicação do Módulo:
##    Mensagens de SUCESSO para cada alínea dos scripts
##    SYNTAX: success <alínea> [<opcional 1>] [<opcional 2>] ... [<opcional n>]
##    Este script não causa terminação do script que o invoca e retorna 0
##
## @param $1: Alínea - Alínea do enunciado que levou ao sucesso
## @param $2..n: Informações adicionais que sejam pedidas na respetiva alínea
###############################################################################

. /home/so/utils/bin/so_utils.sh
so_success "$@"